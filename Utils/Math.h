#pragma once

#include "olcPixelGameEngine.h"

class Math {
public:
    static bool isPointOverLine(olc::vf2d point,
                                olc::vf2d a,
                                olc::vf2d b,
                                float radius);
};
