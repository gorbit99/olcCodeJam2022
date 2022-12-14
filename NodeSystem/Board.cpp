#include "Board.h"

#include "NodeSystem/NodePin.h"
#include "NodeSystem/StartNode.h"
#include "TurnLeftNode.h"
#include "Utils/Drawing.h"

#include <algorithm>
#include <iterator>
#include <memory>

Board::Board() noexcept {
}

void Board::init(olc::PixelGameEngine *pge) {
    nodes.emplace_back(new StartNode({650, 30}));

    selector.init(pge);
    evaluator.init(nodes.at(0));
}

void Board::draw(olc::PixelGameEngine *pge) const {
    for (auto &node : nodes) {
        node->draw(pge);
    }

    if (state == State::ConnectingInputPin) {
        auto pinStart = grabbedInputPin->get().getPosition();
        auto pinEnd = pinStart + olc::vf2d{-10, 0};

        drawDraggedConnection(pge, pinStart, pinEnd);
    }
    if (state == State::ConnectingOutputPin) {
        auto pinStart = grabbedOutputPin->get().getPosition();
        auto pinEnd = pinStart + olc::vf2d{10, 0};

        drawDraggedConnection(pge, pinStart, pinEnd);
    }

    selector.draw();
}

void Board::update(olc::PixelGameEngine *pge) {
    if (selector.isSelectorOpen()) {
        if (selector.update()) {
            nodes.push_back(selector.getResult());
        }
        return;
    }
    checkDragStart(pge);
    handleDragging(pge);
    handleConnectionRightClick(pge);
    handleNodeRightClick(pge);
}

void Board::checkDragStart(olc::PixelGameEngine *pge) {
    if (pge->GetMousePos().x < 600) {
        return;
    }

    if (!pge->GetMouse(0).bPressed || state != State::None) {
        return;
    }

    if (getClickedPin(pge)) {
        return;
    }

    if (getClickedNode(pge)) {
        return;
    }

    selector.open(pge->GetMousePos());
}

bool Board::getClickedNode(olc::PixelGameEngine *pge) {
    auto clickedNode =
            std::find_if(nodes.begin(), nodes.end(), [&](const auto &node) {
                return node.get()->isPointOver(pge->GetMousePos());
            });

    if (clickedNode == nodes.end()) {
        return false;
    }

    if (clickedNode->get()->interact(pge)) {
        return true;
    }

    state = State::DraggingNode;
    grabbedNode = std::distance(nodes.begin(), clickedNode);
    return true;
}

bool Board::getClickedPin(olc::PixelGameEngine *pge) {
    for (auto &node : nodes) {
        for (auto &inputPin : node->getInputPins()) {
            if (!inputPin.isPointOver(pge->GetMousePos())) {
                continue;
            }

            state = State::ConnectingInputPin;
            grabbedInputPin = inputPin;

            return true;
        }

        for (auto &outputPin : node->getOutputPins()) {
            if (outputPin.isConnected()
                || !outputPin.isPointOver(pge->GetMousePos())) {
                continue;
            }

            state = State::ConnectingOutputPin;
            grabbedOutputPin = outputPin;

            return true;
        }
    }

    return false;
}

void Board::handleDragging(olc::PixelGameEngine *pge) {
    if (pge->GetMousePos().x < 600) {
        return;
    }

    switch (state) {
    case State::None:
        break;
    case State::DraggingNode:
        handleNodeDragging(pge);
        break;
    case State::ConnectingInputPin:
    case State::ConnectingOutputPin:
        handlePinDragging(pge);
        break;
    }
}

void Board::handleNodeDragging(olc::PixelGameEngine *pge) {
    if (pge->GetMouse(0).bHeld) {
        nodes.at(grabbedNode.value())->setPosition(pge->GetMousePos());
    }

    if (pge->GetMouse(0).bReleased) {
        grabbedNode.reset();
        state = State::None;
    }
}

void Board::handlePinDragging(olc::PixelGameEngine *pge) {
    if (pge->GetMouse(0).bReleased) {
        auto found = false;
        for (auto &node : nodes) {
            if (state == State::ConnectingOutputPin) {
                for (auto &pin : node->getInputPins()) {
                    if (!pin.isPointOver(pge->GetMousePos())
                        || pin.getPinType()
                                   != grabbedOutputPin->get().getPinType()) {
                        continue;
                    }

                    grabbedOutputPin->get().connectTo(pin);
                    found = true;
                    break;
                }
            } else {
                for (auto &pin : node->getOutputPins()) {
                    if (pin.isConnected()
                        || !pin.isPointOver(pge->GetMousePos())
                        || pin.getPinType()
                                   != grabbedInputPin->get().getPinType()) {
                        continue;
                    }

                    pin.connectTo(grabbedInputPin.value());
                    found = true;
                    break;
                }
            }
            if (found) {
                break;
            }
        }

        state = State::None;
        grabbedInputPin.reset();
        grabbedOutputPin.reset();
    }
}

void Board::drawDraggedConnection(olc::PixelGameEngine *pge,
                                  olc::vf2d start,
                                  olc::vf2d middle) const {
    auto end = pge->GetMousePos();

    drawThickLine(pge, start, middle, 4, olc::YELLOW);
    drawThickLine(pge, middle, end, 4, olc::YELLOW);
}

void Board::handleConnectionRightClick(olc::PixelGameEngine *pge) {
    if (!pge->GetMouse(1).bPressed) {
        return;
    }

    for (auto &node : nodes) {
        for (auto &pin : node->getOutputPins()) {
            if (!pin.isConnected()) {
                continue;
            }
            auto &connection = pin.getConnection();
            if (connection.isPointOver(pge->GetMousePos())) {
                pin.disconnect();
                return;
            }
        }
    }
}

void Board::handleNodeRightClick(olc::PixelGameEngine *pge) {
    if (!pge->GetMouse(1).bPressed) {
        return;
    }

    nodes.erase(std::remove_if(nodes.begin(),
                               nodes.end(),
                               [&](const auto &node) {
                                   return &node != &nodes.at(0)
                                          && node->isPointOver(
                                                  pge->GetMousePos());
                               }),
                nodes.end());
}

void Board::evaluateStep(Field &field) {
    evaluator.step(field);
}

void Board::reset() {
    selector.reset();
    evaluator.init(nodes.at(0));
}
