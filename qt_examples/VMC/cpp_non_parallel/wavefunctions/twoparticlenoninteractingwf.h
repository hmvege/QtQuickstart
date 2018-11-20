#ifndef TWOPARTICLENONINTERACTINGWF_H
#define TWOPARTICLENONINTERACTINGWF_H

#include "wavefunctions/wavefunction.h"

class TwoParticleNonInteractingWF : public WaveFunction
{
private:
    double m_omega = 0;
    double m_alpha = 0;
public:
    TwoParticleNonInteractingWF(int NParticles, int NDimensions);

    void setParameters(double omega, double alpha);
    double calculate(const arma::Mat<double> &rPos);
    double localEnergy(const arma::Mat<double> &rPos);
};

#endif // TWOPARTICLENONINTERACTINGWF_H
