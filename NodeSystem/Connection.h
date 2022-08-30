#pragma once

#include "NodeSystem/InputType.h"
#include "NodeSystem/Node.h"

#include <functional>

template<typename ConnectionType>
class Connection {
public:
    Connection(InputType inputType);

private:
    std::reference_wrapper<Node> endTarget;
};
