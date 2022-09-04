#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class SubtractNode : public Node {
public:
    SubtractNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
