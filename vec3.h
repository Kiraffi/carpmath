#pragma once

#include "vec2.h"
#include "uninittype.h"

struct alignas(16) Vec3
{
    Vec3() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    Vec3(UninitType) {}
    Vec3(float f) : x(f), y(f), z(f), w(0.0f) {}

    Vec3(const Vec2 &a, float b) : x(a.x), y(a.y), z(b), w(0.0f) {}
    Vec3(float b, const Vec2 &a) : x(b), y(a.x), z(a.y), w(0.0f) {}

    Vec3(float x, float y, float z) : x(x), y(y), z(z), w(0.0f) {}

    float &operator[](int index) { return (&x)[index]; }

    float x;
    float y;
    float z;
    float w;
};

Vec3 operator+(const Vec3 &a, const Vec3 &b);
Vec3 operator+(const Vec3 &a, float value);
Vec3 operator+(float value, const Vec3 &a);
Vec3 operator-(const Vec3 &a);
Vec3 operator-(const Vec3 &a, const Vec3 &b);
Vec3 operator-(const Vec3 &a, float value);
Vec3 operator*(const Vec3 &a, float value);
Vec3 operator*(float value, const Vec3 &a);
Vec3 operator*(const Vec3 &a, const Vec3 &b);
Vec3 operator/(const Vec3 &a, float value);
Vec3 operator/(const Vec3 &a, const Vec3 &b);
Vec3 operator/(float value, const Vec3 &a);
Vec3 min(const Vec3 &v1, const Vec3 &v2);
Vec3 max(const Vec3 &v1, const Vec3 &v2);
float min(const Vec3 &v1);
float max(const Vec3 &v1);
float dot(const Vec3 &a, const Vec3 &b);
float sqrLen(const Vec3 &a);
float len(const Vec3 &a);
Vec3 lerp(const Vec3 &a, const Vec3 &b, float t);
Vec3 normalize(const Vec3 &a);
Vec3 cross(const Vec3 &a, const Vec3 &b);
Vec3 proj(const Vec3 &a, const Vec3 &b);
Vec3 reject(const Vec3 &a, const Vec3 &b);
