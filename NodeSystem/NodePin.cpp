#include "NodePin.h"

#include "Node.h"
#include "NodeSystem/PinType.h"

NodePin::NodePin(olc::vf2d offset, PinType pinType, Node &parent)
        : pinType{pinType},
          offset{offset},
          parent{parent} {
}

NodePin::~NodePin() {
}

olc::vf2d NodePin::getOffset() const {
    return offset;
}

olc::vf2d NodePin::getPosition() const {
    return parent.get().getCenter() + offset * 2;
}

Node &NodePin::getParent() {
    return parent;
}

const Node &NodePin::getParent() const {
    return parent;
}

olc::Pixel NodePin::getColor() const {
    return pinTypeColors.at(pinType);
}

bool NodePin::isPointOver(olc::vf2d point) const {
    auto size = olc::vf2d{6, 6};

    auto topLeft = getPosition() - size;
    auto bottomRight = getPosition() + size;

    return point.x >= topLeft.x && point.x <= bottomRight.x
           && point.y >= topLeft.y && point.y <= bottomRight.y;
}

PinType NodePin::getPinType() const {
    return pinType;
}
