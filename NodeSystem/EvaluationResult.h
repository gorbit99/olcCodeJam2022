#pragma once

#include <functional>
#include <optional>

class Node;

struct EvaluationResult {
    std::optional<std::reference_wrapper<Node>> nextNode;
    bool turnEnded;
};
