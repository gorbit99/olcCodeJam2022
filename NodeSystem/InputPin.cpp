#include "InputPin.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/OutputPin.h"
#include "NodeSystem/PinType.h"

InputPin::InputPin(olc::vf2d offset, PinType pinType, Node &parent)
        : NodePin{offset, pinType, parent} {
}

InputPin::~InputPin() {
    if (connectedPin.has_value()) {
        connectedPin->get().disconnect();
    }
}

PinData InputPin::takeData() {
    auto result = data.value();
    data.reset();
    return result;
}

const PinData &InputPin::getData() const {
    return data.value();
}

void InputPin::setData(PinData data) {
    this->data = data;
}

void InputPin::draw(olc::PixelGameEngine *pge) const {
    auto &sprite = SpriteManager::getInstance().getSprite(
            SpriteManager::SpriteAssets::PinIn);

    auto halfSize = olc::vi2d{
            sprite.Sprite()->width / 2,
            sprite.Sprite()->height / 2,
    };

    auto color = NodePin::getColor();

    pge->DrawDecal(NodePin::getPosition() - halfSize * 2,
                   sprite.Decal(),
                   {2, 2},
                   color);
}

void InputPin::connectTo(OutputPin &outputPin) {
    connectedPin = outputPin;
}

void InputPin::disconnect() {
    connectedPin.reset();
}

bool InputPin::isConnected() const {
    return connectedPin.has_value();
}
