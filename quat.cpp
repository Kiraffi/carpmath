#pragma once

#include "quat.h"
#include "mathhelp.h"

static Quat operator -(const Quat &v)
{
    return Quat(-v.vx, -v.vy, -v.vz, -v.w);
}

static Quat operator +(const Quat &a, const Quat &b)
{
    return Quat(a.vx + b.vx, a.vy + b.vy, a.vz + b.vz, a.w + b.w);
}

static Quat operator -(const Quat &a, const Quat &b)
{
    return Quat(a.vx - b.vx, a.vy - b.vy, a.vz - b.vz, a.w - b.w);
}

float dot(const Quat &q1, const Quat &q2)
{
    return q1.vx * q2.vx + q1.vy * q2.vy + q1.vz * q2.vz + q1.w * q2.w;
}




Quat operator *(const Quat &a, const Quat &b)
{
    Vec3 av(a.vx, a.vy, a.vz);
    Vec3 bv(b.vx, b.vy, b.vz);
    return Quat(cross(av, bv) + a.w * bv + b.w * av, a.w * b.w - dot(av, bv));
}

Quat normalize(const Quat &q)
{
    float sqrLength = q.vx * q.vx + q.vy * q.vy + q.vz * q.vz + q.w * q.w;
    if(sqrLength < 1.0e-8f)
    {
        DEBUG_BREAK_MACRO_MATH();
        return Quat();
    }
    float length = 1.0f / sSqrtF(sqrLength);
    return q * length;
}

Quat conjugate(const Quat &q)
{
    return Quat(-q.vx, -q.vy, -q.vz, q.w);
}

Vec3 rotateVector(const Vec3 &v, const Quat &q)
{
    Vec3 qv(q.vx, q.vy, q.vz);
    float d = sqrLen(qv);
    return (v * (q.w * q.w - d) + 2.0f * (qv * dot(v, qv) + cross(qv, v) * q.w));
}

void getAxis(const Quat &quat, Vec3 &right, Vec3 &up, Vec3 &forward)
{
    right.x = 1.0f - 2.0f * quat.vy * quat.vy - 2.0f * quat.vz * quat.vz;
    right.y = 2.0f * quat.vx * quat.vy + 2.0f * quat.w * quat.vz;
    right.z = 2.0f * quat.vx * quat.vz - 2.0f * quat.w * quat.vy;

    up.x = 2.0f * quat.vx * quat.vy - 2.0f * quat.w * quat.vz;
    up.y = 1.0f - 2.0f * quat.vx * quat.vx - 2.0f * quat.vz * quat.vz;
    up.z = 2.0f * quat.vy * quat.vz + 2.0f * quat.w * quat.vx;

    forward.x = 2.0f * quat.vx * quat.vz + 2.0f * quat.w * quat.vy;
    forward.y = 2.0f * quat.vy * quat.vz - 2.0f * quat.w * quat.vx;
    forward.z = 1.0f - 2.0f * quat.vx * quat.vx - 2.0f * quat.vy * quat.vy;

}


Quat getQuatFromAxisAngle(const Vec3 &v, float angle)
{
    float s = sSinF(angle * 0.5f);
    Vec3 v2 = normalize(v) * s;
    Quat result(v2.x, v2.y, v2.z, sCosF(angle * 0.5f));
    return result;
}

Quat getQuatFromNormalizedVectors(const Vec3 &from, const Vec3 &toVector)
{
    float d = dot(from, toVector);
    if(d >= 1.0f - 1e-5f)
        return Quat();

    else if(d <= -1.0f + 1e-5f)
    {
        // Generate a rotation axis to do 180 degree rotation
        if(sAbsF(from.x) < 0.707f)
            return getQuatFromAxisAngle(normalize(cross(Vec3(1.0f, 0.0f, 0.0f), from)), PI);
        else
            return getQuatFromAxisAngle(normalize(cross(Vec3(0.0f, 1.0f, 0.0f), from)), PI);
    }
    else
    {
        float s = sSqrtF((1.0f + d) * 2.0f);
        Vec3 v = cross(from, toVector);
        return normalize(Quat(v.x, v.y, v.z, 0.5f* s));
    }
}

Quat operator*(const Quat &q, float t)
{
    return Quat(q.vx * t, q.vy * t, q.vz * t, q.w * t);
}

Quat operator*(float t, const Quat &q)
{
    return q * t;
}

Quat lerp(Quat const &q1, Quat const &q2, float t)
{
    float dotAngle = dot(q1, q2);
    Quat result(UninitType{});
    if (dotAngle < 0.0f)
    {
        result.vx = q1.vx - t * (q1.vx + q2.vx);
        result.vy = q1.vy - t * (q1.vy + q2.vy);
        result.vz = q1.vz - t * (q1.vz + q2.vz);
        result.w = q1.w - t * (q1.w + q2.w);
    }
    else
    {
        result.vx = q1.vx - t * (q1.vx - q2.vx);
        result.vy = q1.vy - t * (q1.vy - q2.vy);
        result.vz = q1.vz - t * (q1.vz - q2.vz);
        result.w = q1.w - t * (q1.w - q2.w);
    }
    return result;
}

Quat slerp(Quat const &q1, Quat const &q2, float t)
{
    float dotAngle = dot(q1, q2);

    if (dotAngle < 0.0f)
    {
        dotAngle = -dotAngle;
    }
    if (dotAngle > 0.9995)
    {
        return normalize(lerp(q1, q2, t));
    }

    float theta0 = sCosF(dotAngle);
    float theta = theta0 * t;

    float sinTheta = sSinF(theta);
    float sinTheta0 = sSinF(theta0);

    float s2 = sinTheta / sinTheta0;
    float s1 = sCosF(theta) - dotAngle * s2;

    return normalize(Quat(
        q1.vx * s1 + q2.vx * s2,
        q1.vy * s1 + q2.vy * s2,
        q1.vz * s1 + q2.vz * s2,
        q1.w * s1 + q2.w * s2));
}

void getDirectionsFromPitchYawRoll(
    float pitch, float yaw, float roll, Vec3 &rightDir, Vec3 &upDir, Vec3 &forwardDir)
{
    Quat rotation = getQuatFromAxisAngle(Vec3(0.0f, 0.0f, 1.0f), roll);
    rotation = getQuatFromAxisAngle(Vec3(1.0f, 0.0f, 0.0f), pitch) * rotation;
    rotation = getQuatFromAxisAngle(Vec3(0.0f, 1.0f, 0.0f), yaw) * rotation;

    rightDir = rotateVector(Vec3(1.0f, 0.0, 0.0f), rotation);
    upDir = rotateVector(Vec3(0.0, 1.0, 0.0f), rotation);
    forwardDir = rotateVector(Vec3(0.0, 0.0, 1.0f), rotation);
}


