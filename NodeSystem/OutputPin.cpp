#include "OutputPin.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/PinType.h"

OutputPin::OutputPin(olc::vf2d offset, PinType pinType, Node &parent)
        : NodePin{offset, pinType, parent} {
}

void OutputPin::sendData(PinData &data) {
    connection.value().sendData(data);
}

void OutputPin::connectTo(InputPin &other) {
    connection.emplace(*this, other, NodePin::pinType);
}

void OutputPin::draw(olc::PixelGameEngine *pge) const {
    auto sprite = SpriteManager::getInstance().getSprite(
            SpriteManager::SpriteAssets::PinOut);

    auto halfSize = olc::vi2d{
            sprite.get().Sprite()->width / 2,
            sprite.get().Sprite()->height / 2,
    };

    auto color = NodePin::getColor();

    pge->DrawDecal(NodePin::getPosition() - halfSize * 2,
                   sprite.get().Decal(),
                   {2, 2},
                   color);

    if (connection.has_value()) {
        connection.value().draw(pge);
    }
}

void OutputPin::disconnect() {
    connection.reset();
}

Connection &OutputPin::getConnection() {
    return connection.value();
}

bool OutputPin::isConnected() const {
    return connection.has_value();
}
