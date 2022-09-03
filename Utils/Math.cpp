#include "Math.h"

bool Math::isPointOverLine(olc::vf2d point,
                           olc::vf2d a,
                           olc::vf2d b,
                           float radius) {
    auto len = (b - a).mag();
    if (len == 0) {
        return false;
    }

    auto dirVector = (b - a) / len;

    auto t = std::max(0.0f, std::min(len, (point - a).dot(dirVector)));

    auto projectedPoint = a + t * (dirVector);
    return (point - projectedPoint).mag() < radius;
}
