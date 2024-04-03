#include "vec4.h"

#include "mathhelp.h"

Vec4 operator+(const Vec4 &a, const Vec4 &b)
{
    Vec4 result{UninitType{} };
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;
    return result;
}
Vec4 operator+(const Vec4 &a, float value)
{
    Vec4 result{UninitType{} };
    result.x = a.x + value;
    result.y = a.y + value;
    result.z = a.z + value;
    result.w = a.w + value;
    return result;
}
Vec4 operator+(float value, const Vec4 &a)
{
    return a + value;
}


Vec4 operator-(const Vec4 &a)
{
    Vec4 result{UninitType{} };
    result.x = -a.x;
    result.y = -a.y;
    result.z = -a.z;
    result.w = -a.w;
    return result;
}


Vec4 operator-(const Vec4 &a, const Vec4 &b)
{
    Vec4 result{UninitType{} };
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;
    return result;
}

Vec4 operator-(const Vec4 &a, float value)
{
    Vec4 result{UninitType{} };
    result.x = a.x - value;
    result.y = a.y - value;
    result.z = a.z - value;
    result.w = a.w - value;
    return result;
}

Vec4 operator*(const Vec4 &a, float value)
{
    Vec4 result{UninitType{} };
    result.x = a.x * value;
    result.y = a.y * value;
    result.z = a.z * value;
    result.w = a.w * value;
    return result;
}

Vec4 operator*(float value, const Vec4 &a)
{
    Vec4 result{UninitType{} };
    result.x = a.x * value;
    result.y = a.y * value;
    result.z = a.z * value;
    result.w = a.w * value;
    return result;
}

Vec4 operator*(const Vec4 &a, const Vec4 &b)
{
    Vec4 result{UninitType{} };
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;
    result.w = a.w * b.w;
    return result;
}


Vec4 operator/(const Vec4 &a, float value)
{
    Vec4 result{UninitType{} };
    result.x = a.x / value;
    result.y = a.y / value;
    result.z = a.z / value;
    result.w = a.w / value;
    return result;
}

Vec4 operator/(const Vec4 &a, const Vec4 &b)
{
    Vec4 result{UninitType{} };
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    result.z = a.z / b.z;
    result.w = a.w / b.w;
    return result;
}

Vec4 operator/(float value, const Vec4 &a)
{
    Vec4 result{UninitType{} };
    result.x = value / a.x;
    result.y = value / a.y;
    result.z = value / a.z;
    result.w = value / a.w;
    return result;
}

Vec4 minVec(const Vec4 &v1, const Vec4 &v2)
{
    Vec4 result{UninitType{} };
    result.x = sMinF(v1.x, v2.x);
    result.y = sMinF(v1.y, v2.y);
    result.z = sMinF(v1.z, v2.z);
    result.w = sMinF(v1.w, v2.w);
    return result;
}

Vec4 maxVec(const Vec4 &v1, const Vec4 &v2)
{
    Vec4 result{UninitType{} };
    result.x = sMaxF(v1.x, v2.x);
    result.y = sMaxF(v1.y, v2.y);
    result.z = sMaxF(v1.z, v2.z);
    result.w = sMaxF(v1.w, v2.w);
    return result;
}

float minVec(const Vec4 &v1)
{
    return sMinF(sMinF(v1.z, v1.w), sMinF(v1.x, v1.y));
}

float maxVec(const Vec4 &v1)
{
    return sMaxF(sMaxF(v1.z, v1.w), sMaxF(v1.x, v1.y));
}

float dot(const Vec4 &a, const Vec4 &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}


float sqrLen(const Vec4 &a)
{
    return dot(a, a);
}

float len(const Vec4 &a)
{
    return sSqrtF(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}

Vec4 lerp(const Vec4 &a, const Vec4 &b, float t)
{
    Vec4 result{ UninitType{} };
    result.x = a.x + (b.x - a.x) * t;
    result.y = a.y + (b.y - a.y) * t;
    result.z = a.z + (b.z - a.z) * t;
    result.w = a.w + (b.w - a.w) * t;
    return result;
}

Vec4 normalize(const Vec4 &a)
{
    float l2 = sqrLen(a);
    if(l2 < 1.0e-8f)
    {
        DEBUG_BREAK_MACRO_MATH();
        return {};
    }
    float l = sSqrtF(l2);
    float perLen = 1.0f / l;
    return Vec4(a.x * perLen, a.y * perLen, a.z * perLen, a.w * perLen);
}

