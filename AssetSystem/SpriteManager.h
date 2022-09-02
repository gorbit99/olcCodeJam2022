#pragma once

#include "olcPixelGameEngine.h"

#include <functional>
#include <optional>
#include <string>
#include <unordered_map>

class SpriteManager {
public:
    enum class SpriteAssets {
        PinIn,
        PinOut,
        StartNode,
        TurnLeftNode,
        Airplane,
    };

    static SpriteManager &getInstance();

    olc::Renderable &getSprite(SpriteAssets asset);

private:
    SpriteManager();

    static std::optional<SpriteManager> instance;

    std::unordered_map<SpriteAssets, olc::Renderable> loadedSprites;

    std::unordered_map<SpriteAssets, std::string> assetPaths;

    void loadAsset(SpriteAssets asset);
};
