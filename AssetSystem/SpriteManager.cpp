#include "SpriteManager.h"

#include <iostream>
#include <optional>

std::optional<SpriteManager> SpriteManager::instance;

SpriteManager::SpriteManager() {
    assetPaths[SpriteAssets::PinIn] = "./res/sprites/PinIn.png";
    assetPaths[SpriteAssets::PinOut] = "./res/sprites/PinOut.png";

    assetPaths[SpriteAssets::StartNode] = "./res/sprites/StartNode.png";
    assetPaths[SpriteAssets::TurnLeftNode] = "./res/sprites/TurnLeftNode.png";
    assetPaths[SpriteAssets::TurnRightNode] = "./res/sprites/TurnRightNode.png";
    assetPaths[SpriteAssets::WaitNode] = "./res/sprites/WaitNode.png";
    assetPaths[SpriteAssets::BiggerNode] = "./res/sprites/BiggerNode.png";
    assetPaths[SpriteAssets::SmallerNode] = "./res/sprites/SmallerNode.png";
    assetPaths[SpriteAssets::IfNode] = "./res/sprites/IfNode.png";
    assetPaths[SpriteAssets::ConstantNode] = "./res/sprites/ConstantNode.png";

    assetPaths[SpriteAssets::Airplane] = "./res/sprites/Airplane.png";

    assetPaths[SpriteAssets::Fields] = "./res/sprites/Fields.png";
    assetPaths[SpriteAssets::Forests] = "./res/sprites/Forests.png";
    assetPaths[SpriteAssets::Towns] = "./res/sprites/Towns.png";
    assetPaths[SpriteAssets::Suburbs] = "./res/sprites/Suburbs.png";
    assetPaths[SpriteAssets::Lakes] = "./res/sprites/Lakes.png";
    assetPaths[SpriteAssets::Deserts] = "./res/sprites/Deserts.png";

    assetPaths[SpriteAssets::SelectorBackground] =
            "./res/sprites/SelectorBackground.png";
}

SpriteManager &SpriteManager::getInstance() {
    if (!instance.has_value()) {
        instance = SpriteManager{};
    }

    return instance.value();
}

olc::Renderable &SpriteManager::getSprite(SpriteAssets asset) {
    if (loadedSprites.find(asset) == loadedSprites.end()) {
        loadAsset(asset);
    }

    return loadedSprites[asset];
}

void SpriteManager::loadAsset(SpriteAssets asset) {
    auto path = assetPaths[asset];

    if (loadedSprites[asset].Load(path) == olc::rcode::NO_FILE) {
        std::cerr << "Couldn't load file \"" << assetPaths[asset] << "\"!\n";
    }
}
