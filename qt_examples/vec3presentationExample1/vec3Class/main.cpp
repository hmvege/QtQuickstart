#include <iostream>
#include "vec3.h"
#include "solarobject.h"
#include "systemsolver.h"

using namespace std;

int main()
{
    vec3 v1;
    vec3 v2(1,2,3);
//    v1.print();
//    v2.print();

//    v1 += v2;
//    v1.print();

    vec3 v3;
    v3 = v1 + v2;

    // Sets up solar system objects
    SolarObject earth(vec3(1,0,0), vec3(0,1,0), 1, "earth");

    // Sets up a system
    SystemSolver system;

    // Add all objects
    system.addObject(earth);

    // Print the objects
    system.printObjects();

    //

    return 0;
}
