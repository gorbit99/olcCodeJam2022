#include "Airplane.h"

#include "AssetSystem/SpriteManager.h"

const float Airplane::moveTime = 0.5f;
constexpr float PI = 3.1415926f;

bool Airplane::update(olc::PixelGameEngine *pge) {
    currentMoveProgress =
            std::min(1.0f,
                     currentMoveProgress + pge->GetElapsedTime() / moveTime);

    if (currentMoveProgress == 1) {
        currentMoveProgress = 0;
        position += directionToVector(nextDirection);
        direction = nextDirection;

        return true;
    }

    return false;
}

void Airplane::draw(olc::PixelGameEngine *pge) const {
    auto currentPosition = determineCurrentPosition() * 32;
    auto currentRotation = determineCurrentRotation();

    pge->DrawRotatedDecal(
            currentPosition,
            SpriteManager::getInstance()
                    .getSprite(SpriteManager::SpriteAssets::Airplane)
                    .Decal(),
            currentRotation,
            {8, 8});
}

void Airplane::turnLeft() {
    switch (direction) {
    case Direction::Up:
        nextDirection = Direction::Left;
        break;
    case Direction::Down:
        nextDirection = Direction::Right;
        break;
    case Direction::Left:
        nextDirection = Direction::Down;
        break;
    case Direction::Right:
        nextDirection = Direction::Up;
        break;
    }
}

void Airplane::turnRight() {
    switch (direction) {
    case Direction::Up:
        nextDirection = Direction::Right;
        break;
    case Direction::Down:
        nextDirection = Direction::Left;
        break;
    case Direction::Left:
        nextDirection = Direction::Up;
        break;
    case Direction::Right:
        nextDirection = Direction::Down;
        break;
    }
}

olc::vf2d Airplane::determineCurrentPosition() const {
    if (direction == nextDirection) {
        olc::vf2d dirVector = directionToVector(direction);
        auto posDiff = dirVector * currentMoveProgress;
        return posDiff + position + getPositionOffset();
    }

    olc::vf2d forwardVector = directionToVector(direction);
    olc::vf2d sideVector = directionToVector(nextDirection);

    auto forwardMult = std::sin(currentMoveProgress * PI / 2);
    auto sideMult = 1 - std::cos(currentMoveProgress * PI / 2);

    auto posDiff = (forwardVector * forwardMult + sideVector * sideMult) / 2;
    return posDiff + position + getPositionOffset();
}

float Airplane::determineCurrentRotation() const {
    auto difference = nextRotationDegrees();

    auto currentAmount = difference * currentMoveProgress;

    return directionToAngle(direction) + currentAmount;
}

float Airplane::nextRotationDegrees() const {
    if (direction == nextDirection) {
        return 0;
    }

    switch (direction) {
    case Direction::Left:
        if (nextDirection == Direction::Up) {
            return PI / 2;
        }
        return -PI / 2;
    case Direction::Right:
        if (nextDirection == Direction::Up) {
            return -PI / 2;
        }
        return PI / 2;
    case Direction::Up:
        if (nextDirection == Direction::Left) {
            return -PI / 2;
        }
        return PI / 2;
    case Direction::Down:
        if (nextDirection == Direction::Left) {
            return PI / 2;
        }
        return -PI / 2;
    }

    return 0;
}

olc::vi2d Airplane::directionToVector(Direction direction) {
    switch (direction) {
    case Direction::Left:
        return {-1, 0};
    case Direction::Right:
        return {1, 0};
    case Direction::Up:
        return {0, -1};
    case Direction::Down:
        return {0, 1};
    }
    return {0, 0};
}

float Airplane::directionToAngle(Direction direction) {
    switch (direction) {
    case Direction::Left:
        return PI;
    case Direction::Right:
        return 0;
    case Direction::Up:
        return -PI / 2;
    case Direction::Down:
        return -3 * PI / 2;
    }
    return 0;
}

olc::vf2d Airplane::getPositionOffset() const {
    switch (direction) {
    case Direction::Left:
        return {1, 0.5f};
    case Direction::Right:
        return {0, 0.5f};
    case Direction::Up:
        return {0.5f, 1};
    case Direction::Down:
        return {0.5f, 0};
    }
    return {0, 0};
}

olc::vi2d Airplane::getPosition() const {
    return position;
}

void Airplane::reset() {
    position = {0, 0};
    direction = Direction::Right;
    nextDirection = Direction::Right;
    currentMoveProgress = 0;
}

Airplane::Direction Airplane::getDirection() const {
    return direction;
}
