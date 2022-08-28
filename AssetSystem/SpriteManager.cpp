#include "SpriteManager.h"

#include <optional>

std::optional<SpriteManager> SpriteManager::instance;

SpriteManager::SpriteManager() {
    assetPaths[SpriteAssets::StartNode] = "./res/sprites/StartNode.png";
    assetPaths[SpriteAssets::Pin] = "./res/sprites/Pin.png";
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

    loadedSprites[asset].Load(path);
}
