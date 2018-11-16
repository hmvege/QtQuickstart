#include <iostream>
#include "vmcsystem.h"
#include "wavefunctions/twoparticlenoninteractingwf.h"

using namespace std;

int main()
{
    int NParticles = 2;
    int NDimensions = 3;
    double omega = 1.0;

    int MCCycles = 100000;
    double stepLength = 1.0; // This gives around 50% in acceptance ratio

    VMCSystem VMC(NParticles, NDimensions);
    TwoParticleNonInteractingWF WF(NParticles, NDimensions);
    VMC.setWaveFunction(&WF);

    for (double alpha = 0.25; alpha < 2.0; alpha+=0.05)
    {
        printf("\nALPHA = %.2f\n", alpha);
        WF.setParameters(omega, alpha);
        VMC.runVMC(MCCycles, stepLength);
    }

    return 0;
}
