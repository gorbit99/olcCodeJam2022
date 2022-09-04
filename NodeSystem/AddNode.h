#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class AddNode : public Node {
public:
    AddNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
