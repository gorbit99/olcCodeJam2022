#include "PaintGreenNode.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/InputPin.h"

PaintGreenNode::PaintGreenNode(olc::vf2d position)
        : Node{
                SpriteManager::getInstance().getSprite(
                        SpriteManager::SpriteAssets::GreenPaintNode),
                position,
        } {
    inputPins.push_back(InputPin{{-8, 0}, PinType::Flow, *this});
    outputPins.push_back(OutputPin{{8, 0}, PinType::Flow, *this});
}

EvaluationResult PaintGreenNode::evaluate(Field &field) {
    field.paintCloud(Field::CloudColor::Green);

    return {connectedFromPin(0), false};
}
