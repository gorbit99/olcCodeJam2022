#pragma once

#include "NodeSystem/NodePin.h"
#include "olcPixelGameEngine.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class Selector {
public:
    void init(olc::PixelGameEngine *pge);
    bool update();
    void draw() const;
    void open(olc::vf2d position);
    std::unique_ptr<Node> getResult() const;
    bool isSelectorOpen() const;

private:
    enum class NodeType {
        TurnLeftNode,
        TurnRightNode,
        WaitNode,
        BiggerNode,
        SmallerNode,
        IfNode,
        ConstantNode,
    };

    void close();
    std::vector<NodeType> getMatches() const;

    static std::string nodeTypeToName(NodeType nodeType);
    static std::unique_ptr<Node> nodeTypeToNode(NodeType nodeType,
                                                olc::vf2d position);

    bool isOpen = false;
    olc::PixelGameEngine *pge;
    olc::vf2d position;
    std::vector<NodeType> matches;
    int32_t selected;
    std::string prevSearch;

    static const std::vector<NodeType> nodeTypes;
};
