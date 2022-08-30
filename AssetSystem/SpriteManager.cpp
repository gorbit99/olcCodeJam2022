#include "SpriteManager.h"

#include <iostream>
#include <optional>

std::optional<SpriteManager> SpriteManager::instance;

SpriteManager::SpriteManager() {
    assetPaths[SpriteAssets::StartNode] = "./res/sprites/StartNode.png";
    assetPaths[SpriteAssets::PinIn] = "./res/sprites/PinIn.png";
    assetPaths[SpriteAssets::PinOut] = "./res/sprites/PinOut.png";
}

SpriteManager &SpriteManager::getInstance() {
    if (!instance.has_value()) {
        instance = SpriteManager{};
    }

    return instance.value();
}

std::reference_wrapper<olc::Renderable>
        SpriteManager::getSprite(SpriteAssets asset) {
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
