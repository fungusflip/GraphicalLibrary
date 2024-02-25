#pragma once
#include <cmath>

class Vector3 {
public:
    float x, y, z;

    // Constructors
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    // Vector addition
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    // Vector subtraction
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication
    Vector3 operator*(float k) const {
        return Vector3(x * k, y * k, z * k);
    }

    // Scalar division
    Vector3 operator/(float k) const {
        return Vector3(x / k, y / k, z / k);
    }

    // Dot product
    static float Dot(const Vector3& v1, const Vector3& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    // Cross product
    static Vector3 Cross(const Vector3& v1, const Vector3& v2) {
        return Vector3(
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
        );
    }

    // Magnitude calculation
    float Magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Normalization
    Vector3 Normalize() const {
        float mag = Magnitude();
        if (mag != 0) {
            return *this / mag;
        }
        return *this; // Prevent division by zero
    }
};
    