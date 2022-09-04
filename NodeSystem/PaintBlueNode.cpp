#include "PaintBlueNode.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/InputPin.h"

PaintBlueNode::PaintBlueNode(olc::vf2d position)
        : Node{
                SpriteManager::getInstance().getSprite(
                        SpriteManager::SpriteAssets::BluePaintNode),
                position,
        } {
    inputPins.push_back(InputPin{{-8, 0}, PinType::Flow, *this});
    outputPins.push_back(OutputPin{{8, 0}, PinType::Flow, *this});
}

EvaluationResult PaintBlueNode::evaluate(Field &field) {
    field.paintCloud(Field::CloudColor::Blue);

    return {connectedFromPin(0), false};
}
