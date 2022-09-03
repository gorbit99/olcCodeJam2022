#include "TurnRightNode.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/InputPin.h"

TurnRightNode::TurnRightNode(olc::vf2d position)
        : Node{
                SpriteManager::getInstance().getSprite(
                        SpriteManager::SpriteAssets::TurnRightNode),
                position,
        } {
    inputPins.push_back(InputPin{{-8, 0}, PinType::Flow, *this});
    outputPins.push_back(OutputPin{{8, 0}, PinType::Flow, *this});
}

EvaluationResult TurnRightNode::evaluate(Field &field) {
    field.turnRight();

    return {connectedFromPin(0), false};
}
