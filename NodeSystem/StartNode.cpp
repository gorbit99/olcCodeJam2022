#include "StartNode.h"

#include "../AssetSystem/SpriteManager.h"
#include "NodeSystem/Node.h"

StartNode::StartNode(olc::vf2d position)
        : Node{
                SpriteManager::getInstance().getSprite(
                        SpriteManager::SpriteAssets::StartNode),
                position,
        } {
}
