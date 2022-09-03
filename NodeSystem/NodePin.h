#pragma once

#include "PinType.h"
#include "olcPixelGameEngine.h"

#include <functional>
#include <unordered_map>
#include <variant>

class Node;

class NodePin {
public:
    NodePin(olc::vf2d offset, PinType pinType, Node &parent);
    virtual ~NodePin();
    olc::vf2d getOffset() const;
    virtual void draw(olc::PixelGameEngine *pge) const = 0;
    olc::vf2d getPosition() const;
    Node &getParent();
    const Node &getParent() const;
    bool isPointOver(olc::vf2d point) const;
    virtual bool isConnected() const = 0;
    PinType getPinType() const;

protected:
    olc::Pixel getColor() const;
    PinType pinType;

private:
    olc::vf2d offset;

    std::reference_wrapper<Node> parent;
};
