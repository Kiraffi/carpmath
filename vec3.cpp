#include "vec3.h"

#include "mathhelp.h"

Vec3 operator+(const Vec3 &a, const Vec3 &b)
{
    Vec3 result{UninitType{} };
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;
    return result;
}
Vec3 operator+(const Vec3 &a, float value)
{
    Vec3 result{UninitType{} };
    result.x = a.x + value;
    result.y = a.y + value;
    result.z = a.z + value;
    result.w = a.w + value;
    return result;
}
Vec3 operator+(float value, const Vec3 &a)
{
    return a + value;
}


Vec3 operator-(const Vec3 &a)
{
    Vec3 result{UninitType{} };
    result.x = -a.x;
    result.y = -a.y;
    result.z = -a.z;
    result.w = -a.w;
    return result;
}


Vec3 operator-(const Vec3 &a, const Vec3 &b)
{
    Vec3 result{UninitType{} };
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;
    return result;
}

Vec3 operator-(const Vec3 &a, float value)
{
    Vec3 result{UninitType{} };
    result.x = a.x - value;
    result.y = a.y - value;
    result.z = a.z - value;
    result.w = a.w - value;
    return result;
}

Vec3 operator*(const Vec3 &a, float value)
{
    Vec3 result{UninitType{} };
    result.x = a.x * value;
    result.y = a.y * value;
    result.z = a.z * value;
    result.w = a.w * value;
    return result;
}

Vec3 operator*(float value, const Vec3 &a)
{
    Vec3 result{UninitType{} };
    result.x = a.x * value;
    result.y = a.y * value;
    result.z = a.z * value;
    result.w = a.w * value;
    return result;
}

Vec3 operator*(const Vec3 &a, const Vec3 &b)
{
    Vec3 result{UninitType{} };
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;
    result.w = a.w * b.w;
    return result;
}


Vec3 operator/(const Vec3 &a, float value)
{
    Vec3 result{UninitType{} };
    result.x = a.x / value;
    result.y = a.y / value;
    result.z = a.z / value;
    result.w = a.w / value;
    return result;
}

Vec3 operator/(const Vec3 &a, const Vec3 &b)
{
    Vec3 result{UninitType{} };
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    result.z = a.z / b.z;
    result.w = a.w / b.w;
    return result;
}

Vec3 operator/(float value, const Vec3 &a)
{
    Vec3 result{UninitType{} };
    result.x = value / a.x;
    result.y = value / a.y;
    result.z = value / a.z;
    result.w = value / a.w;
    return result;
}

Vec3 minVec(const Vec3 &v1, const Vec3 &v2)
{
    Vec3 result{UninitType{} };
    result.x = sMinF(v1.x, v2.x);
    result.y = sMinF(v1.y, v2.y);
    result.z = sMinF(v1.z, v2.z);
    result.w = sMinF(v1.w, v2.w);
    return result;
}

Vec3 maxVec(const Vec3 &v1, const Vec3 &v2)
{
    Vec3 result{UninitType{} };
    result.x = sMaxF(v1.x, v2.x);
    result.y = sMaxF(v1.y, v2.y);
    result.z = sMaxF(v1.z, v2.z);
    result.w = sMaxF(v1.w, v2.w);
    return result;
}
float minVec(const Vec3 &v1)
{
    return sMinF(v1.z, sMinF(v1.x, v1.y));
}

float maxVec(const Vec3 &v1)
{
    return sMaxF(v1.z, sMaxF(v1.x, v1.y));
}


float dot(const Vec3 &a, const Vec3 &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float sqrLen(const Vec3 &a)
{
    return dot(a, a);
}

float len(const Vec3 &a)
{
    return sSqrtF(a.x * a.x + a.y * a.y + a.z * a.z);
}

Vec3 lerp(const Vec3 &a, const Vec3 &b, float t)
{
    Vec3 result{UninitType{} };
    result.x = a.x + (b.x - a.x) * t;
    result.y = a.y + (b.y - a.y) * t;
    result.z = a.z + (b.z - a.z) * t;
    result.w = 0.0f;
    return result;
}

Vec3 normalize(const Vec3 &a)
{
    float l2 = sqrLen(a);
    if(l2 < 1.0e-8f)
    {
        DEBUG_BREAK_MACRO_MATH();
        return {};
    }
    float l = sSqrtF(l2);
    float perLen = 1.0f / l;
    return {a.x * perLen, a.y * perLen, a.z * perLen};
}



Vec3 cross(const Vec3 &a, const Vec3 &b)
{
    Vec3 result{UninitType{} };
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    result.w = 0.0f;
    return result;
}

Vec3 proj(const Vec3 &a, const Vec3 &b)
{
    return b * (dot(a, b) / dot(b, b));
}

Vec3 reject(const Vec3 &a, const Vec3 &b)
{
    return a - proj(a, b);
}
