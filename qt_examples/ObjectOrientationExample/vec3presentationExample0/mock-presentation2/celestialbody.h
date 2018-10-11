#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include "vec3.h"


class CelestialBody
{
private:
    vec3 m_position;
    vec3 m_velocity;
    double m_mass;
    double m_kineticEnergy;
    double m_potentialEnergy;
    string m_name;
public:
    CelestialBody();
    CelestialBody(vec3 position, vec3 velocity, double mass, string name);

    string getName() { return m_name; }
};

#endif // CELESTIALBODY_H
