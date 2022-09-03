#pragma once

#include "NodeSystem/PinType.h"
#include "Utils/Drawing.h"
#include "olcPixelGameEngine.h"

#include <functional>
#include <tuple>

class InputPin;

class OutputPin;

class Connection {
public:
    Connection(OutputPin &sourcePin, InputPin &targetPin, PinType pinType);
    ~Connection();
    void sendData(PinData data);
    void draw(olc::PixelGameEngine *pge) const;
    bool isPointOver(olc::vf2d point) const;

    OutputPin &getSourcePin();
    InputPin &getTargetPin();

private:
    std::tuple<olc::vf2d, olc::vf2d, olc::vf2d, olc::vf2d> getPoints() const;
    bool connectedToSelf() const;

    OutputPin &sourcePin;
    InputPin &targetPin;
    PinType pinType;
};
