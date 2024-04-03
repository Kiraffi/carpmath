#pragma once

#include "uninittype.h"

struct Vec2
{
    Vec2(): x(0.0f), y(0.0f) {}
    Vec2(UninitType) {}
    Vec2(float f) : x(f), y(f) {}

    Vec2(float x, float y) : x(x), y(y) {}
    float x;
    float y;

    float &operator[](int index) { return (&x)[index]; }
};

Vec2 operator+(const Vec2 &a, const Vec2 &b);
Vec2 operator+(const Vec2 &a, float value);
Vec2 operator+(float value, const Vec2 &a);
Vec2 operator-(const Vec2 &a);
Vec2 operator-(const Vec2 &a, const Vec2 &b);
Vec2 operator-(const Vec2 &a, float value);
Vec2 operator*(const Vec2 &a, float value);
Vec2 operator*(float value, const Vec2 &a);
Vec2 operator*(const Vec2 &a, const Vec2 &b);
Vec2 operator/(const Vec2 &a,float value);
Vec2 operator/(const Vec2 &a, const Vec2 &b);
Vec2 operator/(float value, const Vec2 &a);
Vec2 min(const Vec2 &v1, const Vec2 &v2);
Vec2 max(const Vec2 &v1, const Vec2 &v2);
float min(const Vec2 &v1);
float max(const Vec2 &v1);
float dot(const Vec2 &a, const Vec2 &b);
float sqrLen(const Vec2 &a);
float len(const Vec2 &a);
Vec2 lerp(const Vec2 &a, const Vec2 &b, float t);
Vec2 normalize(const Vec2 &a);
