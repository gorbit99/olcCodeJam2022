#include "LocationNode.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/InputPin.h"

LocationNode::LocationNode(olc::vf2d position)
        : Node{
                SpriteManager::getInstance().getSprite(
                        SpriteManager::SpriteAssets::LocationNode),
                position,
        } {
    inputPins.push_back(InputPin{{-8, 0}, PinType::Flow, *this});
    outputPins.push_back(OutputPin{{8, -10}, PinType::Flow, *this});
    outputPins.push_back(OutputPin{{8, 0}, PinType::Number, *this});
    outputPins.push_back(OutputPin{{8, 10}, PinType::Number, *this});
}

EvaluationResult LocationNode::evaluate(Field &field) {
    auto airplanePos = field.getPlanePosition();
    outputPins.at(1).sendData(static_cast<float>(airplanePos.x));
    outputPins.at(2).sendData(static_cast<float>(airplanePos.y));

    return {connectedFromPin(0), false};
}
