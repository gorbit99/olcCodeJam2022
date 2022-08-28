#pragma once

#include "olcPixelGameEngine.h"

#include <vector>

class Node {
public:
    struct NodePin {
    public:
        enum class PinType {
            In,
            Out,
        };

        NodePin(olc::vf2d offset, PinType pinType);

        olc::vf2d getOffset();
        PinType getPinType();
        void draw(olc::PixelGameEngine *pge, Node &parent);

    private:
        olc::vf2d offset;
        PinType pinType;
    };

    Node(olc::Renderable &graphic, std::vector<NodePin> pins);

    // TODO: Refactor to use a camera
    void draw(olc::PixelGameEngine *pge, olc::vf2d pos);

protected:
    std::vector<NodePin> pins;

private:
    std::reference_wrapper<olc::Renderable> graphic;
    olc::vf2d position;
};
