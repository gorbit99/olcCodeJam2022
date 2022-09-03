#include "IfNode.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/InputPin.h"

IfNode::IfNode(olc::vf2d position)
        : Node{
                SpriteManager::getInstance().getSprite(
                        SpriteManager::SpriteAssets::IfNode),
                position,
        } {
    inputPins.push_back(InputPin{{-8, -8}, PinType::Flow, *this});
    inputPins.push_back(InputPin{{-8, 8}, PinType::Logic, *this});
    outputPins.push_back(OutputPin{{8, -8}, PinType::Flow, *this});
    outputPins.push_back(OutputPin{{8, 8}, PinType::Flow, *this});
}

EvaluationResult IfNode::evaluate(Field &) {
    auto value = std::get<bool>(inputPins.at(1).takeData());

    if (value) {
        return {connectedFromPin(0), false};
    }
    return {connectedFromPin(1), false};
}
