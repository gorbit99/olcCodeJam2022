#include "Evaluator.h"

void Evaluator::init(std::unique_ptr<Node> &startNode) {
    currentNode = *startNode;
}

void Evaluator::step(Field &field) {
    if (!currentNode.has_value()) {
        return;
    }

    auto stop = false;

    while (!stop) {
        std::cout << "Stepped\n";
        auto result = currentNode.value().get().evaluate(field);
        stop = result.turnEnded || !result.nextNode.has_value();
        currentNode = result.nextNode;
    }
}
