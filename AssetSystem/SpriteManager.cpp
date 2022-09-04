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
    assetPaths[SpriteAssets::AndNode] = "./res/sprites/AndNode.png";
    assetPaths[SpriteAssets::OrNode] = "./res/sprites/OrNode.png";
    assetPaths[SpriteAssets::EqualNode] = "./res/sprites/EqualNode.png";
    assetPaths[SpriteAssets::IfNode] = "./res/sprites/IfNode.png";
    assetPaths[SpriteAssets::ConstantNode] = "./res/sprites/ConstantNode.png";
    assetPaths[SpriteAssets::LocationNode] = "./res/sprites/LocationNode.png";
    assetPaths[SpriteAssets::CloudNode] = "./res/sprites/CloudNode.png";
    assetPaths[SpriteAssets::RedPaintNode] = "./res/sprites/RedPaintNode.png";
    assetPaths[SpriteAssets::GreenPaintNode] =
            "./res/sprites/GreenPaintNode.png";
    assetPaths[SpriteAssets::BluePaintNode] = "./res/sprites/BluePaintNode.png";
    assetPaths[SpriteAssets::DirectionNode] = "./res/sprites/DirectionNode.png";
    assetPaths[SpriteAssets::AddNode] = "./res/sprites/AddNode.png";
    assetPaths[SpriteAssets::SubtractNode] = "./res/sprites/SubtractNode.png";
    assetPaths[SpriteAssets::MultiplyNode] = "./res/sprites/MultiplyNode.png";
    assetPaths[SpriteAssets::DivideNode] = "./res/sprites/DivideNode.png";

    assetPaths[SpriteAssets::Airplane] = "./res/sprites/Airplane.png";

    assetPaths[SpriteAssets::Fields] = "./res/sprites/Fields.png";
    assetPaths[SpriteAssets::Forests] = "./res/sprites/Forests.png";
    assetPaths[SpriteAssets::Towns] = "./res/sprites/Towns.png";
    assetPaths[SpriteAssets::Suburbs] = "./res/sprites/Suburbs.png";
    assetPaths[SpriteAssets::Lakes] = "./res/sprites/Lakes.png";
    assetPaths[SpriteAssets::Deserts] = "./res/sprites/Deserts.png";

    assetPaths[SpriteAssets::SelectorBackground] =
            "./res/sprites/SelectorBackground.png";

    assetPaths[SpriteAssets::JavidCharacter] =
            "./res/sprites/JavidCharacter0.png";

    assetPaths[SpriteAssets::StartButton] = "./res/sprites/StartButton.png";
    assetPaths[SpriteAssets::StopButton] = "./res/sprites/StopButton.png";
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
