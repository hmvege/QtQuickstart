#include <iostream>
#include <chrono>
#include <mpi.h>
#include "vmcsystem.h"
#include "wavefunctions/twoparticlenoninteractingwf.h"


using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::duration;

int main(int numberOfArguments, char *cmdLineArguments[])
{
    // MPI Initialization
    int numprocs, processRank;
    MPI_Init (&numberOfArguments, &cmdLineArguments);
    MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank (MPI_COMM_WORLD, &processRank);

    // Program timers
    steady_clock::time_point programStart;
    programStart = steady_clock::now();

    int NParticles = 2;
    int NDimensions = 3;
    double omega = 1.0;

    int MCCycles = 100000;
    double stepLength = 1.0; // This gives around 50% in acceptance ratio

    VMCSystem VMC(NParticles, NDimensions, numprocs, processRank);
    TwoParticleNonInteractingWF WF(NParticles, NDimensions);
    VMC.setWaveFunction(&WF);

    for (double alpha = 0.8; alpha < 1.2; alpha+=0.05)
    {
        if (processRank == 0) {
            printf("\nALPHA = %.2f\n", alpha);
        }
        WF.setParameters(omega, alpha);
        VMC.runVMC(MCCycles, stepLength);
    }

    // Finalizing and printing time taken
    duration<double> programTime = duration_cast<duration<double>>(steady_clock::now() - programStart);

    if (processRank == 0) {
        printf("\nProgram complete. Time used: %f hours (%f seconds)", double(programTime.count())/3600.0, programTime.count());
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}
