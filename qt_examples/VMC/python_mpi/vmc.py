import numpy as np
import abc
import time

from mpi4py import MPI


class _BaseWaveFunction:
    """Base class for VMC wave function."""

    def __init__(self, N_particles, N_dimensions):
        """Basic initialiser always needs the number of particles and 
        dimensions."""
        self.N_particles = N_particles
        self.N_dimensions = N_dimensions

    # Abstractclass makes the class instance required in inherited classes.
    @abc.abstractmethod
    def __call__(self, r):
        """Calculates the wave function and returns it."""
        return 0

    @abc.abstractmethod
    def localEnergy(self, r):
        """
        Calculates the local energy as defined by
        E = (1/Psi_T) * H * Psi_T
        """
        return 0


class TwoParticleNonInteractingWF(_BaseWaveFunction):
    def __init__(self, N_particles, N_dimensions, alpha, omega):
        if N_particles != 2:
            raise ValueError("System defined for two electrons only.")
        super().__init__(N_particles, N_dimensions)
        self.alpha = alpha
        self.omega = omega

    def __call__(self, r):
        """Returns wavefunctions.
        Takes positions matrix r."""
        r_squared = np.sum(r**2)
        return np.exp(- 0.5 * self.omega * self.alpha * r_squared)

    def local_energy(self, r):
        r_squared = np.sum(r**2)
        ret_value = 0.5*self.omega**2*r_squared*(1-self.alpha**2)
        ret_value += 3*self.alpha*self.omega
        return ret_value


class VMCSolver:
    def __init__(self, N_particles, N_dimensions, comm, numprocs, rank):
        self.N_particles = N_particles
        self.N_dimensions = N_dimensions
        self.r_shape = (self.N_particles, self.N_dimensions)

        self.comm = comm
        self.numprocs = numprocs
        self.rank = rank

    def initialize(self):
        self.r_old = 2*np.random.rand(*self.r_shape) - 1
        # To make sure we are not getting a shallow copy
        self.r_new = self.r_old.copy()

    def set_wavefunction(self, wf):
        self.wf = wf

    # # TODO: implement numba here, similar to python_numba example.
    # @staticmethod
    # def update_particles(wf_wavefunction, wf_local_energy, old_wf, r_new,
    #                      r_old, step_length, N_dimensions, N_particles,
    #                      MCCycles, seed, wf_args):
    #     for iPart in range(N_particles):

    #         r_new[iPart] = r_old[iPart] + \
    #             step_length*(np.random.uniform(-1, 1, (N_dimensions)))

    #         new_wf = wf_wavefunction(r_new, wf_args)

    #         ratio = new_wf**2 / old_wf**2

    #         if np.random.uniform(0, 1) <= ratio:
    #             old_wf = new_wf
    #             r_old[iPart] = r_new[iPart]

    #             acceptance_counter += 1
    #         else:
    #             new_wf = old_wf
    #             r_new[iPart] = r_old[iPart]

    #     # Should instead return kinetic and potential energy
    #     local_energy = wf_local_energy(r_new, wf_args)

    #     return old_wf, r_old, r_new, local_energy

    def run_vmc(self, MCCycles, step_length):
        """
        Runs VMC code.
        """

        # Variable for storing ratio R used in the Metropolis update
        ratio = 0
        local_energy = 0
        self.energy = 0
        self.energy_squared = 0

        # Sets acceptance counter to zero for accepted configurations
        self.acceptance_counter = 0

        # Sets initial default positions
        self.initialize()

        old_wf = self.wf(self.r_old)

        t0 = time.time()

        for cycle in range(int(MCCycles/self.numprocs)):

            for iPart in range(self.N_particles):

                self.r_new[iPart] = self.r_old[iPart] + \
                    step_length*np.random.uniform(-1, 1, (self.N_dimensions))

                new_wf = self.wf(self.r_new)

                ratio = new_wf**2 / old_wf**2

                if np.random.uniform(0, 1, 1) <= ratio:
                    old_wf = new_wf
                    self.r_old[iPart] = self.r_new[iPart]

                    self.acceptance_counter += 1
                else:
                    new_wf = old_wf
                    self.r_new[iPart] = self.r_old[iPart]

            # Should instead return kinetic and potential energy
            local_energy = self.wf.local_energy(self.r_new)
            self.energy += local_energy
            self.energy_squared += local_energy**2

        t1 = time.time()

        self.energy = self.comm.allgather(self.energy)
        self.energy_squared = self.comm.allgather(self.energy_squared)

        self.energy = np.sum(self.energy) / MCCycles
        self.energy_squared = np.sum(self.energy_squared) / MCCycles

        prec = 8  # Precision
        if self.rank == 0:
            print("Energy:           {:.{w}f}".format(self.energy, w=prec))
            print("Variance(Energy): {:.{w}f}".format(
                (self.energy_squared - self.energy**2) / MCCycles, w=prec))
            print("Acceptance ratio: {:.{w}f}".format(
                self.acceptance_counter/float(self.N_particles*MCCycles),
                w=prec))
            print("Time used:        {:.4f}".format(t1-t0))


def main():
    N_particles = 2
    N_dimensions = 3
    omega = 1.0
    alpha_values = np.linspace(0.8, 1.2, 5)
    # alpha_values = [1.0]
    MCCycles = int(1e4)
    step_length = 1.0

    comm = MPI.COMM_WORLD
    numprocs = comm.Get_size()
    rank = comm.Get_rank()

    VMC = VMCSolver(N_particles, N_dimensions, comm, numprocs, rank)
    WF = TwoParticleNonInteractingWF(N_particles, N_dimensions, 1.0, 1.0)
    VMC.set_wavefunction(WF)

    for alpha in alpha_values:
        if rank == 0:
            print("\nAlpha:           ", alpha)
        WF.alpha = alpha
        VMC.run_vmc(MCCycles, step_length)


if __name__ == '__main__':
    main()
