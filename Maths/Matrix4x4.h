#pragma once
#include "Vector3.h"
#include "cmath"

struct Matrix4x4;
Matrix4x4 operator *(const Matrix4x4& a, const Matrix4x4& b);

struct Matrix4x4 {
    float m11, m12, m13, m14;
    float m21, m22, m23, m24;
    float m31, m32, m33, m34;
    float m41, m42, m43, m44;

    Matrix4x4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
        : m11{ m11 }, m12{ m12 }, m13{ m13 }, m14{ m14 },
        m21{ m21 }, m22{ m22 }, m23{ m23 }, m24{ m24 },
        m31{ m31 }, m32{ m32 }, m33{ m33 }, m34{ m34 },
        m41{ m41 }, m42{ m42 }, m43{ m43 }, m44{ m44 }
    {}

    static Matrix4x4 Identity() {
        return Matrix4x4(1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);
    }

    static Vector3 Transform(const Matrix4x4& m, const Vector3& v, float w = 1) {
        return Vector3(m.m11 * v.x + m.m12 * v.y + m.m13 * v.z + m.m14 * w,
            m.m21 * v.x + m.m22 * v.y + m.m23 * v.z + m.m24 * w,
            m.m31 * v.x + m.m32 * v.y + m.m33 * v.z + m.m34 * w);
    }

    static Matrix4x4 Translation(const Vector3& translation) {
        auto result = Identity();
        result.m14 = translation.x;
        result.m24 = translation.y;
        result.m34 = translation.z;
        return result;
    }

    static Matrix4x4 Scale(const Vector3& scale) {
        auto result = Identity();
        result.m11 = scale.x;
        result.m22 = scale.y;
        result.m33 = scale.z;
        return result;
    }

    static Matrix4x4 RotationX(float x) {
        auto result = Identity();
        result.m22 = cosf(x);
        result.m23 = -sinf(x);
        result.m32 = sinf(x);
        result.m33 = cosf(x);
        return result;
    }

    static Matrix4x4 RotationY(float y) {
        auto result = Identity();
        result.m11 = cosf(y);
        result.m31 = -sinf(y);
        result.m13 = sinf(y);
        result.m33 = cosf(y);
        return result;
    }

    static Matrix4x4 RotationZ(float z) {
        auto result = Identity();
        result.m11 = cosf(z);
        result.m12 = -sinf(z);
        result.m21 = sinf(z);
        result.m22 = cosf(z);
        return result;
    }

    static Matrix4x4 Rotation(const Vector3& rotation) {
        return RotationZ(rotation.z) * RotationY(rotation.y) * RotationX(rotation.x);
    }

    static Matrix4x4 Perspective(float fov, float aspectRatio, float nearPlane, float farPlane)
    {
        float yScale = 1.0f / tanf(fov * 0.5f);
        float xScale = yScale / aspectRatio;
        float Q = farPlane / (farPlane - nearPlane);

        return Matrix4x4(xScale, 0.0f, 0.0f, 0.0f,
            0.0f, yScale, 0.0f, 0.0f,
            0.0f, 0.0f, Q, Q * nearPlane,
            0.0f, 0, -1, 0.0f);
    }

    static Matrix4x4 LookAt(const Vector3& eye, const Vector3& target, const Vector3& up) {
        Vector3 zAxis = (eye - target).Normalize();
        Vector3 xAxis = Vector3::Cross(up, zAxis).Normalize();
        Vector3 yAxis = Vector3::Cross(zAxis, xAxis);

        Matrix4x4 viewMatrix(
            xAxis.x, yAxis.x, zAxis.x, 0,
            xAxis.y, yAxis.y, zAxis.y, 0,
            xAxis.z, yAxis.z, zAxis.z, 0,
            -Vector3::Dot(xAxis, eye), -Vector3::Dot(yAxis, eye), -Vector3::Dot(zAxis, eye), 1
        );

        return viewMatrix;
    }

};


inline Matrix4x4 operator *(const Matrix4x4& a, const Matrix4x4& b) {
    return Matrix4x4(
        b.m11 * a.m11 + b.m21 * a.m12 + b.m31 * a.m13 + b.m41 * a.m14,
        b.m12 * a.m11 + b.m22 * a.m12 + b.m32 * a.m13 + b.m42 * a.m14,
        b.m13 * a.m11 + b.m23 * a.m12 + b.m33 * a.m13 + b.m43 * a.m14,
        b.m14 * a.m11 + b.m24 * a.m12 + b.m34 * a.m13 + b.m44 * a.m14,

        b.m11 * a.m21 + b.m21 * a.m22 + b.m31 * a.m23 + b.m41 * a.m24,
        b.m12 * a.m21 + b.m22 * a.m22 + b.m32 * a.m23 + b.m42 * a.m24,
        b.m13 * a.m21 + b.m23 * a.m22 + b.m33 * a.m23 + b.m43 * a.m24,
        b.m14 * a.m21 + b.m24 * a.m22 + b.m34 * a.m23 + b.m44 * a.m24,

        b.m11 * a.m31 + b.m21 * a.m32 + b.m31 * a.m33 + b.m41 * a.m34,
        b.m12 * a.m31 + b.m22 * a.m32 + b.m32 * a.m33 + b.m42 * a.m34,
        b.m13 * a.m31 + b.m23 * a.m32 + b.m33 * a.m33 + b.m43 * a.m34,
        b.m14 * a.m31 + b.m24 * a.m32 + b.m34 * a.m33 + b.m44 * a.m34,

        b.m11 * a.m41 + b.m21 * a.m42 + b.m31 * a.m43 + b.m41 * a.m44,
        b.m12 * a.m41 + b.m22 * a.m42 + b.m32 * a.m43 + b.m42 * a.m44,
        b.m13 * a.m41 + b.m23 * a.m42 + b.m33 * a.m43 + b.m43 * a.m44,
        b.m14 * a.m41 + b.m24 * a.m42 + b.m34 * a.m43 + b.m44 * a.m44);
}

inline Vector3 operator *(const Matrix4x4& m, const Vector3& v) {
    return Vector3(m.m11 * v.x + m.m12 * v.y + m.m13 * v.z + m.m14 * 1,
        m.m21 * v.x + m.m22 * v.y + m.m23 * v.z + m.m24 * 1,
        m.m31 * v.x + m.m32 * v.y + m.m33 * v.z + m.m34 * 1);
}