#include "Selector.h"

#include "AssetSystem/SpriteManager.h"
#include "BiggerNode.h"
#include "ConstantNode.h"
#include "NodeSystem/IfNode.h"
#include "NodeSystem/TurnLeftNode.h"
#include "NodeSystem/TurnRightNode.h"
#include "WaitNode.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <vector>

void Selector::init(olc::PixelGameEngine *pge) {
    this->pge = pge;
}

bool Selector::update() {
    if (!isOpen) {
        return false;
    }

    if (pge->TextEntryGetString().size() > 15) {
        pge->TextEntryEnable(true, pge->TextEntryGetString().substr(0, 15));
    }

    matches = getMatches();

    if (pge->GetKey(olc::UP).bPressed) {
        selected = std::max(0, selected - 1);
    }

    auto maxSelect = std::min(static_cast<int>(matches.size()), 6);
    if (pge->GetKey(olc::DOWN).bPressed) {
        selected = std::min(maxSelect - 1, selected + 1);
    }

    if (prevSearch != pge->TextEntryGetString()) {
        selected = 0;
        prevSearch = pge->TextEntryGetString();
    }

    if (pge->GetKey(olc::ENTER).bPressed && matches.size() != 0) {
        close();
        return true;
    }

    if (pge->GetKey(olc::ESCAPE).bPressed) {
        close();
        return false;
    }

    auto mousePos = pge->GetMousePos();
    if (mousePos.x >= position.x + 3 && mousePos.x <= position.x + 296) {
        auto hoverId = (mousePos.y - position.y - 27) / 20;
        if (hoverId >= 0 && hoverId < maxSelect) {
            selected = hoverId;
            if (pge->GetMouse(0).bPressed) {
                close();
                return true;
            }
        }
    }

    if (pge->GetMouse(1).bPressed) {
        close();
        return false;
    }

    return false;
}

void Selector::draw() const {
    if (!isOpen) {
        return;
    }

    auto &sprite = SpriteManager::getInstance().getSprite(
            SpriteManager::SpriteAssets::SelectorBackground);

    pge->DrawDecal(position, sprite.Decal());

    pge->DrawStringPropDecal(position + olc::vf2d{5, 5},
                             pge->TextEntryGetString(),
                             olc::WHITE,
                             {2, 2});
    auto cursorPos = pge->TextEntryGetCursor();
    auto textBeforeCursor = pge->TextEntryGetString().substr(0, cursorPos);
    auto textWidth = pge->GetTextSizeProp(textBeforeCursor).x;

    pge->DrawLineDecal(
            position + olc::vf2d{static_cast<float>(5 + textWidth * 2), 5},
            position
                    + olc::vf2d{static_cast<float>(5 + textWidth * 2), 5 + 16});

    for (auto i = 0u; i < std::min(static_cast<size_t>(6), matches.size());
         i++) {
        pge->DrawStringPropDecal(
                position + olc::vf2d{5, static_cast<float>(32 + i * 18)},
                nodeTypeToName(matches.at(i)),
                olc::WHITE,
                {2, 2});
    }

    if (matches.size() != 0) {
        pge->FillRectDecal(position + olc::vi2d{3, 28 + selected * 18},
                           {294, 20},
                           {255, 255, 255, 64});
    }
}

void Selector::open(olc::vf2d position) {
    this->position = position;
    isOpen = true;
    pge->TextEntryEnable(true);
    selected = 0;
}

void Selector::close() {
    isOpen = false;
    pge->TextEntryEnable(false);
}

std::string Selector::nodeTypeToName(NodeType nodeType) {
    switch (nodeType) {
    case NodeType::TurnLeftNode:
        return "Turn Left";
    case NodeType::TurnRightNode:
        return "Turn Right";
    case NodeType::WaitNode:
        return "Wait";
    case NodeType::BiggerNode:
        return "Greater";
    case NodeType::IfNode:
        return "If";
    case NodeType::ConstantNode:
        return "Constant";
    }
    return "";
}

std::unique_ptr<Node> Selector::nodeTypeToNode(NodeType nodeType,
                                               olc::vf2d position) {
    switch (nodeType) {
    case NodeType::TurnLeftNode:
        return std::make_unique<TurnLeftNode>(position);
    case NodeType::TurnRightNode:
        return std::make_unique<TurnRightNode>(position);
    case NodeType::WaitNode:
        return std::make_unique<WaitNode>(position);
    case NodeType::BiggerNode:
        return std::make_unique<BiggerNode>(position);
    case NodeType::IfNode:
        return std::make_unique<IfNode>(position);
    case NodeType::ConstantNode:
        return std::make_unique<ConstantNode>(position);
    }
}

const std::vector<Selector::NodeType> Selector::nodeTypes = {
        NodeType::TurnLeftNode,
        NodeType::TurnRightNode,
        NodeType::WaitNode,
        NodeType::BiggerNode,
        NodeType::IfNode,
        NodeType::ConstantNode,
};

std::vector<Selector::NodeType> Selector::getMatches() const {
    auto searchStr = pge->TextEntryGetString();

    std::vector<NodeType> matches{nodeTypes};
    matches.erase(std::remove_if(matches.begin(),
                                 matches.end(),
                                 [&](const auto &node) {
                                     auto str = nodeTypeToName(node);
                                     return std::search(
                                                    str.begin(),
                                                    str.end(),
                                                    searchStr.begin(),
                                                    searchStr.end(),
                                                    [](char ch1, char ch2) {
                                                        return std::tolower(ch1)
                                                               == std::tolower(
                                                                       ch2);
                                                    })
                                            == str.end();
                                 }),
                  matches.end());

    std::sort(matches.begin(), matches.end());

    return matches;
}

std::unique_ptr<Node> Selector::getResult() const {
    return nodeTypeToNode(matches.at(selected), position);
}

bool Selector::isSelectorOpen() const {
    return isOpen;
}
