#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class PaintGreenNode : public Node {
public:
    PaintGreenNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
