#include "wavefunction.h"
#include <cmath>

WaveFunction::WaveFunction(int NParticles, int NDimensions) :
    m_NParticles(NParticles),
    m_NDimensions(NDimensions)
{
    /*
     * Base class for all wave functions.
     */

}

WaveFunction::~WaveFunction()
{

}

double WaveFunction::calculate(const arma::Mat<double> &rPos)
{
    /*
     * None interacting wave function.
     */
    exit(0);
    return 0.0;
}

double WaveFunction::localEnergy(const arma::Mat<double> &rPos)
{
    /*
     * Non-interacting local energy.
     */
    exit(0);
    return 0.0;
}
