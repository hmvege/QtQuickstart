#ifndef VEC3_H
#define VEC3_H

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class vec3
{
private:
    double v[3];

public:
    vec3(); // Default constructor
    ~vec3(); // Destructor

    // Copy constructor
    vec3(vec3 const &copy);

    // Parametetrized constructor
    vec3(double x, double y, double z);

    // Copy assignement constructor
    vec3 &operator= (const vec3 &copy);

    // Printing functions
    void print();

    // Setters, a way of updating private class variables
    void setXYZ(double x, double y, double z) {
        v[0] = x;
        v[1] = y;
        v[2] = z;
    }

    // Getters, a way of getting private class variables
    double x() const { return v[0]; } // Const means that you cannot use the returns value to modify the object.
    // Add one for y() and z()

    // Missing a way of taking the length of a vector


    // Operator overloading
    double &operator[](int index) { return v[index]; } // Allows retrieving components like vec[i]

    // Overloading method for adding vectors
    vec3 &operator+=(const vec3 &other); // This allows c += a

    // Add methods for subtracting, multiplying and dividing with other vectors

    // Add methods for addin, subtracting, multiplying and dividing with other doubles

};

inline vec3 operator+(vec3 lhs, vec3 rhs)
{
    // This allows c = a + b
    lhs += rhs;
    return lhs;
}


#endif // VEC3_H
