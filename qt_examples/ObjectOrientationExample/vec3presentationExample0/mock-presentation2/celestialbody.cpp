#include "celestialbody.h"

CelestialBody::CelestialBody()
{
}

CelestialBody::CelestialBody(vec3 position, vec3 velocity, double mass, string name) :
    m_position(position), m_velocity(velocity), m_mass(mass), m_name(name)
{
}
