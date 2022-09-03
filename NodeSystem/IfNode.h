#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class IfNode : public Node {
public:
    IfNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
