#include "helium.h"

Helium::Helium(int NParticles, int NDimensions) : WaveFunction (NParticles, NDimensions)
{
    if (NParticles != 2)
    {
        printf("Helium atom only has two electrons.\n");
        exit(1);
    }
}

double Helium::calculate(const arma::Mat<double> &rPos)
{
    /*
     * Wave functions. Takes in position and particle
     */
    double sum = 0;
    for (int i = 0; i < m_NParticles; i++) {
        for (int j = 0; j < m_NDimensions; j++) {
            sum += rPos(i,j)*rPos(i,j);
        }
    }
    return exp( - 0.5 * m_omega * sum);

}

double Helium::localEnergy(const arma::Mat<double> &rPos)
{
    /*
     * Returns the local energy for the wave functions. Need to have derived
     * E_L = (1/Psi) * H * Psi, with H being the Hamiltonian and Psi the trial wave function.
     */
    double rSquared = 0;
    double kineticEnergy = 0;
    double potentialEnergy = 0;

    for (int i = 0; i < m_NParticles; i++) {
        // Calculates the laplacian numerically
        rSquared = 0;
        for (int j = 0; j < m_NDimensions; j++) {
            rSquared += rPos(i,j)*rPos(i,j);
        }

    }
    kineticEnergy *= -0.5;
    potentialEnergy *= 0.5*m_omega*m_omega;

//    for (int i = 0; i < nParticles; i++)
//    {
//        kineticEnergy += laplacian(r,i);
//        for (int j = 0; j < nDimensions; j++)
//        {
//            potentialEnergy += r[i][j]*r[i][j];
//        }
//    }
}

void Helium::setParameters(double omega)
{
    // Variational parameters and other goes here
    m_omega = omega;
}
