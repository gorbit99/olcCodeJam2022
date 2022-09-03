#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class BiggerNode : public Node {
public:
    BiggerNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
