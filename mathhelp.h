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
