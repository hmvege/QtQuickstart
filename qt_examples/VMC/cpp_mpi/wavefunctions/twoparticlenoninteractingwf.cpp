#include "twoparticlenoninteractingwf.h"

TwoParticleNonInteractingWF::TwoParticleNonInteractingWF(int NParticles, int NDimensions) : WaveFunction (NParticles, NDimensions)
{
    if (NParticles != 2)
    {
        printf("System defined for two electrons only.\n");
        exit(1);
    }
}

void TwoParticleNonInteractingWF::setParameters(double omega, double alpha)
{
    // Variational parameters and other goes here
    m_omega = omega;
    m_alpha = alpha;
}

double TwoParticleNonInteractingWF::calculate(const arma::Mat<double> &rPos)
{
    /*
     * None interacting wave function.
     *
     * Psi_T = exp( - alpha * omega * (r1^2 + r2^2)
     *
     * This can be rewritten!
     */
    double rSquared = 0.0;

    for (int iPart = 0; iPart < m_NParticles; iPart++) {
        for (int iDim = 0; iDim < m_NDimensions; iDim++) {
            rSquared += rPos(iPart,iDim)*rPos(iPart,iDim);
        }
    }

    return exp( - 0.5 * m_omega * m_alpha * rSquared);

}

double TwoParticleNonInteractingWF::localEnergy(const arma::Mat<double> &rPos)
{
    /*
     * Non-interacting local energy.
     */
    double rSquared = 0.0;

    for (int iPart = 0; iPart < m_NParticles; iPart++) {
        for (int iDim = 0; iDim < m_NDimensions; iDim++) {
            rSquared += rPos(iPart,iDim)*rPos(iPart,iDim);
        }
    }
    return 0.5*m_omega*m_omega*rSquared*(1-m_alpha*m_alpha) + 3*m_alpha*m_omega;
}
