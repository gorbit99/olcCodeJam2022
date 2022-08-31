#pragma once

#include "olcPixelGameEngine.h"

void drawThickLine(olc::PixelGameEngine *pge,
                   olc::vf2d start,
                   olc::vf2d end,
                   float thickness,
                   olc::Pixel color = olc::WHITE);
