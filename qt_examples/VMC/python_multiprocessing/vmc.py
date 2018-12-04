import numpy as np
import abc
import time
import copy as cp

import multiprocessing as mp


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
    def __init__(self, N_particles, N_dimensions, numprocs=0):
        self.N_particles = N_particles
        self.N_dimensions = N_dimensions
        self.numprocs = numprocs
        self.r_shape = (self.N_particles, self.N_dimensions)

    def initialize(self):
        self.r_old = 2*np.random.rand(*self.r_shape) - 1
        # To make sure we are not getting a shallow copy
        self.r_new = self.r_old.copy()

    def set_wavefunction(self, wf):
        self.wf = wf

    @staticmethod
    def run_metropolis(input_values):
        [wavefunction, r_new, r_old, step_length,
         N_dimensions, N_particles, MCCycles, seed] = input_values
        acceptance_counter = 0

        np.random.seed(seed)

        energy = 0
        energy_squared = 0

        old_wf = wavefunction(r_old)

        for cycle in range(MCCycles):
            for iPart in range(N_particles):

                r_new[iPart] = r_old[iPart] + \
                    step_length*np.random.uniform(-1, 1, (N_dimensions))

                new_wf = wavefunction(r_new)

                ratio = new_wf**2 / old_wf**2

                if np.random.uniform(0,1) <= ratio:
                    old_wf = new_wf
                    r_old[iPart] = r_new[iPart]

                    acceptance_counter += 1
                else:
                    new_wf = old_wf
                    r_new[iPart] = r_old[iPart]

            # Should instead return kinetic and potential energy
            local_energy = wavefunction.local_energy(r_new)
            energy += local_energy
            energy_squared += local_energy**2

        return energy, energy_squared, acceptance_counter

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

        t0 = time.time()

        if self.numprocs != 0:
            with mp.Pool(processes=self.numprocs) as p:
                # Sets up input values.
                input_values = zip(
                    [self.wf for i in range(self.numprocs)],
                    [self.r_new for i in range(self.numprocs)],
                    [self.r_old for i in range(self.numprocs)],
                    [step_length for i in range(self.numprocs)],
                    [self.N_dimensions for i in range(self.numprocs)],
                    [self.N_particles for i in range(self.numprocs)],
                    [int(MCCycles / self.numprocs)
                        for i in range(self.numprocs)],
                    # Ensures each processor has a different seed.
                    list(range(self.numprocs)))

                # Lets multiprocessing handle the parallelization
                results = p.map(self.run_metropolis, input_values)

                self.energy = np.sum([r[0] for r in results])
                self.energy_squared = np.sum([r[1] for r in results])
                self.acceptance_counter = np.sum([r[2] for r in results])
        else:
            self.energy, self.energy_squared, self.acceptance_counter = \
                self.run_metropolis([self.wf, self.r_new, self.r_old, step_length,
                             self.N_dimensions, self.N_particles, MCCycles,
                             0]) 

        t1 = time.time()

        self.energy /= MCCycles
        self.energy_squared /= MCCycles

        prec = 8  # Precision
        print("Energy:           {:.{w}f}".format(self.energy, w=prec))
        print("Variance(Energy): {:.{w}f}".format(
            (self.energy_squared - self.energy**2)/MCCycles, w=prec))
        print("Acceptance ratio: {:.{w}f}".format(
            self.acceptance_counter/float(self.N_particles*MCCycles), w=prec))
        print("Time used:        {:.4f}".format(t1-t0))


def main():
    numprocs = 4
    N_particles = 2
    N_dimensions = 3
    omega = 1.0
    alpha_values = np.linspace(0.8, 1.2, 5)
    MCCycles = int(1e4)
    step_length = 1.0

    VMC = VMCSolver(N_particles, N_dimensions, numprocs)
    WF = TwoParticleNonInteractingWF(N_particles, N_dimensions, 1.0, 1.0)
    VMC.set_wavefunction(WF)

    for alpha in alpha_values:
        print("\nAlpha:           ", alpha)
        WF.alpha = alpha
        VMC.run_vmc(MCCycles, step_length)


if __name__ == '__main__':
    main()
