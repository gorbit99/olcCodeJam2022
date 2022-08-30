#pragma once

#include "NodePin.h"
#include "olcPixelGameEngine.h"

#include <vector>

class Node {
public:
    Node(olc::Renderable &graphic, olc::vf2d position);

    // TODO: Refactor to use a camera
    void draw(olc::PixelGameEngine *pge);
    olc::vf2d getCenter() const;

private:
    std::reference_wrapper<olc::Renderable> graphic;
    olc::vf2d position;
};
