#pragma once

#include "olcPixelGameEngine.h"

class Airplane {
public:
    bool update(olc::PixelGameEngine *pge);
    void draw(olc::PixelGameEngine *pge) const;
    void turnLeft();
    void turnRight();

private:
    olc::vf2d determineCurrentPosition() const;
    float nextRotationDegrees() const;

    enum class Direction {
        Up,
        Down,
        Left,
        Right,
    };

    olc::vi2d position{0, 0};
    Direction direction = Direction::Right;
    Direction nextDirection = Direction::Right;
    float currentMoveProgress = 0;

    static const float moveTime;
};
