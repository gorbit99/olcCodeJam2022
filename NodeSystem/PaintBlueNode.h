#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class PaintBlueNode : public Node {
public:
    PaintBlueNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
