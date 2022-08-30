
#pragma once

#include "AssetSystem/SpriteManager.h"
#include "Node.h"
#include "NodeSystem/NodePin.h"

#include <optional>

template<typename DataType>
class OutputPin : public NodePin<DataType> {
public:
    OutputPin(olc::vf2d offset, PinType pinType)
            : NodePin<DataType>{offset, pinType} {
    }

    void sendData(DataType &data) {
    }

    void setData(DataType data) {
        this->data = data;
    }

    void draw(olc::PixelGameEngine *pge, olc::vf2d parentCenter) override {
        auto sprite = SpriteManager::getInstance().getSprite(
                SpriteManager::SpriteAssets::PinIn);

        auto halfSize = olc::vi2d{
                sprite.get().Sprite()->width,
                sprite.get().Sprite()->height,
        };

        auto color = NodePin<DataType>::getColor();

        pge->DrawDecal(parentCenter + NodePin<DataType>::getOffset() * 2
                               - halfSize,
                       sprite.get().Decal(),
                       {2, 2},
                       color);
    }

private:
    std::optional<Connection>
};
