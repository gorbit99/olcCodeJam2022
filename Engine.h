#pragma once

#include "NodeSystem/Board.h"
#include "NodeSystem/Node.h"
#include "NodeSystem/StartNode.h"
#include "NodeSystem/TurnLeftNode.h"
#include "olcPixelGameEngine.h"

class Game : public olc::PixelGameEngine {
public:
    Game();
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

    Board board;
};
