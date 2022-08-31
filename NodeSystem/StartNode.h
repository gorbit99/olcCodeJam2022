#pragma once

#include "NodeSystem/InputPin.h"
#include "NodeSystem/Node.h"
#include "NodeSystem/NodePin.h"
#include "NodeSystem/OutputPin.h"

class StartNode : public Node {
public:
    StartNode(olc::vf2d position);
};
