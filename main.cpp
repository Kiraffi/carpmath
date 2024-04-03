#include "mat4.h"
#include "mathhelp.h"
#include "quat.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"


#include <stdio.h>

void sTestVec2()
{
    Vec2 a(1, 2);
    Vec2 b(3, 4);
    Vec2 result = a * b;

    float d = dot(a, b);

    printf("V2: %f, %f\n", result.x, result.y);
    printf("V2-dot: %f\n", d);
}

void sTestVec3()
{
    Vec3 a(1, 2, 3);
    Vec3 b(4, 5, 6);
    Vec3 result = a * b;

    float d = dot(a, b);

    printf("V3: %f, %f, %f\n", result.x, result.y, result.z);
    printf("V3-dot: %f\n", d);
}

void sTestVec4()
{
    Vec4 a(1, 2, 3, 4);
    Vec4 b(5, 6, 7, 8);
    Vec4 result = a * b;

    float d = dot(a, b);

    printf("V4: %f, %f, %f, %f\n", result.x, result.y, result.z, result.w);
    printf("V4-dot: %f\n", d);
}

void sTestQuat()
{
    Quat a(0, 0, 0, 1);

    Quat b = getQuatFromAxisAngle(Vec3(1, 0, 0), PI * 1.0f);
    Quat c = a * b;

    printf("Q: %f, %f, %f, %f\n", c.vx, c.vy, c.vz, c.w);
}

void sTestMat4()
{
    Mat4x4 m1;
    Mat4x4 m2;
    Mat4x4 m3 = m1 * m2;

    printf("\nMat4\n");
    for(int i = 1; i <= 16; ++i)
    {
        if((i % 4) == 0)
        {
            printf("%f\n", m3[i - 1]);
        }
        else
        {
            printf("%f, ", m3[i - 1]);
        }
    }
}

int main()
{
    sTestVec2();
    sTestVec3();
    sTestVec4();

    sTestQuat();
    sTestMat4();
    return 0;
}
