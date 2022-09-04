#pragma once

#include "NodeSystem/EvaluationResult.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"

class LocationNode : public Node {
public:
    LocationNode(olc::vf2d position);

    EvaluationResult evaluate(Field &field) override;
};
