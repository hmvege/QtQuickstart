#ifndef WAVEFUNCTION_H
#define WAVEFUNCTION_H

#include <armadillo>

class WaveFunction
{
protected:
    int m_NParticles;
    int m_NDimensions;
public:
    WaveFunction(int NParticles, int NDimensions);
    virtual ~WaveFunction();

    virtual double calculate(const arma::Mat<double> &rPos);
    virtual double localEnergy(const arma::Mat<double> &rPos);
};

#endif // WAVEFUNCTION_H
