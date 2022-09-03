#include "SmallerNode.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/InputPin.h"

#include <iostream>

SmallerNode::SmallerNode(olc::vf2d position)
        : Node{
                SpriteManager::getInstance().getSprite(
                        SpriteManager::SpriteAssets::SmallerNode),
                position,
        } {
    inputPins.push_back(InputPin{{-8, -10}, PinType::Flow, *this});
    inputPins.push_back(InputPin{{-8, 0}, PinType::Number, *this});
    inputPins.push_back(InputPin{{-8, 10}, PinType::Number, *this});
    outputPins.push_back(OutputPin{{8, -8}, PinType::Flow, *this});
    outputPins.push_back(OutputPin{{8, 8}, PinType::Logic, *this});
}

EvaluationResult SmallerNode::evaluate(Field &) {
    auto val1 = std::get<float>(inputPins.at(1).takeData());
    auto val2 = std::get<float>(inputPins.at(2).takeData());

    auto result = val1 < val2;
    outputPins.at(1).sendData(result);

    return {connectedFromPin(0), false};
}
