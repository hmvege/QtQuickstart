#include "vmcsystem.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <mpi.h>

using std::cout;
using std::endl;

VMCSystem::VMCSystem(int NParticles, int NDimensions, int numprocs, int rank) :
    m_NParticles(NParticles),
    m_NDimensions(NDimensions),
    m_numprocs(numprocs),
    m_rank(rank)
{
    m_newWaveFunction = 0;
    m_oldWaveFunction = 0;

    m_rNew.resize(m_NParticles, m_NDimensions);
    m_rOld.resize(m_NParticles, m_NDimensions);

    m_rNew.zeros();
    m_rOld.zeros();
}


void VMCSystem::runVMC(int MCCycles, double stepLength)
{
    /*
     * Runs the Variational Monte Carlo integration.
     */

    // Variable for storing ratio R used in the Metropolis update
    double ratio = 0;

    double localEnergy = 0;
    m_energy = 0;
    m_energySquared = 0;

    // Sets acceptance counter to zero for accepted configurations
    m_acceptanceCounter = 0;

    // Sets up RNGs
    std::mt19937_64 generator(1234 + m_rank);
    std::uniform_real_distribution<double> uniformDistribution(-1,1);
    std::uniform_real_distribution<double> acceptanceDistribution(0,1);

    // Sets particle positions to some initial random value.
    for (int iPart = 0; iPart < m_NParticles; iPart++)
    {
        for (int iDim = 0; iDim < m_NDimensions; iDim++)
        {
            m_rOld(iPart,iDim) = uniformDistribution(generator);
            m_rNew(iPart,iDim) = m_rOld(iPart,iDim);
        }
    }

    // Splits MC cycles for all processors
    m_MCCycles = MCCycles / m_numprocs;

    // Sets initial wave function
    m_oldWaveFunction = m_WF->calculate(m_rOld);

    for (int cycle = 0; cycle < m_MCCycles; cycle++)
    {

        // Performs a Metropolis update on each particle
        for (int iPart = 0; iPart < m_NParticles; iPart++)
        {

            // Sets a suggested update
            for (int iDim = 0; iDim < m_NDimensions; iDim++) {
                m_rNew(iPart,iDim) = m_rOld(iPart,iDim) + stepLength*uniformDistribution(generator);
            }

            // Retrieves new wave function
            m_newWaveFunction = m_WF->calculate(m_rNew);

            // Updates ratio
            ratio = (m_newWaveFunction*m_newWaveFunction) / (m_oldWaveFunction*m_oldWaveFunction);

            // Metropolis test
            if (acceptanceDistribution(generator) <= ratio)
            {
                // Accepts new state, and updates
                m_oldWaveFunction = m_newWaveFunction;
                for (int iDim = 0; iDim < m_NDimensions; iDim++)
                {
                    m_rOld(iPart,iDim) = m_rNew(iPart,iDim);
                }

                // Updates acceptance counter
                m_acceptanceCounter++;
            }
            else
            {
                // Resets parameters
                m_newWaveFunction = m_oldWaveFunction;
                for (int iDim = 0; iDim < m_NDimensions; iDim++)
                {
                    m_rNew(iPart,iDim) = m_rOld(iPart,iDim);
                }
            }


        }

        // Sample the new local energy of the system.
        localEnergy = m_WF->localEnergy(m_rNew);
        m_energy += localEnergy;
        m_energySquared += (localEnergy*localEnergy);

    }

    double tmpEnergy = 0;
    double tmpEnergySquared = 0;

    MPI_Reduce(&m_energy, &tmpEnergy, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&m_energySquared, &tmpEnergySquared, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    m_energy = tmpEnergy / double(m_MCCycles*m_numprocs);
    m_energySquared = tmpEnergySquared / double(m_MCCycles*m_numprocs);

//    cout << m_MCCycles*m_numprocs << endl;

    if (m_rank==0) {
        cout << std::setprecision(16) << "Energy:           " << m_energy << endl;
        cout << std::setprecision(16) << "Variance(Energy): " << (m_energySquared - m_energy*m_energy) / double(m_MCCycles) << endl;
        cout << std::setprecision(16) << "Acceptance ratio: " << m_acceptanceCounter / double(m_NParticles*m_MCCycles) << endl;
    }
}
