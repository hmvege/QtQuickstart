#ifndef HELIUM_H
#define HELIUM_H

#include "wavefunctions/wavefunction.h"

class Helium : public WaveFunction
{
private:
    double m_omega = 0;
public:
    Helium(int NParticles, int NDimensions);

    virtual double calculate(const arma::Mat<double> &rPos);
    virtual double localEnergy(const arma::Mat<double> &rPos);

    void setParameters(double omega);
};

#endif // HELIUM_H
