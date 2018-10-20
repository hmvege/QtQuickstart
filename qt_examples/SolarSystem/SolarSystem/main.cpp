#include <iostream>
#include <cmath>
#include "vec3.h"
#include "celestialbody.h"
#include "system.h"
#include "forwardeuler.h"
#include "newtoniangravity.h"
#include "resultstorer.h"


using std::cout;
using std::endl;

int main()
{
    // Initializes sun, earth, jupiter
    double massSun = 1988500e24; // kg
    vec3 posSun(0,0,0);
    vec3 velSun(0,0,0);

    double massEarth = 5.97219e24; // massEarth / massSun
    vec3 posEarth(1,0,0);
    vec3 velEarth(0,2*M_PI,0);

    double massJupiter = 1.0; // Physical mass needed
    vec3 posJupiter(0,0,0);
    vec3 velJupiter(0,0,0);

    // Normalizes all masses to 1
    massEarth /= massSun;
    massJupiter /= massJupiter;
    massSun /= massSun;

    // Sets up the Celestial Body objects
    CelestialBody *earth = new CelestialBody(posEarth, velEarth, massEarth, "earth");
    CelestialBody *jupiter = new CelestialBody(posJupiter, velJupiter, massJupiter, "jupiter");
    CelestialBody *sun = new CelestialBody(posSun, velSun, massSun, "sun");

    // Specifies the number of steps, time to run for and step size
    unsigned long NSteps = 1000;
    double T = 1; // Time, years
    double h = T / double(NSteps);
    double G = 4*M_PI*M_PI;

    // Initializes system
    System S;

    // Initializes integrator
    ForwardEuler integrator;

    // Initializes force
    NewtonianGravity force(G, massSun);

    // Adds objects to the System
    S.addObject(sun);
    S.addObject(earth);
//    S.addObject(jupiter); // First verify that the 2-body problem produces the correct results

    // Initializes a class object for storing results and ultimately printing them
    ResultStorer res(&S, NSteps+1);

    // Push initial positions and velocities to file.
    S.updateEnergies();
    res.pushResults(&S, 0); // Passes system(the object containing all the solar system objects), and the index 0, the initial step

    cout << "Number of bodies in the solar system is: " << S.bodies.size() << endl;

    // Prints start position
    S.bodies[1]->printObject();

    for (unsigned int iStep = 0; iStep < NSteps; iStep++) {
        // Resets all force vec3 vectors in the CelestialBody objects
        S.resetForces();

        // Calculates new forces
        force.calculateForces(&S);

        // Integrates one step forward
        integrator.integrate(&S, h);

        // Find the new kinetic energy, potential energy and angular momentum
        S.updateEnergies();
        force.calculatePotential(&S);

        // Pushes result to storage object
        res.pushResults(&S, iStep);
    }

    // Prints end position
    S.bodies[1]->printObject();

    // Writes results to file
    res.writeToFile("run1");

    return 0;
}
