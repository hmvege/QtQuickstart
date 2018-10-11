#include "solarobject.h"

SolarObject::SolarObject( vec3 newPosition, vec3 newVelocity, double newMass, string newName)
{
    position = newPosition;
    velocity = newVelocity;
    mass = newMass;
    name = newName;
}
