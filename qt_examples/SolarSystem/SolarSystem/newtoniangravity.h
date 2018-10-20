#ifndef NEWTONIANGRAVITY_H
#define NEWTONIANGRAVITY_H

#include <vector>
#include "system.h"

using std::vector;

class NewtonianGravity
{
private:
    double m_G;
    double m_sunMass;
public:
    NewtonianGravity(double G, double sunMass);
    ~NewtonianGravity() {}

    // Method for calculating forces
    void calculateForces(System *system);

    // Method for calculating potential(place here since the potential is force dependent)
    void calculatePotential(System *system);
};

#endif // NEWTONIANGRAVITY_H
