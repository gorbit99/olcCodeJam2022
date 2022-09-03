#include "WaitNode.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/InputPin.h"

WaitNode::WaitNode(olc::vf2d position)
        : Node{
                SpriteManager::getInstance().getSprite(
                        SpriteManager::SpriteAssets::WaitNode),
                position,
        } {
    inputPins.push_back(InputPin{{-8, 0}, PinType::Flow, *this});
    outputPins.push_back(OutputPin{{8, 0}, PinType::Flow, *this});
}

EvaluationResult WaitNode::evaluate(Field &) {
    return {connectedFromPin(0), true};
}
