#ifndef SYSTEMSOLVER_H
#define SYSTEMSOLVER_H

#include <vector>
#include "solarobject.h"

class SystemSolver
{
private:
    std::vector<SolarObject> m_objects;
public:
    SystemSolver();

    void addObject(SolarObject newObject);
    void printObjects();
};

#endif // SYSTEMSOLVER_H
