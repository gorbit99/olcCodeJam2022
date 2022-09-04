#include "DirectionNode.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/InputPin.h"

#include <iostream>

DirectionNode::DirectionNode(olc::vf2d position)
        : Node{
                SpriteManager::getInstance().getSprite(
                        SpriteManager::SpriteAssets::DirectionNode),
                position,
        } {
    inputPins.push_back(InputPin{{-8, -10}, PinType::Flow, *this});
    outputPins.push_back(OutputPin{{8, -8}, PinType::Flow, *this});
    outputPins.push_back(OutputPin{{8, 8}, PinType::Number, *this});
}

EvaluationResult DirectionNode::evaluate(Field &field) {
    auto result = 0;
    switch (field.getPlaneDirection()) {
    case Airplane::Direction::Right:
        result = 0;
    case Airplane::Direction::Up:
        result = 1;
    case Airplane::Direction::Left:
        result = 2;
    case Airplane::Direction::Down:
        result = 3;
    }
    outputPins.at(1).sendData(static_cast<float>(result));

    return {connectedFromPin(0), false};
}
