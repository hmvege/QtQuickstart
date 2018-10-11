#include "systemsolver.h"
#include <iostream>

using std::cout;
using std::endl;

SystemSolver::SystemSolver()
{

}

void SystemSolver::addObject(SolarObject newObject)
{
    m_objects.push_back(newObject);
}

void SystemSolver::printObjects()
{
    for (unsigned int i = 0; i < m_objects.size(); i++)
    {
        m_objects[i].print();
    }
}
