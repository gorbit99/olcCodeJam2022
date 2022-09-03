#include "ConstantNode.h"

#include "AssetSystem/SpriteManager.h"
#include "NodeSystem/InputPin.h"

#include <algorithm>
#include <string>

ConstantNode::ConstantNode(olc::vf2d position)
        : Node{
                SpriteManager::getInstance().getSprite(
                        SpriteManager::SpriteAssets::ConstantNode),
                position,
        } {
    inputPins.push_back(InputPin{{-16, 0}, PinType::Flow, *this});
    outputPins.push_back(OutputPin{{16, -8}, PinType::Flow, *this});
    outputPins.push_back(OutputPin{{16, 8}, PinType::Number, *this});
}

EvaluationResult ConstantNode::evaluate(Field &) {
    outputPins.at(1).sendData(static_cast<float>(value));

    return {connectedFromPin(0), false};
}

void ConstantNode::draw(olc::PixelGameEngine *pge) const {
    Node::draw(pge);

    auto text = std::to_string(value);
    auto textWidth = pge->GetTextSizeProp(text).x;

    pge->DrawStringPropDecal(getCenter() + olc::vi2d{-textWidth / 2 - 4, -3},
                             text);
}

bool ConstantNode::interact(olc::PixelGameEngine *pge) {
    olc::vi2d plusTopLeft{-7, -12};
    olc::vi2d plusBottomRight{3, -7};
    olc::vi2d minusTopLeft{-7, 7};
    olc::vi2d minusBottomRight{3, 12};

    auto point = (pge->GetMousePos() - getCenter()) / 2;

    if (point.x >= plusTopLeft.x && point.x <= plusBottomRight.x
        && point.y >= plusTopLeft.y && point.y <= plusBottomRight.y) {
        value = std::min(99, value + 1);
        return true;
    }

    if (point.x >= minusTopLeft.x && point.x <= minusBottomRight.x
        && point.y >= minusTopLeft.y && point.y <= minusBottomRight.y) {
        value = std::max(-99, value - 1);
        return true;
    }

    return false;
}
