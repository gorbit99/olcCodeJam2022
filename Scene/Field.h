#pragma once

#include "Airplane.h"
#include "AssetSystem/SpriteManager.h"
#include "olcPixelGameEngine.h"

#include <array>
#include <cstdint>
#include <optional>
#include <unordered_map>
#include <vector>

#undef None

class Field {
public:
    enum class CloudState {
        None,
        Regular,
        Rain,
        Red,
        Green,
        Blue,
    };

    void init(std::array<std::array<CloudState, 16>, 16> initialState,
              std::array<std::array<CloudState, 16>, 16> winState);
    bool update(olc::PixelGameEngine *pge);
    void draw(olc::PixelGameEngine *pge) const;
    void reset();

    void turnLeft();
    void turnRight();
    olc::vi2d getPlanePosition() const;
    void createCloud();
    enum class CloudColor {
        Red,
        Green,
        Blue,
    };
    void paintCloud(CloudColor color);
    Airplane::Direction getPlaneDirection() const;

private:
    struct CloudGraphic {
        int32_t xOffset;
        int32_t yOffset;
        float maxRadius;
        olc::Pixel baseColor;
    };

    void initBackground();
    void initSeparator();
    void initClouds();
    void initCloud(uint32_t x, uint32_t y);
    void drawTile(olc::PixelGameEngine *pge, uint32_t x, uint32_t y) const;
    void drawSeparators(olc::PixelGameEngine *pge) const;
    void drawCloud(olc::PixelGameEngine *pge,
                   const CloudGraphic &cloudGraphic,
                   int32_t tileX,
                   int32_t tileY) const;

    std::array<std::array<CloudState, 16>, 16> clouds;
    std::array<std::array<CloudState, 16>, 16> initialState;
    std::array<std::array<CloudState, 16>, 16> targetState;
    std::array<std::array<std::vector<CloudGraphic>, 16>, 16> cloudGraphics;
    Airplane airplane;

    olc::Renderable backgroundTexture;
    olc::Renderable separatorLine;

    std::vector<olc::vf2d> circleShape;
    std::vector<olc::vf2d> circleUV;

    float animTimer = 0;
    float turnTimer = 0;

    bool firstTurn = true;

    std::optional<std::pair<olc::vi2d, CloudState>> changingCloud;

    static std::unordered_map<CloudState, olc::Pixel> cloudColors;
};
