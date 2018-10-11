#include "vec3.h"
#include <iostream>

using std::cout;
using std::endl;

vec3::vec3()
{
    components[0] = 0;
    components[1] = 0;
    components[2] = 0;
}

vec3::vec3(double x, double y, double z)
{
    components[0] = x;
    components[1] = y;
    components[2] = z;
}

void vec3::print()
{
    cout << "[" << components[0] << ", " << components[1] <<", " << components[2] << "]" <<endl;
}

void vec3::print(std::string msg)
{
    cout << msg;
    print();
}

vec3 &vec3::operator+=(const vec3 &other)
{
    components[0] += other.components[0];
    components[1] += other.components[1];
    components[2] += other.components[2];
    return *this;
}


vec3 &vec3::operator-=(const vec3 &other)
{
    components[0] -= other.components[0];
    components[1] -= other.components[1];
    components[2] -= other.components[2];
    return *this;
}


vec3 &vec3::operator+=(const double &other)
{
    components[0] += other;
    components[1] += other;
    components[2] += other;
    return *this;
}


vec3 &vec3::operator-=(const double &other)
{
    components[0] -= other;
    components[1] -= other;
    components[2] -= other;
    return *this;
}
