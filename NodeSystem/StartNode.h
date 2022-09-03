#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"
#include "NodeSystem/NodePin.h"
#include "NodeSystem/OutputPin.h"
#include "Scene/Field.h"

class StartNode : public Node {
public:
    StartNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
