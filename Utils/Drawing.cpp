#include "Drawing.h"

void drawThickLine(olc::PixelGameEngine *pge,
                   olc::vf2d start,
                   olc::vf2d end,
                   float thickness,
                   olc::Pixel color) {
    auto directionVector = end - start;
    auto tangentVector =
            olc::vf2d(-directionVector.y, directionVector.x).norm();

    auto pt1 = start + thickness / 2 * tangentVector;
    auto pt2 = start - thickness / 2 * tangentVector;
    auto pt3 = end + thickness / 2 * tangentVector;
    auto pt4 = end - thickness / 2 * tangentVector;

    pge->DrawPolygonDecal(nullptr,
                          {pt1, pt2, pt4, pt3},
                          {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
                          color);
}
