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

    virtual double calculate(const arma::Mat<double> &rPos) = 0;
    virtual double localEnergy(const arma::Mat<double> &rPos) = 0;
};

#endif // WAVEFUNCTION_H
