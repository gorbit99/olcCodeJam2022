#include "InputPin.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/OutputPin.h"
#include "NodeSystem/PinType.h"

#include <algorithm>

InputPin::InputPin(olc::vf2d offset, PinType pinType, Node &parent)
        : NodePin{offset, pinType, parent} {
}

InputPin::~InputPin() {
    for (auto &connectedPin : connectedPins) {
        connectedPin.get().disconnect();
    }
}

PinData InputPin::takeData() {
    if (!data.has_value()) {
        switch (pinType) {
        case PinType::Flow:
            return std::monostate{};
        case PinType::Logic:
            return false;
        case PinType::Number:
            return 0.0f;
        }
    }
    auto result = data.value();
    data.reset();
    return result;
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
    connectedPins.push_back(outputPin);
}

void InputPin::disconnect(OutputPin &outputPin) {
    connectedPins.erase(std::remove_if(connectedPins.begin(),
                                       connectedPins.end(),
                                       [&](const auto &connectedPin) {
                                           return &connectedPin.get()
                                                  == &outputPin;
                                       }),
                        connectedPins.end());
}

bool InputPin::isConnected() const {
    return connectedPins.size() > 0;
}
