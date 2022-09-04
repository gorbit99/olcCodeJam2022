#include "FadeOut.h"

#include <algorithm>
#include <cmath>

void FadeOut::start(float fadeTime, std::function<void()> callback) {
    this->fadeTime = fadeTime;
    fadeFunction = callback;
    elapsed = 0;
}

void FadeOut::update(olc::PixelGameEngine *pge) {
    elapsed += pge->GetElapsedTime();

    if (elapsed >= fadeTime && fadeFunction.has_value()) {
        fadeFunction.value()();
        fadeFunction.reset();
    }
}

void FadeOut::draw(olc::PixelGameEngine *pge) const {
    olc::vi2d size{
            pge->ScreenWidth(),
            pge->ScreenHeight(),
    };
    auto opacity = std::max(0.0f, 1 - std::abs(1 - elapsed / fadeTime));

    pge->FillRectDecal({0, 0},
                       size,
                       {0, 0, 0, static_cast<uint8_t>(opacity * 255)});
}
