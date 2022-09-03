#pragma once

#include "olcPixelGameEngine.h"

#include <unordered_map>
#include <variant>

enum class PinType {
    Flow,
    Number,
    Logic,
};

const std::unordered_map<PinType, olc::Pixel> pinTypeColors = {
        {PinType::Flow, olc::RED},
        {PinType::Logic, olc::GREEN},
        {PinType::Number, olc::YELLOW}};

typedef std::variant<bool, float, std::monostate> PinData;
