#pragma once

#include "quat.h"
#include "vec3.h"

struct Transform
{
    Vec3 pos;
    Quat rot;
    Vec3 scale{ 1.0f, 1.0f, 1.0f };
};
