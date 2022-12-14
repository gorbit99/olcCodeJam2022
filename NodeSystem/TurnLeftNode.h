#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class TurnLeftNode : public Node {
public:
    TurnLeftNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
