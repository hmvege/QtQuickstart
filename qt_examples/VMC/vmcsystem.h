#ifndef VMCSYSTEM_H
#define VMCSYSTEM_H

#include <armadillo>
#include "wavefunctions/wavefunction.h"

class VMCSystem
{
private:
    int m_NParticles;
    int m_NDimensions;
    unsigned long long m_acceptanceCounter;

    // Wave functions
    double m_newWaveFunction;
    double m_oldWaveFunction;

    // Position
    arma::Mat<double> m_rOld;
    arma::Mat<double> m_rNew;

    // Wave function, empty pointer, ready to be initialized
    WaveFunction *m_WF = nullptr;

    // Variables to store energy in
    double m_energy = 0;
    double m_energySquared = 0;
public:
    VMCSystem(int NParticles, int NDimensions);

    void setWaveFunction(WaveFunction * WF) { m_WF = WF; }

    void runVMC(int MCCycles, double stepLength);
};

#endif // VMCSYSTEM_H
