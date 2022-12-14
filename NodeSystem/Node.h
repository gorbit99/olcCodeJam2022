#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/NodePin.h"
#include "NodeSystem/OutputPin.h"
#include "Scene/Field.h"
#include "olcPixelGameEngine.h"

#include <cstdint>
#include <functional>
#include <optional>
#include <vector>

class Node {
public:
    Node(olc::Renderable &graphic, olc::vf2d position);
    virtual ~Node() {
    }

    // TODO: Refactor to use a camera
    virtual void draw(olc::PixelGameEngine *pge) const;
    olc::vf2d getCenter() const;
    olc::vi2d getSize() const;

    bool isPointOver(olc::vf2d point) const;

    std::vector<InputPin> &getInputPins();
    std::vector<OutputPin> &getOutputPins();

    void setPosition(olc::vf2d position);

    virtual EvaluationResult evaluate(Field &field) = 0;
    virtual bool interact(olc::PixelGameEngine *pge);

protected:
    std::optional<std::reference_wrapper<Node>> connectedFromPin(uint32_t pin);

    std::vector<InputPin> inputPins;
    std::vector<OutputPin> outputPins;

private:
    std::reference_wrapper<olc::Renderable> graphic;
    olc::vf2d position;
};
