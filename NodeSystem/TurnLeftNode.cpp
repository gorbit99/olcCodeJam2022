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
}
