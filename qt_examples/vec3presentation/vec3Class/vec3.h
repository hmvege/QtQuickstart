#ifndef VEC3_H
#define VEC3_H

#include <string>

class vec3
{
public:
    double components[3];

    vec3(); // Default constructor

    // Parameterized constructor
    vec3(double x, double y, double z);

    void print();
    void print(std::string msg);

    vec3 &operator+=(const vec3 &other);
    vec3 &operator-=(const vec3 &other);
    vec3 &operator+=(const double &other);
    vec3 &operator-=(const double &other);
//    vec3 &operator*=(const vec3 &other);
//    vec3 &operator/=(const vec3 &other);
};


inline vec3 operator+(vec3 lhs, vec3 rhs)
{
    lhs += rhs;
    return lhs;
}

inline vec3 operator-(vec3 lhs, vec3 rhs)
{
    lhs -= rhs;
    return lhs;
}


inline vec3 operator+(vec3 lhs, double rhs)
{
    lhs += rhs;
    return lhs;
}

inline vec3 operator-(vec3 lhs, double rhs)
{
    lhs -= rhs;
    return lhs;
}


#endif // VEC3_H
