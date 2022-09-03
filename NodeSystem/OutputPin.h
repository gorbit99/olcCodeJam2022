#pragma once

#include "Connection.h"
#include "NodePin.h"
#include "PinType.h"

#include <optional>
#include <vector>

class Node;

class OutputPin : public NodePin {
public:
    OutputPin(olc::vf2d offset, PinType pinType, Node &parent);
    void sendData(PinData data);
    void connectTo(InputPin &other);
    void disconnect();
    void draw(olc::PixelGameEngine *pge) const override;
    Connection &getConnection();
    bool isConnected() const override;

private:
    std::optional<Connection> connection;
};
