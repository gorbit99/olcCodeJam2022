#include "Airplane.h"

bool Airplane::update(olc::PixelGameEngine *pge) {
}

void Airplane::draw(olc::PixelGameEngine *pge) const {
}

void Airplane::turnLeft() {
    switch (direction) {
    case Direction::Up:
        direction = Direction::Left;
        break;
    case Direction::Down:
        direction = Direction::Right;
        break;
    case Direction::Left:
        direction = Direction::Down;
        break;
    case Direction::Right:
        direction = Direction::Up;
        break;
    }
}

void Airplane::turnRight() {
    switch (direction) {
    case Direction::Up:
        direction = Direction::Right;
        break;
    case Direction::Down:
        direction = Direction::Left;
        break;
    case Direction::Left:
        direction = Direction::Up;
        break;
    case Direction::Right:
        direction = Direction::Down;
        break;
    }
}
