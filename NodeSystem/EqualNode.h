#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class EqualNode : public Node {
public:
    EqualNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
