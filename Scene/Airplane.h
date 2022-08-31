#pragma once

#include "olcPixelGameEngine.h"

class Airplane {
public:
    bool update(olc::PixelGameEngine *pge);
    void draw(olc::PixelGameEngine *pge) const;
    void turnLeft();
    void turnRight();

private:
    enum class Direction {
        Up,
        Down,
        Left,
        Right,
    };

    olc::vf2d position{0, 0};
    Direction direction = Direction::Right;
};
