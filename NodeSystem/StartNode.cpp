#include "StartNode.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/EvaluationResult.h"

StartNode::StartNode(olc::vf2d position)
        : Node{
                SpriteManager::getInstance().getSprite(
                        SpriteManager::SpriteAssets::StartNode),
                position,
        } {
    outputPins.push_back(OutputPin{{8, 0}, PinType::Flow, *this});
}

EvaluationResult StartNode::evaluate(Field &) {
    return {connectedFromPin(0), false};
}
