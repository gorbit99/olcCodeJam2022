#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class PaintRedNode : public Node {
public:
    PaintRedNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
