#include "CloudNode.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/InputPin.h"

CloudNode::CloudNode(olc::vf2d position)
        : Node{
                SpriteManager::getInstance().getSprite(
                        SpriteManager::SpriteAssets::CloudNode),
                position,
        } {
    inputPins.push_back(InputPin{{-8, 0}, PinType::Flow, *this});
    outputPins.push_back(OutputPin{{8, 0}, PinType::Flow, *this});
}

EvaluationResult CloudNode::evaluate(Field &field) {
    field.createCloud();

    return {connectedFromPin(0), false};
}
