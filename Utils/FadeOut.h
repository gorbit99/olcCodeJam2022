#pragma once

#include "olcPixelGameEngine.h"

#include <functional>
#include <optional>

class FadeOut {
public:
    void start(float fadeTime, std::function<void(void)> callback);
    void draw(olc::PixelGameEngine *pge) const;
    void update(olc::PixelGameEngine *pge);

private:
    float fadeTime;
    std::optional<std::function<void(void)>> fadeFunction;
    float elapsed = 0;
};
