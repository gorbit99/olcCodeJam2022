#include "Field.h"

#include <cstdint>

void Field::draw(olc::PixelGameEngine *pge) const {
    pge->FillRect({0, 0}, {512, 512}, {36, 69, 25});

    pge->DrawLine({0, 0}, {511, 0}, {18, 34, 12}, 0xf0f0f0f0);
    pge->DrawLine({0, 0}, {0, 511}, {18, 34, 12}, 0xf0f0f0f0);

    for (auto i = 0; i < 16; i++) {
        auto offset = i * 32 + 31;

        pge->DrawLine({0, offset}, {511, offset}, {18, 34, 12}, 0xf0f0f0f0);
        pge->DrawLine({offset, 0}, {offset, 511}, {18, 34, 12}, 0xf0f0f0f0);
    }

    airplane.draw(pge);
}
