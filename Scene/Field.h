#pragma once

#include "Airplane.h"
#include "olcPixelGameEngine.h"

#include <array>

#undef None

class Field {
public:
    void draw(olc::PixelGameEngine *pge) const;

private:
    enum class CloudState {
        None,
        Regular,
        Rain,
    };

    std::array<std::array<CloudState, 16>, 16> clouds;
    Airplane airplane;
};
