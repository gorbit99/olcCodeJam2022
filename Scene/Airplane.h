#pragma once

#include "olcPixelGameEngine.h"

class Airplane {
public:
    enum class Direction {
        Up,
        Down,
        Left,
        Right,
    };

    bool update(olc::PixelGameEngine *pge);
    void draw(olc::PixelGameEngine *pge) const;
    void turnLeft();
    void turnRight();
    olc::vi2d getPosition() const;
    void reset();
    Direction getDirection() const;
    static const float moveTime;

private:
    olc::vf2d determineCurrentPosition() const;
    float determineCurrentRotation() const;
    float nextRotationDegrees() const;
    olc::vf2d getPositionOffset() const;

    static olc::vi2d directionToVector(Direction direction);
    static float directionToAngle(Direction direction);

    olc::vi2d position{0, 0};
    Direction direction = Direction::Right;
    Direction nextDirection = Direction::Right;
    float currentMoveProgress = 0;
};
