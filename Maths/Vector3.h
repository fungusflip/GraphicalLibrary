#pragma once
#include <corecrt_math.h>

class Vector3
{
public:
    float x, y, z;
    Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } { }

    // Equality operator 
    bool operator==(const Vector3& other) const {
        // fix the equal operator implementation
        // The equal operator implementation here is just for x and not for y and z 
        return x == other.x && y == other.y && z == other.z;
    }

    // Inequality operator
    bool operator!=(const Vector3& other) const {
        return !(*this == other);// Return the code i wrote on top not to be equal 
        // return x !== other.x && y !== other.y && z !== other.z;Exactly like on the top but top code is cleaner 
    }

    // TODO:
    // Negate Operator
    Vector3 operator-() const { 
        // return new vector where all components are negated
        return Vector3(-x, -y, -z);
    }

    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
        // We do not use && cause it uses for bool and here is not a bool 
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(float k) const {
        return Vector3(x * k, y * k, z * k);
    }

    Vector3 operator/(float k) const {
        return Vector3(x / k, y / k, z / k);
    }

    float Magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }


};
