#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class ConstantNode : public Node {
public:
    ConstantNode(olc::vf2d position);
    EvaluationResult evaluate(Field &field) override;

    void draw(olc::PixelGameEngine *pge) const override;
    bool interact(olc::PixelGameEngine *pge) override;

    int32_t value = 0;
};
