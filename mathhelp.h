#pragma once


#ifndef DEBUG_BREAK_MACRO_MATH
#if _MSC_VER
#define DEBUG_BREAK_MACRO() __debugbreak()
#else
#include <signal.h>
#define DEBUG_BREAK_MACRO_MATH() raise(SIGTRAP)
#endif
#endif

#ifndef ASSERT_MATH
#define ASSERT_MATH(x) do{ if(x) {} else { DEBUG_BREAK_MACRO_MATH(); } } while(0)
#endif

#include <math.h>
#include <stdint.h>

#ifndef PI
#define PI (3.141596f)
#endif

static float sTanF(float f)
{
    return ::tanf(f);
}
static float sSinF(float f)
{
    return ::sinf(f);
}

static float sCosF(float f)
{
    return ::cosf(f);
}

static float sSqrtF(float f)
{
    return ::sqrt(f);
}

static float sMinF(float f1, float f2)
{
    return f1 < f2 ? f1 : f2;
}

static float sMaxF(float f1, float f2)
{
    return f1 > f2 ? f1 : f2;
}

static float sAbsF(float f)
{
    return ::fabsf(f);
}

static float sToRadians(float angle)
{
    return float((angle / 180.0f) * PI);
}
static float sToDegrees(float angle)
{
    return float(180.0f / PI * angle);
}

static float sClampF(float v, float minValue, float maxValue)
{
    v = v < minValue ? minValue : v;
    v = v > maxValue ? maxValue : v;
    return v;
}

static uint32_t sGetColor(float r, float g, float b, float a)
{
    r = sClampF(r, 0.0f, 1.0f);
    g = sClampF(g, 0.0f, 1.0f);
    b = sClampF(b, 0.0f, 1.0f);
    a = sClampF(a, 0.0f, 1.0f);
    uint32_t color = uint32_t(r * 255.0f);
    color |= (uint32_t(g * 255.0f)) << 8u;
    color |= (uint32_t(b * 255.0f)) << 16u;
    color |= (uint32_t(a * 255.0f)) << 24u;
    return color;
}
