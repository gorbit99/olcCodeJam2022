#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class SmallerNode : public Node {
public:
    SmallerNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
