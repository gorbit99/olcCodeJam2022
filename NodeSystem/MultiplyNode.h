#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class MultiplyNode : public Node {
public:
    MultiplyNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
