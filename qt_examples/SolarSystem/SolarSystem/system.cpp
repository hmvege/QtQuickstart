#include "system.h"

System::System()
{

}

void System::resetForces() {
    /*
     * Ensures the force vector in each object is set to zero.
     */
    for (CelestialBody *obj : bodies) {
        obj->force = {0,0,0};
    }
}

void System::updateEnergies()
{
    for (CelestialBody *obj : bodies) {
        obj->kineticEnergy = obj->velocity.lengthSquared() * obj->mass * 0.5;
        obj->angularMomentum = cross(obj->position, obj->velocity) * obj->mass;
    }
}
