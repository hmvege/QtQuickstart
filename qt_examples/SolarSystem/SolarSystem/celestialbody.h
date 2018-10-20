#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include "vec3.h"


class CelestialBody
{
private:
public:
    // For now, public variables...
    vec3 position;
    vec3 velocity;
    vec3 force;
    vec3 angularMomentum;
    double mass;
    double kineticEnergy;
    double potentialEnergy;
    string name;

    // Default constructor
    CelestialBody();

    // Destructor
    ~CelestialBody() {}

    // Default, parametrized constructor
    CelestialBody(vec3 newPosition, vec3 newVelocity, double newMass, string newName);

    // Prints the object
    void printObject();
};

#endif // CELESTIALBODY_H
