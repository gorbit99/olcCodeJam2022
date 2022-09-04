#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class CloudNode : public Node {
public:
    CloudNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
