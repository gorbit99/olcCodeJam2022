#include "Node.h"

#include "../AssetSystem/SpriteManager.h"

#include <vector>

// NodePin

Node::NodePin::NodePin(olc::vf2d offset, PinType pinType)
        : offset{offset},
          pinType{pinType} {
}

olc::vf2d Node::NodePin::getOffset() {
    return offset;
}

Node::NodePin::PinType Node::NodePin::getPinType() {
    return pinType;
}

void Node::NodePin::draw(olc::PixelGameEngine *pge, Node &parent) {
    auto sprite = SpriteManager::getInstance().getSprite(
            SpriteManager::SpriteAssets::Pin);

    auto halfSize = olc::vi2d{
            sprite.get().Sprite()->width / 2,
            sprite.get().Sprite()->height / 2,
    };

    pge->DrawDecal(parent.position + halfSize, sprite.get().Decal());
}

// Node

Node::Node(olc::Renderable &graphic, std::vector<NodePin> pins)
        : pins{pins},
          graphic{graphic} {
}

void Node::draw(olc::PixelGameEngine *pge, olc::vf2d pos) {
    auto halfSize = olc::vi2d{
            graphic.get().Sprite()->width / 2,
            graphic.get().Sprite()->height / 2,
    };

    pge->DrawDecal(pos + halfSize, graphic.get().Decal());

    for (auto &pin : pins) {
        pin.draw(pge, *this);
    }
}
