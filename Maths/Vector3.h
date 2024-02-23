#pragma once

#include <cmath> // Include the cmath header for math functions

class Vector3
{
public:
    float x, y, z;

    // Constructor
    Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}

    // Equality operator 
    bool operator==(const Vector3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    // Inequality operator
    bool operator!=(const Vector3& other) const {
        return !(*this == other);
    }

    // Negate Operator
    Vector3 operator-() const {
        return Vector3(-x, -y, -z);
    }

    // Addition operator
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    // Subtraction operator
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication operator
    Vector3 operator*(float k) const {
        return Vector3(x * k, y * k, z * k);
    }

    // Scalar division operator
    Vector3 operator/(float k) const {
        return Vector3(x / k, y / k, z / k);
    }

    // Magnitude calculation
    float Magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Normalize method
    Vector3 Normalize() const {
        float mag = Magnitude();
        if (mag != 0) {
            return *this / mag;
        }
        return *this; // Prevent division by zero
    }

    // Dot product method
    float Dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
};
