import numpy as np
import abc
import time

import numba as nb


class _BaseWaveFunction:
    """Base class for VMC wave function."""

    def __init__(self, N_particles, N_dimensions):
        """Basic initialiser always needs the number of particles and 
        dimensions."""
        self.N_particles = N_particles
        self.N_dimensions = N_dimensions

    # Abstractclass makes the class instance required in inherited classes.
    @staticmethod
    @abc.abstractmethod
    def wavefunction(r):
        """Calculates the wave function and returns it."""
        return 0

    @staticmethod
    @abc.abstractmethod
    def localEnergy(r):
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

    @staticmethod
    @nb.jit(nopython=True)
    def wavefunction(r, args):
        """Returns wavefunctions.
        Takes positions matrix r."""
        omega, alpha = args
        r_squared = np.sum(r**2)
        return np.exp(- 0.5 * omega * alpha * r_squared)

    @staticmethod
    @nb.jit(nopython=True)
    def local_energy(r, args):
        omega, alpha = args
        r_squared = np.sum(r**2)
        ret_value = 0.5*omega**2*r_squared*(1-alpha**2)
        ret_value += 3*alpha*omega
        return ret_value


class VMCSolver:
    def __init__(self, N_particles, N_dimensions, N_processors):
        self.N_particles = N_particles
        self.N_dimensions = N_dimensions
        self.r_shape = (self.N_particles, self.N_dimensions)

    def initialize(self):
        self.r_old = 2*np.random.rand(*self.r_shape) - 1
        # To make sure we are not getting a shallow copy
        self.r_new = self.r_old.copy()

    def set_wavefunction(self, wf):
        self.wf = wf

    @staticmethod
    @nb.njit(parallel=False)
    def run_metropolis(wf_wavefunction, wf_local_energy, r_new, r_old,
                       step_length, N_dimensions, N_particles, MCCycles, 
                       seed, wf_args):


        acceptance_counter = 0

        np.random.seed(seed)

        old_wf = wf_wavefunction(r_old, wf_args)

        energy = np.zeros(MCCycles, dtype=np.float64)
        energy_squared = np.zeros(MCCycles, dtype=np.float64)

        for cycle in nb.prange(MCCycles):
            for iPart in range(N_particles):

                r_new[iPart] = r_old[iPart] + \
                    step_length*(np.random.uniform(-1, 1, (N_dimensions)))

                new_wf = wf_wavefunction(r_new, wf_args)

                ratio = new_wf**2 / old_wf**2

                if np.random.uniform(0, 1) <= ratio:
                    old_wf = new_wf
                    r_old[iPart] = r_new[iPart]

                    acceptance_counter += 1
                else:
                    new_wf = old_wf
                    r_new[iPart] = r_old[iPart]

            # Should instead return kinetic and potential energy
            local_energy = wf_local_energy(r_new, wf_args)

            energy[cycle] = local_energy
            energy_squared[cycle] = local_energy**2

        return energy.sum(), energy_squared.sum(), acceptance_counter

    def run_vmc(self, MCCycles, step_length, wf_args=[]):
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

        old_wf = self.wf.wavefunction(self.r_old, wf_args)
        # e = self.wf.local_energy(self.r_old, *wf_args)
        # exit(1)
        t0 = time.time()

        self.energy, self.energy_squared, self.acceptance_counter = \
            self.run_metropolis(self.wf.wavefunction, self.wf.local_energy,
                                self.r_new, self.r_old, step_length,
                                self.N_dimensions, self.N_particles, MCCycles,
                                0, wf_args)
        self.energy /= MCCycles
        self.energy_squared /= MCCycles

        t1 = time.time()

        prec = 8  # Precision
        print("Energy:           {:.{w}f}".format(self.energy, w=prec))
        print("Variance(Energy): {:.{w}f}".format(
            (self.energy_squared - self.energy**2) / MCCycles, w=prec))
        print("Acceptance ratio: {:.{w}f}".format(
            self.acceptance_counter/float(self.N_particles*MCCycles), w=prec))
        print("Time used:        {:.4f}".format(t1-t0))


def main():
    N_processors = 4
    N_particles = 2
    N_dimensions = 3
    omega = 1.0
    alpha_values = np.linspace(0.8, 1.2, 5)
    MCCycles = int(1e4)
    step_length = 1.0

    VMC = VMCSolver(N_particles, N_dimensions, N_processors)
    WF = TwoParticleNonInteractingWF(N_particles, N_dimensions, 1.0, 1.0)
    VMC.set_wavefunction(WF)

    for alpha in alpha_values:
        print("\nAlpha:           ", alpha)
        WF.alpha = alpha
        VMC.run_vmc(MCCycles, step_length, [omega, alpha])


if __name__ == '__main__':
    main()
