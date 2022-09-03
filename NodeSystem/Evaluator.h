#pragma once

#include "Node.h"
#include "Scene/Field.h"

#include <functional>
#include <optional>

class Evaluator {
public:
    void init(std::unique_ptr<Node> &startNode);
    void step(Field &scene);

private:
    std::optional<std::reference_wrapper<Node>> currentNode;
};
