#include "AndNode.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/InputPin.h"

#include <iostream>

AndNode::AndNode(olc::vf2d position)
        : Node{
                SpriteManager::getInstance().getSprite(
                        SpriteManager::SpriteAssets::AndNode),
                position,
        } {
    inputPins.push_back(InputPin{{-8, -10}, PinType::Flow, *this});
    inputPins.push_back(InputPin{{-8, 0}, PinType::Logic, *this});
    inputPins.push_back(InputPin{{-8, 10}, PinType::Logic, *this});
    outputPins.push_back(OutputPin{{8, -8}, PinType::Flow, *this});
    outputPins.push_back(OutputPin{{8, 8}, PinType::Logic, *this});
}

EvaluationResult AndNode::evaluate(Field &) {
    auto val1 = std::get<bool>(inputPins.at(1).takeData());
    auto val2 = std::get<bool>(inputPins.at(2).takeData());

    auto result = val1 && val2;
    outputPins.at(1).sendData(result);

    return {connectedFromPin(0), false};
}
