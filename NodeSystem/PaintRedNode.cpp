#include "PaintRedNode.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/InputPin.h"

PaintRedNode::PaintRedNode(olc::vf2d position)
        : Node{
                SpriteManager::getInstance().getSprite(
                        SpriteManager::SpriteAssets::RedPaintNode),
                position,
        } {
    inputPins.push_back(InputPin{{-8, 0}, PinType::Flow, *this});
    outputPins.push_back(OutputPin{{8, 0}, PinType::Flow, *this});
}

EvaluationResult PaintRedNode::evaluate(Field &field) {
    field.paintCloud(Field::CloudColor::Red);

    return {connectedFromPin(0), false};
}
