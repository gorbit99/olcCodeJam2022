#include "Node.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/InputPin.h"

#include <iostream>
#include <vector>

Node::Node(olc::Renderable &graphic, olc::vf2d position)
        : graphic{graphic},
          position{position} {
}

void Node::draw(olc::PixelGameEngine *pge) const {
    auto halfSize = getSize() / 2.0f;

    pge->DrawDecal(position - halfSize * 2, graphic.get().Decal(), {2, 2});

    for (auto &inputPin : inputPins) {
        inputPin.draw(pge);
    }

    for (auto &outputPin : outputPins) {
        outputPin.draw(pge);
    }
}

olc::vf2d Node::getCenter() const {
    return position;
}

olc::vi2d Node::getSize() const {
    return {
            graphic.get().Sprite()->width,
            graphic.get().Sprite()->height,
    };
}

bool Node::isPointOver(olc::vf2d point) const {
    auto topLeft = getCenter() - getSize();
    auto bottomRight = getCenter() + getSize();

    return point.x >= topLeft.x && point.x <= bottomRight.x
           && point.y >= topLeft.y && point.y <= bottomRight.y;
}

std::vector<InputPin> &Node::getInputPins() {
    return inputPins;
}

std::vector<OutputPin> &Node::getOutputPins() {
    return outputPins;
}

void Node::setPosition(olc::vf2d position) {
    this->position = position;
}
