#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class WaitNode : public Node {
public:
    WaitNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
