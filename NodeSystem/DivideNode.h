#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class DivideNode : public Node {
public:
    DivideNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
