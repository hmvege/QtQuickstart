#include "forwardeuler.h"

ForwardEuler::ForwardEuler()
{

}

void ForwardEuler::integrate(System *system, const double h)
{
    /*
     * Forward Euler
     */

    for (CelestialBody *obj : system->bodies) {

        obj->position += obj->velocity*h;

        obj->velocity += obj->force*h / obj->mass;
    }
}
