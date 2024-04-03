#pragma once

#include "vec3.h"
#include "uninittype.h"

struct alignas(16) Vec4
{
    Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    Vec4(UninitType) {}
    Vec4(float f) : x(f), y(f), z(f), w(f) {}
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    Vec4(const Vec2 &a, const Vec2 &b) : x(a.x), y(a.y), z(b.x), w(b.y) {}
    Vec4(const Vec2 &a, float b, float c) : x(a.x), y(a.y), z(b), w(c) {}
    Vec4(float b, const Vec2 &a, float c) : x(b), y(a.x), z(a.y), w(c) {}
    Vec4(float b, float c, const Vec2 &a) : x(b), y(c), z(a.x), w(a.y) {}

    Vec4(float b, const Vec3 &a) : x(b), y(a.x), z(a.y), w(a.z) {}
    Vec4(const Vec3 &a, float b) : x(a.x), y(a.y), z(a.z), w(b) {}


    float x;
    float y;
    float z;
    float w;

    float &operator[](int index) { return ( &x )[ index ]; }
};

Vec4 operator+(const Vec4 &a, const Vec4 &b);
Vec4 operator+(const Vec4 &a, float value);
Vec4 operator+(float value, const Vec4 &a);
Vec4 operator-(const Vec4 &a);
Vec4 operator-(const Vec4 &a, const Vec4 &b);
Vec4 operator-(const Vec4 &a, float value);
Vec4 operator*(const Vec4 &a, float value);
Vec4 operator*(float value, const Vec4 &a);
Vec4 operator*(const Vec4 &a, const Vec4 &b);
Vec4 operator/(const Vec4 &a, float value);
Vec4 operator/(const Vec4 &a, const Vec4 &b);
Vec4 operator/(float value, const Vec4 &a);
Vec4 min(const Vec4 &v1, const Vec4 &v2);
Vec4 max(const Vec4 &v1, const Vec4 &v2);
float min(const Vec4 &v1);
float max(const Vec4 &v1);
float dot(const Vec4 &a, const Vec4 &b);
float sqrLen(const Vec4 &a);
float len(const Vec4 &a);
Vec4 lerp(const Vec4 &a, const Vec4 &b, float t);
Vec4 normalize(const Vec4 &a);
