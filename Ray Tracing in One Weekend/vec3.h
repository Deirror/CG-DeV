#pragma once

#include <iostream>

class vec3 {
public:
    double e[3];

    vec3();
    vec3(double e0, double e1, double e2);

    double x() const;
    double y() const;
    double z() const;

    vec3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);

    vec3& operator+=(const vec3& v);
    vec3& operator*=(double t);
    vec3& operator/=(double t);

    static vec3 random(); 

    static vec3 random(double min, double max);

    double length() const;
    double length_squared() const;

    friend std::ostream& operator<<(std::ostream& out, const vec3& v);
    friend vec3 operator+(const vec3& u, const vec3& v);
    friend vec3 operator-(const vec3& u, const vec3& v);
    friend vec3 operator*(const vec3& u, const vec3& v);
    friend vec3 operator*(double t, const vec3& v);
    friend vec3 operator*(const vec3& v, double t);
    friend vec3 operator/(const vec3& v, double t);
    friend double dot(const vec3& u, const vec3& v);
    friend vec3 cross(const vec3& u, const vec3& v);
    friend vec3 unit_vector(const vec3& v);
    friend vec3 random_unit_vector();
    friend vec3 random_on_hemisphere(const vec3& normal);
};

using point3 = vec3;

std::ostream& operator<<(std::ostream& out, const vec3& v);
vec3 operator+(const vec3& u, const vec3& v);
vec3 operator-(const vec3& u, const vec3& v);
vec3 operator*(const vec3& u, const vec3& v);
vec3 operator*(double t, const vec3& v);
vec3 operator*(const vec3& v, double t);
vec3 operator/(const vec3& v, double t);
double dot(const vec3& u, const vec3& v);
vec3 cross(const vec3& u, const vec3& v);
vec3 unit_vector(const vec3& v);
