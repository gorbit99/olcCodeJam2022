#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class OrNode : public Node {
public:
    OrNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
