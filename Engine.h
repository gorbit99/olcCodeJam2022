#pragma once

#include "NodeSystem/StartNode.h"
#include "olcPixelGameEngine.h"

class Game : public olc::PixelGameEngine {
public:
    Game();
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

private:
    StartNode startNode;
};
