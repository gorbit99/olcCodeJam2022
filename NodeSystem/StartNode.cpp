#include "StartNode.h"

#include "../AssetSystem/SpriteManager.h"
#include "NodeSystem/Node.h"

StartNode::StartNode()
        : Node{SpriteManager::getInstance().getSprite(
                       SpriteManager::SpriteAssets::StartNode),
               {}} {
    pins.emplace_back(NodePin{{8, 0}, NodePin::PinType::Out});
}
