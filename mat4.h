#pragma once

#include "quat.h"
#include "uninittype.h"
#include "vec3.h"
#include "vec4.h"

// The matrices are used mostly in row order where
// row 0 = x vec, transpose.x
// row 1 = y vec, transpose.y
// row 2 = z vec, transpose.z
// row 3 = projection stuff.
// It makes easy to convert to 4x3 or from 4x3 to 4x4,
// since no need to transpose and shaders use rowmatrix,
// so its direct copy.
struct alignas(16) Mat3x4;

struct alignas(16) Mat4x4
{
    Mat4x4() :
        _00(1.0f), _01(0.0f), _02(0.0f), _03(0.0f),
        _10(0.0f), _11(1.0f), _12(0.0f), _13(0.0f),
        _20(0.0f), _21(0.0f), _22(1.0f), _23(0.0f),
        _30(0.0f), _31(0.0f), _32(0.0f), _33(1.0f) {}
    Mat4x4(UninitType) {}

    Mat4x4(
        float f00, float f01, float f02, float f03,
        float f10, float f11, float f12, float f13,
        float f20, float f21, float f22, float f23,
        float f30, float f31, float f32, float f33)
        : _00(f00), _01(f01), _02(f02), _03(f03)
          , _10(f10), _11(f11), _12(f12), _13(f13)
          , _20(f20), _21(f21), _22(f22), _23(f23)
          , _30(f30), _31(f31), _32(f32), _33(f33)
    {}
    Mat4x4(const Mat3x4 &mat);

    float &operator[](int index) { return (&_00)[index]; }
    float operator[](int index) const { return (&_00)[index]; }

    float _00;
    float _01;
    float _02;
    float _03;

    float _10;
    float _11;
    float _12;
    float _13;

    float _20;
    float _21;
    float _22;
    float _23;

    float _30;
    float _31;
    float _32;
    float _33;

};

struct alignas(16) Mat3x4
{
    Mat3x4() :
        _00(1.0f), _01(0.0f), _02(0.0f), _03(0.0f),
        _10(0.0f), _11(1.0f), _12(0.0f), _13(0.0f),
        _20(0.0f), _21(0.0f), _22(1.0f), _23(0.0f) {}
    Mat3x4(UninitType) {}

    Mat3x4(
        float f00, float f01, float f02, float f03,
        float f10, float f11, float f12, float f13,
        float f20, float f21, float f22, float f23)
        : _00(f00), _01(f01), _02(f02), _03(f03)
          , _10(f10), _11(f11), _12(f12), _13(f13)
          , _20(f20), _21(f21), _22(f22), _23(f23)
    {}

    Mat3x4(const Mat4x4 &mat);

    float &operator[](int index) { return (&_00)[index]; }
    float operator[](int index) const { return (&_00)[index]; }

    float _00;
    float _01;
    float _02;
    float _03;

    float _10;
    float _11;
    float _12;
    float _13;

    float _20;
    float _21;
    float _22;
    float _23;
};

Mat3x4 getMat4FromQuaternion(const Quat &quat);
Mat3x4 getMat4FromScale(const Vec3 &scale);
Mat3x4 getMat4FromTranslation(const Vec3 &pos);

Mat4x4 createOrthoMat4(float width, float height, float nearPlane, float farPlane);
Mat4x4 createPerspectiveMat4(float fov, float aspectRatio, float nearPlane, float farPlane);

Mat4x4 createMat4FromLookAt(const Vec3 &pos, const Vec3 &target, const Vec3 &up);

Mat4x4 transpose(const Mat4x4 &m);
Mat4x4 operator*(const Mat4x4 &a, const Mat4x4 &b);

bool operator==(const Mat4x4 &a, const Mat4x4 &b);
Mat4x4 inverse(const Mat4x4 &m);

bool isIdentity(const Mat4x4 &m);


Vec4 operator*(const Mat4x4& m, const Vec4& v);
Vec4 operator*(const Vec4& v, const Mat4x4& m);

Vec4 operator*(const Mat3x4 &m, const Vec4 &v);
Vec4 operator*(const Vec4 &v, const Mat3x4 &m);

Mat4x4 operator*(const Mat4x4 &a, const Mat3x4 &b);
Mat4x4 operator*(const Mat3x4 &a, const Mat4x4 &b);
Mat3x4 operator*(const Mat3x4 &a, const Mat3x4 &b);

