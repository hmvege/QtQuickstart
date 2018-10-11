#ifndef SOLAROBJECT_H
#define SOLAROBJECT_H

#include "vec3.h"
#include <string>


using std::string;

class SolarObject
{
public:
    vec3 position;
    vec3 velocity;
    double mass;
    string name;

    SolarObject(vec3 newPosition, vec3 newVelocity, double newMass, string newName);
};

#endif // SOLAROBJECT_H
