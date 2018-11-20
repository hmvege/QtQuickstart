#include <iostream>
#include <chrono>
#include "vmcsystem.h"
#include "wavefunctions/twoparticlenoninteractingwf.h"


using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::duration;

int main(int numberOfArguments, char *cmdLineArguments[])
{
    // Program timers
    steady_clock::time_point programStart;
    programStart = steady_clock::now();

    int NParticles = 2;
    int NDimensions = 3;
    double omega = 1.0;

    int MCCycles = 1000000;
    double stepLength = 1.0; // This gives around 50% in acceptance ratio

    VMCSystem VMC(NParticles, NDimensions);
    TwoParticleNonInteractingWF WF(NParticles, NDimensions);
    VMC.setWaveFunction(&WF);

    for (double alpha = 0.8; alpha < 1.2; alpha+=0.05)
    {
        printf("\nALPHA = %.2f\n", alpha);
        WF.setParameters(omega, alpha);
        VMC.runVMC(MCCycles, stepLength);
    }

    // Finalizing and printing time taken
    duration<double> programTime = duration_cast<duration<double>>(steady_clock::now() - programStart);

    printf("\nProgram complete. Time used: %f hours (%f seconds)", double(programTime.count())/3600.0, programTime.count());

    return 0;
}
