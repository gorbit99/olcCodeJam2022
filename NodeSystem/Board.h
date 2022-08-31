#pragma once

#include "NodeSystem/Node.h"

#include <functional>
#include <memory>
#include <optional>
#include <vector>

#undef None

class Board {
public:
    Board() noexcept;
    void init();
    void draw(olc::PixelGameEngine *pge) const;
    void update(olc::PixelGameEngine *pge);

private:
    bool getClickedNode(olc::PixelGameEngine *pge);
    bool getClickedPin(olc::PixelGameEngine *pge);
    void checkDragStart(olc::PixelGameEngine *pge);
    void handleDragging(olc::PixelGameEngine *pge);
    void handleNodeDragging(olc::PixelGameEngine *pge);
    void handlePinDragging(olc::PixelGameEngine *pge);
    void drawDraggedConnection(olc::PixelGameEngine *pge,
                               olc::vf2d start,
                               olc::vf2d middle) const;
    void handleConnectionRightClick(olc::PixelGameEngine *pge);
    void handleNodeRightClick(olc::PixelGameEngine *pge);

    enum class State {
        None,
        DraggingNode,
        ConnectingInputPin,
        ConnectingOutputPin,
    };

    State state = State::None;
    std::vector<std::unique_ptr<Node>> nodes;
    std::optional<std::size_t> grabbedNode;
    std::optional<std::reference_wrapper<InputPin>> grabbedInputPin;
    std::optional<std::reference_wrapper<OutputPin>> grabbedOutputPin;
};
