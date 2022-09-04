#include "Field.h"

#include "AssetSystem/SpriteManager.h"
#include "Scene/Airplane.h"
#include "Utils/Constants.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <unordered_map>
#include <utility>
#include <vector>

void Field::init(std::array<std::array<CloudState, 16>, 16> initialState,
                 std::array<std::array<CloudState, 16>, 16> winState) {
    this->clouds = initialState;
    this->targetState = winState;
    this->initialState = initialState;

    initBackground();
    initSeparator();
    initClouds();
}

bool Field::update(olc::PixelGameEngine *pge) {
    if (firstTurn) {
        firstTurn = false;
        return true;
    }
    if (airplane.update(pge)) {
        if (changingCloud.has_value()) {
            clouds[changingCloud->first.y][changingCloud->first.x] =
                    changingCloud->second;
            changingCloud.reset();
        }

        std::vector<CloudState> states = {
                CloudState::None,
                CloudState::Regular,
                CloudState::Rain,
                CloudState::Red,
                CloudState::Green,
                CloudState::Blue,
        };

        turnTimer = 0;

        return true;
    }

    animTimer += pge->GetElapsedTime();
    turnTimer += pge->GetElapsedTime();
    return false;
}

void Field::draw(olc::PixelGameEngine *pge) const {
    pge->DrawDecal({0, 0}, backgroundTexture.Decal());

    for (auto x = 0u; x < 16; x++) {
        for (auto y = 0u; y < 16; y++) {
            drawTile(pge, x, y);
        }
    }

    drawSeparators(pge);

    airplane.draw(pge);
}

void Field::drawTile(olc::PixelGameEngine *pge, uint32_t x, uint32_t y) const {
    for (auto &cloudGraphic : cloudGraphics[y][x]) {
        drawCloud(pge, cloudGraphic, x, y);
    }
}

void Field::drawSeparators(olc::PixelGameEngine *pge) const {
    pge->DrawDecal({0, 0}, separatorLine.Decal());
    pge->DrawRotatedDecal({0, 1}, separatorLine.Decal(), -PI / 2);

    for (auto i = 0; i < 16; i++) {
        auto offset = i * 32 + 31;

        pge->DrawDecal({static_cast<float>(offset), 0}, separatorLine.Decal());
        pge->DrawRotatedDecal({0, static_cast<float>(offset + 1)},
                              separatorLine.Decal(),
                              -PI / 2);
    }
}

void Field::initBackground() {
    backgroundTexture.Create(32 * 16, 32 * 16);

    std::vector<SpriteManager::SpriteAssets> assetTypes = {
            SpriteManager::SpriteAssets::Fields,
            SpriteManager::SpriteAssets::Forests,
            SpriteManager::SpriteAssets::Towns,
            SpriteManager::SpriteAssets::Suburbs,
            SpriteManager::SpriteAssets::Lakes,
            SpriteManager::SpriteAssets::Deserts,
    };

    std::vector<float> probabilities = {
            0.75,
            0.1,
            0.05,
            0.05,
            0.025,
            0.025,
    };

    std::vector<uint32_t> assetCounts;

    for (auto assetType : assetTypes) {
        auto &sprite = SpriteManager::getInstance().getSprite(assetType);

        assetCounts.push_back(sprite.Sprite()->width / 32);
    }

    for (auto x = 0u; x < 16; x++) {
        for (auto y = 0u; y < 16; y++) {
            auto typeRoll = rand() / static_cast<float>(RAND_MAX);

            uint32_t type = 0;
            for (size_t i = 0; i < assetTypes.size(); i++) {
                if (probabilities[i] >= typeRoll) {
                    type = i;
                    break;
                }
                typeRoll -= probabilities[i];
            }

            auto spriteType = assetTypes[type];
            auto spriteId = rand() % assetCounts[type];

            auto &sprite = SpriteManager::getInstance().getSprite(spriteType);
            auto xOffset = spriteId * 32;

            for (auto dx = 0u; dx < 32; dx++) {
                for (auto dy = 0u; dy < 32; dy++) {
                    backgroundTexture.Sprite()->SetPixel(
                            {static_cast<int>(x * 32 + dx),
                             static_cast<int>(y * 32 + dy)},
                            sprite.Sprite()->GetPixel(
                                    {static_cast<int>(xOffset + dx),
                                     static_cast<int>(dy)}));
                }
            }
        }
    }

    backgroundTexture.Decal()->Update();
}

void Field::initSeparator() {
    separatorLine.Create(1, 32 * 16);
    for (auto i = 0; i < 32 * 16; i++) {
        separatorLine.Sprite()->SetPixel({0, i},
                                         i % 4 < 2 ? olc::WHITE : olc::BLANK);
    }

    separatorLine.Decal()->Update();
}

void Field::initClouds() {
    for (auto i = 0u; i < 10; i++) {
        auto x = std::cos(i / 10.0f * PI * 2) / 2;
        auto y = std::sin(i / 10.0f * PI * 2) / 2;

        circleShape.emplace_back(x, y);
        circleUV.emplace_back(x + 0.5f, y + 0.5f);
    }

    for (auto x = 0u; x < 16; x++) {
        for (auto y = 0u; y < 16; y++) {
            initCloud(x, y);
        }
    }
}

void Field::initCloud(uint32_t x, uint32_t y) {
    for (auto dx = 0; dx < 3; dx++) {
        for (auto dy = 0; dy < 3; dy++) {
            auto xOffset = rand() % 6 - 3;
            auto yOffset = rand() % 6 - 3;

            auto xPos = xOffset + 32 / 3 * dx + 32 / 6;
            auto yPos = yOffset + 32 / 3 * dy + 32 / 6;

            auto maxRadius = rand() / static_cast<float>(RAND_MAX) * 10 + 10;
            uint8_t grey = rand() % 32 + (256 - 32);

            cloudGraphics[y][x].push_back(
                    {xPos, yPos, maxRadius, {grey, grey, grey}});
        }
    }
}

void Field::drawCloud(olc::PixelGameEngine *pge,
                      const CloudGraphic &cloudGraphic,
                      int32_t tileX,
                      int32_t tileY) const {
    if (clouds[tileY][tileX] == CloudState::None
        && (!changingCloud.has_value()
            || changingCloud->first != olc::vi2d{tileX, tileY})) {
        return;
    }

    auto currentRadius = cloudGraphic.maxRadius;
    auto radiusBob = std::sin(animTimer / 3 + tileX * 16 + tileY) * 2;
    auto currentColor = cloudColors[clouds[tileY][tileX]];

    if (changingCloud.has_value()
        && changingCloud->first == olc::vi2d{tileX, tileY}) {
        if (changingCloud->second == CloudState::None) {
            currentRadius = std::max(
                    0.0f,
                    currentRadius - turnTimer * 30 / Airplane::moveTime);
        } else if (clouds[tileY][tileX] == CloudState::None) {
            currentRadius = std::min(cloudGraphic.maxRadius, turnTimer * 60);
            currentColor = cloudColors[changingCloud->second];
        } else {
            auto nextColor = cloudColors[changingCloud->second];
            auto lerp = turnTimer / Airplane::moveTime;

            currentColor = olc::PixelLerp(currentColor, nextColor, lerp);
        }
    }

    std::vector<olc::vf2d> points;
    points.reserve(circleShape.size());
    for (auto point : circleShape) {
        points.push_back(
                point * (currentRadius + radiusBob)
                + olc::vi2d{
                        static_cast<int>(tileX * 32 + cloudGraphic.xOffset),
                        static_cast<int>(tileY * 32 + cloudGraphic.yOffset)});
    }

    auto mixedColor =
            olc::Pixel{static_cast<uint8_t>(cloudGraphic.baseColor.r
                                            * (currentColor.r / 255.0f)),
                       static_cast<uint8_t>(cloudGraphic.baseColor.g
                                            * (currentColor.g / 255.0f)),
                       static_cast<uint8_t>(cloudGraphic.baseColor.b
                                            * (currentColor.b / 255.0f))};
    pge->DrawPolygonDecal(nullptr, points, circleUV, mixedColor);
}

std::unordered_map<Field::CloudState, olc::Pixel> Field::cloudColors = {
        {CloudState::None, olc::WHITE},
        {CloudState::Regular, olc::WHITE},
        {CloudState::Rain, {107, 107, 107}},
        {CloudState::Red, {255, 122, 122}},
        {CloudState::Green, {122, 255, 122}},
        {CloudState::Blue, {122, 122, 255}},
};

void Field::turnLeft() {
    airplane.turnLeft();
}

void Field::turnRight() {
    airplane.turnRight();
}

olc::vi2d Field::getPlanePosition() const {
    return airplane.getPosition();
}

void Field::reset() {
    clouds = initialState;
    airplane.reset();
    firstTurn = true;
    changingCloud.reset();
    animTimer = 0;
    turnTimer = 0;
}

void Field::createCloud() {
    changingCloud = std::make_pair(airplane.getPosition(), CloudState::Regular);
}

void Field::paintCloud(CloudColor color) {
    switch (color) {
    case CloudColor::Red:
        changingCloud = std::make_pair(airplane.getPosition(), CloudState::Red);
        break;
    case CloudColor::Green:
        changingCloud =
                std::make_pair(airplane.getPosition(), CloudState::Green);
        break;
    case CloudColor::Blue:
        changingCloud =
                std::make_pair(airplane.getPosition(), CloudState::Blue);
        break;
    }
}

Airplane::Direction Field::getPlaneDirection() const {
    return airplane.getDirection();
}
