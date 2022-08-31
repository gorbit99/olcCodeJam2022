#pragma once

#include "NodeSystem/NodePin.h"
#include "NodeSystem/OutputPin.h"
#include "NodeSystem/PinType.h"

#include <functional>
#include <optional>

class InputPin : public NodePin {
public:
    InputPin(olc::vf2d offset, PinType pinType, Node &parent);
    ~InputPin();
    PinData takeData();
    const PinData &getData() const;
    void setData(PinData data);
    void draw(olc::PixelGameEngine *pge) const override;
    void connectTo(OutputPin &outputPin);
    void disconnect();
    bool isConnected() const override;

private:
    std::optional<PinData> data;

    std::optional<std::reference_wrapper<OutputPin>> connectedPin;
};
