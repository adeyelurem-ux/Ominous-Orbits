//
// Created by Michael Adeyelure on 06/09/2026.
//

#ifndef OMINOUS_ORBITS_VECTOR3_H
#define OMINOUS_ORBITS_VECTOR3_H

#include <iostream>

struct Vector3 {
    double x = 0;
    double y = 0;
    double z = 0;

    constexpr Vector3() = default;
    constexpr Vector3(const double x, const double y, const double z) : x(x), y(y), z(z){}


    constexpr Vector3& operator+=(const Vector3& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;

        return *this;
    }


    constexpr Vector3& operator-=(const Vector3& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;

        return *this;
    }


    constexpr Vector3& operator*=(const double scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;

        return *this;
    }


    constexpr Vector3& operator/=(const double scalar) {
        const double inv = 1.0 / scalar;

        *this *= inv;
        return *this;
    }


    [[nodiscard]] friend constexpr Vector3 operator+(Vector3 lhs, const Vector3& rhs) {
        return lhs += rhs;
    }


    [[nodiscard]] friend constexpr Vector3 operator-(Vector3 lhs, const Vector3& rhs) {
        return lhs -= rhs;
    }


    [[nodiscard]] friend constexpr Vector3 operator*(Vector3 lhs, const double scalar) {
        return lhs *= scalar;
    }


    [[nodiscard]] friend constexpr Vector3 operator*(const double scalar, Vector3 rhs) {
        return rhs *= scalar;
    }


    [[nodiscard]] friend constexpr Vector3 operator/(Vector3 lhs, const double scalar) {
        return lhs /= scalar;
    }


    [[nodiscard]] constexpr double dot(const Vector3& rhs) const {
        return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
    }


    [[nodiscard]] friend constexpr double dot(const Vector3& lhs, const Vector3& rhs) {
        return lhs.dot(rhs);
    }


    [[nodiscard]] constexpr Vector3 cross(const Vector3& rhs) const {
        return Vector3{
            y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x
        };
    }


    [[nodiscard]] friend constexpr double mod_sqd(const Vector3& v) {
        return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
    }


    [[nodiscard]] constexpr Vector3 along(const Vector3& b) const {
       return (this->dot(b) / mod_sqd(b)) * b;
    }


    [[nodiscard]] constexpr Vector3 along_unit(const Vector3& u) const {
        return (this->dot(u) * u);
    }


    friend std::ostream& operator<<(std::ostream& os, const Vector3& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
};

#endif //OMINOUS_ORBITS_VECTOR3_H
