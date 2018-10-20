#ifndef RESULTSTORER_H
#define RESULTSTORER_H

#include <string>
#include "system.h"

using std::string;

class ResultStorer
{
private:
    unsigned long m_NObjects;
    unsigned long m_NSteps;
    unsigned long m_NTotElements;

    std::vector<vec3> m_positions;
    std::vector<vec3> m_velocities;
    std::vector<double> m_kineticEnergies;
    std::vector<double> m_potentialEnergies;
    std::vector<vec3> m_angularMomentum;
    std::vector<std::string> m_objectNames;

    // Contigious memory allocation
    inline unsigned long getIndex(unsigned long iStep, unsigned long iObj) {
        return iObj + m_NObjects*iStep;
    }

public:
    ResultStorer(System *S, unsigned long NSteps);
    ~ResultStorer();

    void pushResults(System *S, unsigned long iStep);
    void writeToFile(string runName);
};

#endif // RESULTSTORER_H
