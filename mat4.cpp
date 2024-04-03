#include "mat4.h"

#include "mathhelp.h"
#include "quat.h"
#include "transform.h"
#include "vec3.h"
#include "vec4.h"

#include <xmmintrin.h>

Mat4x4::Mat4x4(const Mat3x4 &mat)
    : _00(mat._00), _01(mat._01), _02(mat._02), _03(mat._03)
      , _10(mat._10), _11(mat._11), _12(mat._12), _13(mat._13)
      , _20(mat._20), _21(mat._21), _22(mat._22), _23(mat._23)
      , _30(0.0f), _31(0.0f), _32(0.0f), _33(1.0f)
{}

Mat3x4::Mat3x4(const Mat4x4 &mat)
    : _00(mat._00), _01(mat._01), _02(mat._02), _03(mat._03)
      , _10(mat._10), _11(mat._11), _12(mat._12), _13(mat._13)
      , _20(mat._20), _21(mat._21), _22(mat._22), _23(mat._23)
{
    ASSERT_MATH(mat._30 == 0.0f && mat._31 == 0.0f && mat._32 == 0.0f && mat._33 == 1.0f);
}


Mat4x4 createOrthoMatrix(float width, float height, float nearPlane, float farPlane)
{
    Mat4x4 result;

    ASSERT_MATH(sAbsF(width) >= 1.0f);
    ASSERT_MATH(sAbsF(height) >= 1.0f);
    ASSERT_MATH(sAbsF(farPlane - nearPlane) > 0.00001f);

    float fRange = 1.0f / (farPlane - nearPlane);

    result._00 = 2.0f / width;
    result._11 = 2.0f / height;
    result._22 = fRange;
    result._23 = -fRange * nearPlane;
    result._33 = 1.0f;
    return result;
}

Mat4x4 createPerspectiveMatrix(float fov, float aspectRatio, float nearPlane, float farPlane)
{
    Mat4x4 result;
    ASSERT_MATH(sAbsF(fov) > 0.00001f);
    ASSERT_MATH(sAbsF(aspectRatio) > 0.001f);
    ASSERT_MATH(sAbsF(farPlane - nearPlane) > 0.00001f);
    ASSERT_MATH(sAbsF(nearPlane) > 0.0f);

    float yScale = 1.0f / sTanF(sToRadians(fov * 0.5f));
    float xScale = yScale / aspectRatio;
    float fRange = farPlane / (farPlane - nearPlane);

    result._00 = xScale;
    result._11 = yScale;

    result._22 = -fRange;
    result._23 = -nearPlane * fRange;
    result._32 = -1.0f;
    result._33 = 0.0f;
    return result;
}

Mat4x4 createMatrixFromLookAt(const Vec3 &pos, const Vec3 &target, const Vec3 &up)
{
    const Vec3 forward = -normalize(target - pos);
    const Vec3 right = normalize(cross(up, forward));
    const Vec3 realUp = normalize(cross(forward, right));

    Mat4x4 result(UninitType{});
    result._00 = right.x;
    result._01 = right.y;
    result._02 = right.z;
    result._03 = -dot(pos, right);

    result._10 = realUp.x;
    result._11 = realUp.y;
    result._12 = realUp.z;
    result._13 = -dot(pos, realUp);

    result._20 = forward.x;
    result._21 = forward.y;
    result._22 = forward.z;
    result._23 = -dot(pos, forward);

    result._30 = 0.0;
    result._31 = 0.0;
    result._32 = 0.0;
    result._33 = 1.0;
    return result;
}

bool operator==(const Mat4x4 &a, const Mat4x4 &b)
{
    static constexpr float EPS_DIFF = 5.0e-2f;

    for(int i = 0; i < 16; ++i)
    {
        float f = sAbsF(a[i] - b[i]);
        if(f > EPS_DIFF)
            return false;
    }
    return true;
}

Mat4x4 inverse(const Mat4x4& m)
{
    Mat4x4 inv(UninitType{});
    inv[0] = (
        (m[5]  * m[10] * m[15] - m[5]  * m[11] * m[14]) -
        (m[9]  * m[6]  * m[15] - m[9]  * m[7]  * m[14]) +
        (m[13] * m[6]  * m[11] - m[13] * m[7]  * m[10]));

    inv[1] = -(
        (m[1]  * m[10] * m[15] - m[1]  * m[11] * m[14]) -
        (m[9]  * m[2]  * m[15] - m[9]  * m[3]  * m[14]) +
        (m[13] * m[2]  * m[11] - m[13] * m[3]  * m[10]));

    inv[2] = (
        (m[1]  * m[6] * m[15] - m[1]  * m[7] * m[14]) -
        (m[5]  * m[2] * m[15] - m[5]  * m[3] * m[14]) +
        (m[13] * m[2] * m[7]  - m[13] * m[3] * m[6]));

    inv[3] = -(
        (m[1] * m[6] * m[11] - m[1] * m[7] * m[10]) -
        (m[5] * m[2] * m[11] - m[5] * m[3] * m[10]) +
        (m[9] * m[2] * m[7]  - m[9] * m[3] * m[6]));




    inv[4] = - (
        (m[4]  * m[10] * m[15] - m[4]  * m[11] * m[14]) -
        (m[8]  * m[6]  * m[15] - m[8]  * m[7]  * m[14]) +
        (m[12] * m[6]  * m[11] - m[12] * m[7]  * m[10]));

    inv[5] = (
        (m[0]  * m[10] * m[15] - m[0]  * m[11] * m[14]) -
        (m[8]  * m[2]  * m[15] - m[8]  * m[3]  * m[14]) +
        (m[12] * m[2]  * m[11] - m[12] * m[3]  * m[10]));

    inv[6] = -(
        (m[0] * m[6] * m[15] - m[0] * m[7] * m[14]) -
        (m[4] * m[2] * m[15] - m[4] * m[3] * m[14]) +
        (m[12] * m[2] * m[7] - m[12] * m[3] * m[6]));

    inv[7] = (
        (m[0] * m[6] * m[11] - m[0] * m[7] * m[10]) -
        (m[4] * m[2] * m[11] - m[4] * m[3] * m[10]) +
        (m[8] * m[2] * m[7]  - m[8] * m[3] * m[6]));




    inv[8] = (
        (m[4] * m[9] * m[15] - m[4] * m[11] * m[13]) -
        (m[8] * m[5] * m[15] - m[8] * m[7] * m[13]) +
        (m[12] * m[5] * m[11] - m[12] * m[7] * m[9]));

    inv[9] = -(
        (m[0] * m[9] * m[15] - m[0] * m[11] * m[13]) -
        (m[8] * m[1] * m[15] - m[8] * m[3] * m[13]) +
        (m[12] * m[1] * m[11] - m[12] * m[3] * m[9]));

    inv[10] = (
        (m[0] * m[5] * m[15] - m[0] * m[7] * m[13]) -
        (m[4] * m[1] * m[15] - m[4] * m[3] * m[13]) +
        (m[12] * m[1] * m[7] - m[12] * m[3] * m[5]));

    inv[11] = -(
        (m[0] * m[5] * m[11] - m[0] * m[7] * m[9]) -
        (m[4] * m[1] * m[11] - m[4] * m[3] * m[9]) +
        (m[8] * m[1] * m[7]  - m[8] * m[3] * m[5]));




    inv[12] = -(
        (m[4] * m[9] * m[14] - m[4] * m[10] * m[13]) -
        (m[8] * m[5] * m[14] - m[8] * m[6] * m[13]) +
        (m[12] * m[5] * m[10] - m[12] * m[6] * m[9]));

    inv[13] = (
        (m[0] * m[9] * m[14] - m[0] * m[10] * m[13]) -
        (m[8] * m[1] * m[14] - m[8] * m[2] * m[13]) +
        (m[12] * m[1] * m[10] - m[12] * m[2] * m[9]));

    inv[14] = -(
        (m[0] * m[5] * m[14] - m[0] * m[6] * m[13]) -
        (m[4] * m[1] * m[14] - m[4] * m[2] * m[13]) +
        (m[12] * m[1] * m[6] - m[12] * m[2] * m[5]));

    inv[15] = (
        (m[0] * m[5] * m[10] - m[0] * m[6] * m[9]) -
        (m[4] * m[1] * m[10] - m[4] * m[2] * m[9]) +
        (m[8] * m[1] * m[6]  - m[8] * m[2] * m[5]));

    float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
    {
        return Mat4x4();
    }
    det = 1.0f / det;
    Mat4x4 result{ UninitType{} };
    for (int i = 0; i < 16; i++)
        result[i] = inv[i] * det;

    return result;
}


bool isIdentity(const Mat4x4 &m)
{
    static constexpr float EPS_DIFF = 1.0e-4f;

    for(int i = 0; i < 16; ++i)
    {
        float f = m[i];

        if(i == (i / 4) + (i / 4) * 4)
            f = f - 1.0f;

        if(sAbsF(f) > EPS_DIFF)
            return false;
    }
    return true;
}

Mat3x4 getMatrixFromQuaternion(const Quat &quat)
{
    Mat3x4 result{ UninitType{} };
    float xy2 = 2.0f * quat.vx * quat.vy;
    float xz2 = 2.0f * quat.vx * quat.vz;
    float yz2 = 2.0f * quat.vy * quat.vz;

    float wx2 = 2.0f * quat.w * quat.vx;
    float wy2 = 2.0f * quat.w * quat.vy;
    float wz2 = 2.0f * quat.w * quat.vz;

    float xx2 = 2.0f * quat.vx * quat.vx;
    float yy2 = 2.0f * quat.vy * quat.vy;
    float zz2 = 2.0f * quat.vz * quat.vz;

    result._00 = 1.0f - yy2 - zz2;
    result._01 = xy2 - wz2;
    result._02 = xz2 + wy2;

    result._10 = xy2 + wz2;
    result._11 = 1.0f - xx2 - zz2;
    result._12 = yz2 - wx2;

    result._20 = xz2 - wy2;
    result._21 = yz2 + wx2;
    result._22 = 1.0f - xx2 - yy2;

    result._03 = 0.0f;
    result._13 = 0.0f;
    result._23 = 0.0f;

    return result;
}


Mat3x4 getMatrixFromScale(const Vec3 &scale)
{
    Mat3x4 result;
    result._00 = scale.x;
    result._11 = scale.y;
    result._22 = scale.z;

    return result;
}

Mat3x4 getMatrixFromTranslation(const Vec3 &pos)
{
    Mat3x4 result;
    result._03 = pos.x;
    result._13 = pos.y;
    result._23 = pos.z;

    return result;

}



Mat3x4 getMatrixFromTransform(const Transform &trans)
{
    Mat3x4 result{ UninitType{} };
    float xy2 = 2.0f * trans.rot.vx * trans.rot.vy;
    float xz2 = 2.0f * trans.rot.vx * trans.rot.vz;
    float yz2 = 2.0f * trans.rot.vy * trans.rot.vz;

    float wx2 = 2.0f * trans.rot.w * trans.rot.vx;
    float wy2 = 2.0f * trans.rot.w * trans.rot.vy;
    float wz2 = 2.0f * trans.rot.w * trans.rot.vz;

    float xx2 = 2.0f * trans.rot.vx * trans.rot.vx;
    float yy2 = 2.0f * trans.rot.vy * trans.rot.vy;
    float zz2 = 2.0f * trans.rot.vz * trans.rot.vz;

    result._00 = (1.0f - yy2 - zz2) * trans.scale.x;
    result._01 = (xy2 - wz2) * trans.scale.x;
    result._02 = (xz2 + wy2) * trans.scale.x;

    result._10 = (xy2 + wz2) * trans.scale.y;
    result._11 = (1.0f - xx2 - zz2) * trans.scale.y;
    result._12 = (yz2 - wx2) * trans.scale.y;

    result._20 = (xz2 - wy2) * trans.scale.z;
    result._21 = (yz2 + wx2) * trans.scale.z;
    result._22 = (1.0f - xx2 - yy2) * trans.scale.z;

    result._03 = trans.pos.x;
    result._13 = trans.pos.y;
    result._23 = trans.pos.z;

    return result;
}

 Mat3x4 getInverseMatrixFromTransform(const Transform &trans)
{
    Mat3x4 result{ UninitType{} };
    float xy2 = 2.0f * trans.rot.vx * trans.rot.vy;
    float xz2 = 2.0f * trans.rot.vx * trans.rot.vz;
    float yz2 = 2.0f * trans.rot.vy * trans.rot.vz;

    float wx2 = -2.0f * trans.rot.w * trans.rot.vx;
    float wy2 = -2.0f * trans.rot.w * trans.rot.vy;
    float wz2 = -2.0f * trans.rot.w * trans.rot.vz;

    float xx2 = 2.0f * trans.rot.vx * trans.rot.vx;
    float yy2 = 2.0f * trans.rot.vy * trans.rot.vy;
    float zz2 = 2.0f * trans.rot.vz * trans.rot.vz;

    Vec3 onePerScale = 1.0f / trans.scale;
    // TODO: Is scale xyz, xyz, xyz or xxx, yyy, zzz
    result._00 = (1.0f - yy2 - zz2) * onePerScale.x;
    result._01 = (xy2 - wz2) * onePerScale.y;
    result._02 = (xz2 + wy2) * onePerScale.z;

    result._10 = (xy2 + wz2) * onePerScale.x;
    result._11 = (1.0f - xx2 - zz2) * onePerScale.y;
    result._12 = (yz2 - wx2) * onePerScale.z;

    result._20 = (xz2 - wy2) * onePerScale.x;
    result._21 = (yz2 + wx2) * onePerScale.y;
    result._22 = (1.0f - xx2 - yy2) * onePerScale.z;

    result._03 = -((trans.pos.x * result._00) + (trans.pos.y * result._01) + (trans.pos.z * result._02));
    result._13 = -((trans.pos.x * result._10) + (trans.pos.y * result._11) + (trans.pos.z * result._12));
    result._23 = -((trans.pos.x * result._20) + (trans.pos.y * result._21) + (trans.pos.z * result._22));

    return result;
}




Mat4x4 transpose(const Mat4x4 &m)
{
    Mat4x4 result{ UninitType{} };
    result._00 = m._00;
    result._01 = m._10;
    result._02 = m._20;
    result._03 = m._30;

    result._10 = m._01;
    result._11 = m._11;
    result._12 = m._21;
    result._13 = m._31;

    result._20 = m._02;
    result._21 = m._12;
    result._22 = m._22;
    result._23 = m._32;

    result._30 = m._03;
    result._31 = m._13;
    result._32 = m._23;
    result._33 = m._33;

    return result;
}


Vec4 operator*(const Mat4x4 &m, const Vec4 &v)
{
    Vec4 result{ UninitType{} };
    result.x = v.x * m._00 + v.y * m._01 + v.z * m._02 + v.w * m._03;
    result.y = v.x * m._10 + v.y * m._11 + v.z * m._12 + v.w * m._13;
    result.z = v.x * m._20 + v.y * m._21 + v.z * m._22 + v.w * m._23;
    result.w = v.x * m._30 + v.y * m._31 + v.z * m._32 + v.w * m._33;
    return result;
}

Vec4 operator*(const Vec4 &v, const Mat4x4 &m)
{
    Vec4 result{ UninitType{} };
    result.x = v.x * m._00 + v.y * m._10 + v.z * m._20 + v.w * m._30;
    result.y = v.x * m._01 + v.y * m._11 + v.z * m._21 + v.w * m._31;
    result.z = v.x * m._02 + v.y * m._12 + v.z * m._22 + v.w * m._32;
    result.w = v.x * m._03 + v.y * m._13 + v.z * m._23 + v.w * m._33;
    return result;
}

Vec4 operator*(const Mat3x4 &m, const Vec4 &v)
{
    Vec4 result{ UninitType{} };
    result.x = v.x * m._00 + v.y * m._01 + v.z * m._02 + v.w * m._03;
    result.y = v.x * m._10 + v.y * m._11 + v.z * m._12 + v.w * m._13;
    result.z = v.x * m._20 + v.y * m._21 + v.z * m._22 + v.w * m._23;
    result.w = v.w;
    return result;
}

Vec4 operator*(const Vec4 &v, const Mat3x4 &m)
{
    Vec4 result{ UninitType{} };
    result.x = v.x * m._00 + v.y * m._10 + v.z * m._20;
    result.y = v.x * m._01 + v.y * m._11 + v.z * m._21;
    result.z = v.x * m._02 + v.y * m._12 + v.z * m._22;
    result.w = v.x * m._03 + v.y * m._13 + v.z * m._23 + v.w * 1.0f;
    return result;
}



Mat4x4 operator*(const Mat4x4 &a, const Mat4x4 &b)
{
    Mat4x4 result{ UninitType{} };

#if (__AVX__ || __SSE__ || __SSE2__ || __SSE3__ || __SSE4_1__ || _M_AMD64 || _M_X64) && 1

    const __m128 aRows0 = _mm_load_ps(&a._00);
    const __m128 aRows1 = _mm_load_ps(&a._10);
    const __m128 aRows2 = _mm_load_ps(&a._20);
    const __m128 aRows3 = _mm_load_ps(&a._30);

    const __m128 bR0 = _mm_load_ps(&b._00);
    const __m128 bR1 = _mm_load_ps(&b._10);
    const __m128 bR2 = _mm_load_ps(&b._20);
    const __m128 bR3 = _mm_load_ps(&b._30);
    {
        const __m128 r00 = _mm_mul_ps(_mm_shuffle_ps(aRows0, aRows0, _MM_SHUFFLE(0, 0, 0, 0)), bR0);
        const __m128 r01 = _mm_mul_ps(_mm_shuffle_ps(aRows0, aRows0, _MM_SHUFFLE(1, 1, 1, 1)), bR1);
        const __m128 r02 = _mm_mul_ps(_mm_shuffle_ps(aRows0, aRows0, _MM_SHUFFLE(2, 2, 2, 2)), bR2);
        const __m128 r03 = _mm_mul_ps(_mm_shuffle_ps(aRows0, aRows0, _MM_SHUFFLE(3, 3, 3, 3)), bR3);
        const __m128 r0Res = _mm_add_ps(_mm_add_ps(r00, r01), _mm_add_ps(r02, r03));
        _mm_store_ps(&result._00, r0Res);
    }
    {
        const __m128 r10 = _mm_mul_ps(_mm_shuffle_ps(aRows1, aRows1, _MM_SHUFFLE(0, 0, 0, 0)), bR0);
        const __m128 r11 = _mm_mul_ps(_mm_shuffle_ps(aRows1, aRows1, _MM_SHUFFLE(1, 1, 1, 1)), bR1);
        const __m128 r12 = _mm_mul_ps(_mm_shuffle_ps(aRows1, aRows1, _MM_SHUFFLE(2, 2, 2, 2)), bR2);
        const __m128 r13 = _mm_mul_ps(_mm_shuffle_ps(aRows1, aRows1, _MM_SHUFFLE(3, 3, 3, 3)), bR3);
        const __m128 r1Res = _mm_add_ps(_mm_add_ps(r10, r11), _mm_add_ps(r12, r13));
        _mm_store_ps(&result._10, r1Res);
    }
    {
        const __m128 r20 = _mm_mul_ps(_mm_shuffle_ps(aRows2, aRows2, _MM_SHUFFLE(0, 0, 0, 0)), bR0);
        const __m128 r21 = _mm_mul_ps(_mm_shuffle_ps(aRows2, aRows2, _MM_SHUFFLE(1, 1, 1, 1)), bR1);
        const __m128 r22 = _mm_mul_ps(_mm_shuffle_ps(aRows2, aRows2, _MM_SHUFFLE(2, 2, 2, 2)), bR2);
        const __m128 r23 = _mm_mul_ps(_mm_shuffle_ps(aRows2, aRows2, _MM_SHUFFLE(3, 3, 3, 3)), bR3);
        const __m128 r2Res = _mm_add_ps(_mm_add_ps(r20, r21), _mm_add_ps(r22, r23));
        _mm_store_ps(&result._20, r2Res);
    }
    {
        const __m128 r30 = _mm_mul_ps(_mm_shuffle_ps(aRows3, aRows3, _MM_SHUFFLE(0, 0, 0, 0)), bR0);
        const __m128 r31 = _mm_mul_ps(_mm_shuffle_ps(aRows3, aRows3, _MM_SHUFFLE(1, 1, 1, 1)), bR1);
        const __m128 r32 = _mm_mul_ps(_mm_shuffle_ps(aRows3, aRows3, _MM_SHUFFLE(2, 2, 2, 2)), bR2);
        const __m128 r33 = _mm_mul_ps(_mm_shuffle_ps(aRows3, aRows3, _MM_SHUFFLE(3, 3, 3, 3)), bR3);
        const __m128 r3Res = _mm_add_ps(_mm_add_ps(r30, r31), _mm_add_ps(r32, r33));
        _mm_store_ps(&result._30, r3Res);
    }
#else

    #define MATRIX_ADD_ROW_MULT(row, col) (\
        a._##row##0 * b._0##col + \
        a._##row##1 * b._1##col + \
        a._##row##2 * b._2##col + \
        a._##row##3 * b._3##col)
#define MATRIX_SET(row, col) (result._##row##col)  = MATRIX_ADD_ROW_MULT(row, col)

    MATRIX_SET(0, 0);
    MATRIX_SET(0, 1);
    MATRIX_SET(0, 2);
    MATRIX_SET(0, 3);

    MATRIX_SET(1, 0);
    MATRIX_SET(1, 1);
    MATRIX_SET(1, 2);
    MATRIX_SET(1, 3);

    MATRIX_SET(2, 0);
    MATRIX_SET(2, 1);
    MATRIX_SET(2, 2);
    MATRIX_SET(2, 3);

    MATRIX_SET(3, 0);
    MATRIX_SET(3, 1);
    MATRIX_SET(3, 2);
    MATRIX_SET(3, 3);

#undef MATRIX_ADD_ROW_MULT
#undef MATRIX_SET

#endif
    return result;
}


Mat3x4 operator*(const Mat3x4 &a, const Mat3x4 &b)
{
    Mat3x4 result{ UninitType{} };

#if (__AVX__ || __SSE__ || __SSE2__ || __SSE3__ || __SSE4_1__ || _M_AMD64 || _M_X64) && 1

    const __m128 aRows0 = _mm_load_ps(&a._00);
    const __m128 aRows1 = _mm_load_ps(&a._10);
    const __m128 aRows2 = _mm_load_ps(&a._20);

    const __m128 bR0 = _mm_load_ps(&b._00);
    const __m128 bR1 = _mm_load_ps(&b._10);
    const __m128 bR2 = _mm_load_ps(&b._20);
    const __m128 bR3 = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);
    {
        const __m128 r00 = _mm_mul_ps(_mm_shuffle_ps(aRows0, aRows0, _MM_SHUFFLE(0, 0, 0, 0)), bR0);
        const __m128 r01 = _mm_mul_ps(_mm_shuffle_ps(aRows0, aRows0, _MM_SHUFFLE(1, 1, 1, 1)), bR1);
        const __m128 r02 = _mm_mul_ps(_mm_shuffle_ps(aRows0, aRows0, _MM_SHUFFLE(2, 2, 2, 2)), bR2);
        const __m128 r03 = _mm_mul_ps(_mm_shuffle_ps(aRows0, aRows0, _MM_SHUFFLE(3, 3, 3, 3)), bR3);
        const __m128 r0Res = _mm_add_ps(_mm_add_ps(r00, r01), _mm_add_ps(r02, r03));
        _mm_store_ps(&result._00, r0Res);
    }
    {
        const __m128 r10 = _mm_mul_ps(_mm_shuffle_ps(aRows1, aRows1, _MM_SHUFFLE(0, 0, 0, 0)), bR0);
        const __m128 r11 = _mm_mul_ps(_mm_shuffle_ps(aRows1, aRows1, _MM_SHUFFLE(1, 1, 1, 1)), bR1);
        const __m128 r12 = _mm_mul_ps(_mm_shuffle_ps(aRows1, aRows1, _MM_SHUFFLE(2, 2, 2, 2)), bR2);
        const __m128 r13 = _mm_mul_ps(_mm_shuffle_ps(aRows1, aRows1, _MM_SHUFFLE(3, 3, 3, 3)), bR3);
        const __m128 r1Res = _mm_add_ps(_mm_add_ps(r10, r11), _mm_add_ps(r12, r13));
        _mm_store_ps(&result._10, r1Res);
    }
    {
        const __m128 r20 = _mm_mul_ps(_mm_shuffle_ps(aRows2, aRows2, _MM_SHUFFLE(0, 0, 0, 0)), bR0);
        const __m128 r21 = _mm_mul_ps(_mm_shuffle_ps(aRows2, aRows2, _MM_SHUFFLE(1, 1, 1, 1)), bR1);
        const __m128 r22 = _mm_mul_ps(_mm_shuffle_ps(aRows2, aRows2, _MM_SHUFFLE(2, 2, 2, 2)), bR2);
        const __m128 r23 = _mm_mul_ps(_mm_shuffle_ps(aRows2, aRows2, _MM_SHUFFLE(3, 3, 3, 3)), bR3);
        const __m128 r2Res = _mm_add_ps(_mm_add_ps(r20, r21), _mm_add_ps(r22, r23));
        _mm_store_ps(&result._20, r2Res);
    }

#else

    #define MATRIX_ADD_ROW_MULT0(row, col) (\
        a._##row##0 * b._0##col + \
        a._##row##1 * b._1##col + \
        a._##row##2 * b._2##col)
    #define MATRIX_ADD_ROW_MULT1(row, col) (\
        a._##row##0 * b._0##col + \
        a._##row##1 * b._1##col + \
        a._##row##2 * b._2##col + \
        a._##row##3)

    #define MATRIX_SET0(row, col) (result._##row##col)  = MATRIX_ADD_ROW_MULT0(row, col)
    #define MATRIX_SET1(row, col) (result._##row##col)  = MATRIX_ADD_ROW_MULT1(row, col)

    MATRIX_SET0(0, 0);
    MATRIX_SET0(0, 1);
    MATRIX_SET0(0, 2);
    MATRIX_SET1(0, 3);

    MATRIX_SET0(1, 0);
    MATRIX_SET0(1, 1);
    MATRIX_SET0(1, 2);
    MATRIX_SET1(1, 3);

    MATRIX_SET0(2, 0);
    MATRIX_SET0(2, 1);
    MATRIX_SET0(2, 2);
    MATRIX_SET1(2, 3);

    #undef MATRIX_ADD_ROW_MULT0
    #undef MATRIX_ADD_ROW_MULT1
    #undef MATRIX_SET0
    #undef MATRIX_SET1

#endif
    return result;
}

