#include <iostream>
#include <cmath>
#include "vec3.h"
#include "celestialbody.h"
#include "system.h"
#include "forwardeuler.h"
#include "newtoniangravity.h"

using std::cout;
using std::endl;

int main()
{
    // Testing some basic vec3 operations
    vec3 v1(1,2,3), v2(3,2,1);
    v1 += v2;
    v1.print();

    exit(1); // Try to run some basic vec3 operations before continuing!

    // Project begins here
    // Initializes sun, earth, jupiter
    double massSun = 1988500e24; // kg
    vec3 posSun(0,0,0);
    vec3 velSun(0,0,0);

    double massEarth = 5.97219e24; // massEarth / massSun
    vec3 posEarth(1,0,0);
    vec3 velEarth(0,2*M_PI,0);

    double massJupiter = 1.0;
    vec3 posJupiter(0,0,0);
    vec3 velJupiter(0,0,0);

    // Creates new CelestialBody objects for sun, earth and jupiter
    CelestialBody *sun = new CelestialBody(posSun, velSun, massSun, "sun");
    // Add earth here!!

    // Specifies the number of steps, time to run for and step size
    int NSteps = 100;
    double T = 1; // Time, years
    double h = T / double(NSteps);
    double G = 4*M_PI*M_PI;

    System S;
    ForwardEuler integrator;
    NewtonianGravity force(G, massSun);

    S.addObject(sun);
    S.addObject(earth); 

    // First verify that the 2-body problem produces the 
    // correct results before moving on with the three body problems
    // S.addObject(jupiter); 

    cout << "Number of bodies in the solar system is: " << S.bodies.size() << endl;

    // Prints start position of Earth
    S.bodies[1]->printObject();

    for (int iStep = 0; iStep < NSteps; iStep++)
    {
        S.resetForces(); // Since we only stores one step at the time...
        force.calculateForces(&S);
        integrator.integrate(&S, h);

    }

    // Prints end position of Earth, which should be approximately the same as the start
    S.bodies[1]->printObject();

    return 0;
}
