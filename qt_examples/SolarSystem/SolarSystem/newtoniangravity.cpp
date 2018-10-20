#include "newtoniangravity.h"
#include <cmath>

NewtonianGravity::NewtonianGravity(double G, double sunMass)
{
    m_G = G;
    m_sunMass = sunMass;
}


void NewtonianGravity::calculateForces(System *system)
{
    /*
     * Takes the system class and calculates forces between the objects
     */

    // Distance, temporary distance vector and temporary force vector
    double r = 0;
    vec3 r_temp(0, 0, 0);
    vec3 force_temp(0, 0, 0);

    // Calculates forces between all objects
    for (unsigned int iObj = 0; iObj < system->bodies.size(); iObj++) {
        for (unsigned int jObj = iObj + 1; jObj < system->bodies.size(); jObj++) {

            // Calculates the distance between object i and j
            r_temp = system->bodies[iObj]->position - system->bodies[jObj]->position;
            r = sqrt(r_temp.length());

            // Sets forces from object j on i
            force_temp = r_temp / (r*r*r) * (-m_G) * system->bodies[iObj]->mass * system->bodies[jObj]->mass;
            system->bodies[iObj]->force += force_temp;

            // Uses N3L and sets forces from object i on j
            system->bodies[jObj]->force -= force_temp;

        }
    }
}

void NewtonianGravity::calculatePotential(System *system)
{
    // Temporary distance vector defined as r = |x_i - x_j|
    vec3 distance = {0,0,0};

    for (CelestialBody *iobj : system->bodies)
    {
        // Resets potential energy
        iobj->potentialEnergy = 0;

        // Sums up all of the potential energy contributions
        for (CelestialBody *jobj : system->bodies)
        {
            if (iobj == jobj) continue;
            distance = iobj->position - jobj->position;
            iobj->potentialEnergy -= m_G * jobj->mass * iobj->mass / distance.length();
        }
    }
}
