#pragma once

#include "olcPixelGameEngine.h"

#include <unordered_map>

class Node;

enum class PinType {
    Flow,
    Number,
    Logic,
};

template<typename DataType>
class NodePin {
public:
    NodePin(olc::vf2d offset, PinType pinType)
            : offset{offset},
              pinType{pinType} {
    }

    olc::vf2d getOffset() const {
        return offset;
    }
    virtual void draw(olc::PixelGameEngine *pge, Node &parent) = 0;

protected:
    olc::Pixel getColor() const {
        return pinColorMap.at(pinType);
    }

private:
    PinType pinType;
    static const std::unordered_map<PinType, olc::Pixel> pinColorMap;
    olc::vf2d offset;
};

template<typename DataType>
const std::unordered_map<PinType, olc::Pixel> NodePin<DataType>::pinColorMap = {
        {PinType::Flow, olc::RED},
        {PinType::Logic, olc::GREEN},
        {PinType::Number, olc::YELLOW}};
