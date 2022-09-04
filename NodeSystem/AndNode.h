#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class AndNode : public Node {
public:
    AndNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
