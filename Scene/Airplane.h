#pragma once

#include "olcPixelGameEngine.h"

class Airplane {
public:
    bool update(olc::PixelGameEngine *pge);
    void draw(olc::PixelGameEngine *pge) const;
    void turnLeft();
    void turnRight();
    olc::vi2d getPosition() const;
    static const float moveTime;

private:
    enum class Direction {
        Up,
        Down,
        Left,
        Right,
    };

    olc::vf2d determineCurrentPosition() const;
    float determineCurrentRotation() const;
    float nextRotationDegrees() const;
    olc::vf2d getPositionOffset() const;

    static olc::vi2d directionToVector(Direction direction);
    static float directionToAngle(Direction direction);

    olc::vi2d position{3, 3};
    Direction direction = Direction::Right;
    Direction nextDirection = Direction::Right;
    float currentMoveProgress = 0;
};
