#include "TurnLeftNode.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/InputPin.h"

TurnLeftNode::TurnLeftNode(olc::vf2d position)
        : Node{
                SpriteManager::getInstance().getSprite(
                        SpriteManager::SpriteAssets::TurnLeftNode),
                position,
        } {
    inputPins.push_back(InputPin{{-8, 0}, PinType::Flow, *this});
    outputPins.push_back(OutputPin{{8, 0}, PinType::Flow, *this});
}

EvaluationResult TurnLeftNode::evaluate(Field &field) {
    field.turnLeft();

    return {connectedFromPin(0), false};
}
