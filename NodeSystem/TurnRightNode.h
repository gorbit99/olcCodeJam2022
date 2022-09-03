#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class TurnRightNode : public Node {
public:
    TurnRightNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
