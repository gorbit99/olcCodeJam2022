#include "Airplane.h"

#include "AssetSystem/SpriteManager.h"

#include <algorithm>

const float Airplane::moveTime = 0.5;
constexpr float PI = 3.1415926f;

bool Airplane::update(olc::PixelGameEngine *pge) {
    currentMoveProgress =
            std::min(1.0f, currentMoveProgress + pge->GetElapsedTime());

    return currentMoveProgress == 1;
}

void Airplane::draw(olc::PixelGameEngine *pge) const {
    auto currentPosition = position;

    pge->DrawDecal(position * 32,
                   SpriteManager::getInstance()
                           .getSprite(SpriteManager::SpriteAssets::Airplane)
                           .Decal());
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
    float angle = nextRotationDegrees();
}

float Airplane::nextRotationDegrees() const {
    if (direction == nextDirection) {
        return 0;
    }

    if (direction == Direction::Left) {
        if (direction == Direction::Up) {
            return -PI / 2;
        }
        return PI / 2;
    }

    if (direction == Direction::Right) {
        if (direction == Direction::Up) {
            return PI / 2;
        }
        return -PI / 2;
    }

    if (direction == Direction::Up) {
        if (direction == Direction::Left) {
            return PI / 2;
        }
        return -PI / 2;
    }

    if (direction == Direction::Down) {
        if (direction == Direction::Left) {
            return -PI / 2;
        }
        return PI / 2;
    }
}
