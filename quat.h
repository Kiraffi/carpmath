#pragma once

#include "uninittype.h"
#include "vec3.h"

struct alignas(16) Quat
{
    Quat() : vx(0.0f), vy(0.0f), vz(0.0f), w(1.0f) {}
    Quat(UninitType) {}
    Quat(const Vec3 &v, float w) : vx(v.x), vy(v.y), vz(v.z), w(w) {}
    Quat(float x, float y, float z, float w) : vx(x), vy(y), vz(z), w(w) {}
    float vx;
    float vy;
    float vz;
    float w;
};

float dot(const Quat &q1, const Quat &q2);
Quat operator *(const Quat &a, const Quat &b);
Quat normalize(const Quat &q);
Quat conjugate(const Quat &q);
Vec3 rotateVector(const Vec3 &v, const Quat &q);
void getAxis(const Quat &quat, Vec3 &right, Vec3 &up, Vec3 &forward);
Quat getQuatFromAxisAngle(const Vec3 &v, float angle);
Quat getQuatFromNormalizedVectors(const Vec3 &from, const Vec3 &toVector);
Quat operator*(const Quat &q, float t);
Quat operator*(float t, const Quat &q);
Quat lerp(Quat const &q1, Quat const &q2, float t);
Quat slerp(Quat const &q1, Quat const &q2, float t);
void getDirectionsFromPitchYawRoll(
    float pitch, float yaw, float roll, Vec3 &rightDir, Vec3 &upDir, Vec3 &forwardDir);


