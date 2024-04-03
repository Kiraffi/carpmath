#include "vec2.h"

#include "mathhelp.h"

Vec2 operator+(const Vec2 &a, const Vec2 &b)
{
    Vec2 result{ UninitType{} };
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

Vec2 operator+(const Vec2 &a, float value)
{
    Vec2 result{ UninitType{} };
    result.x = a.x + value;
    result.y = a.y + value;
    return result;
}

Vec2 operator+(float value, const Vec2 &a)
{
    return a + value;
}


Vec2 operator-(const Vec2 &a)
{
    Vec2 result{ UninitType{} };
    result.x = -a.x;
    result.y = -a.y;
    return result;
}


Vec2 operator-(const Vec2 &a, const Vec2 &b)
{
    Vec2 result{ UninitType{} };
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

Vec2 operator-(const Vec2 &a, float value)
{
    Vec2 result{ UninitType{} };
    result.x = a.x - value;
    result.y = a.y - value;
    return result;
}

Vec2 operator*(const Vec2 &a, float value)
{
    Vec2 result{ UninitType{} };
    result.x = a.x * value;
    result.y = a.y * value;
    return result;
}

Vec2 operator*(float value, const Vec2 &a)
{
    Vec2 result{ UninitType{} };
    result.x = a.x * value;
    result.y = a.y * value;
    return result;
}

Vec2 operator*(const Vec2 &a, const Vec2 &b)
{
    Vec2 result{ UninitType{} };
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    return result;
}

Vec2 operator/(const Vec2 &a, float value)
{
    Vec2 result{ UninitType{} };
    result.x = a.x / value;
    result.y = a.y / value;
    return result;
}

Vec2 operator/(const Vec2 &a, const Vec2 &b)
{
    Vec2 result{ UninitType{} };
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    return result;
}

Vec2 operator/(float value, const Vec2 &a)
{
    Vec2 result{ UninitType{} };
    result.x = value / a.x;
    result.y = value / a.y;
    return result;
}


Vec2 minVec(const Vec2 &v1, const Vec2 &v2)
{
    Vec2 result{ UninitType{} };
    result.x = sMinF(v1.x, v2.x);
    result.y = sMinF(v1.y, v2.y);
    return result;
}

Vec2 maxVec(const Vec2 &v1, const Vec2 &v2)
{
    Vec2 result{ UninitType{} };
    result.x = sMaxF(v1.x, v2.x);
    result.y = sMaxF(v1.y, v2.y);
    return result;
}

float minVec(const Vec2 &v1)
{
    return sMinF(v1.x, v1.y);
}

float maxVec(const Vec2 &v1)
{
    return sMaxF(v1.x, v1.y);
}


float dot(const Vec2 &a, const Vec2 &b)
{
    return a.x * b.x + a.y * b.y;
}

float sqrLen(const Vec2 &a)
{
    return dot(a, a);
}

float len(const Vec2 &a)
{
    return sSqrtF(a.x * a.x + a.y * a.y);
}

Vec2 lerp(const Vec2 &a, const Vec2 &b, float t)
{
    Vec2 result{ UninitType{} };
    result.x = a.x + (b.x - a.x) * t;
    result.y = a.y + (b.y - a.y) * t;
    return result;
}


Vec2 normalize(const Vec2 &a)
{
    float l2 = sqrLen(a);
    if(l2 < 1.0e-8f)
    {
        DEBUG_BREAK_MACRO_MATH();
        return {};
    }
    float l = sSqrtF(l2);
    float perLen = 1.0f / l;
    return {a.x * perLen, a.y * perLen};
}

