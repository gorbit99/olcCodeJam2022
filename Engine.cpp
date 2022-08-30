#include "Engine.h"

#include <memory>

Game::Game() {
    sAppName = "WeatherBringer ltd.";
}

bool Game::OnUserCreate() {
    startNode = std::make_unique<StartNode>(olc::vf2d{20, 20});
    return true;
}

bool Game::OnUserUpdate(float fElapsedTime) {
    Clear(olc::BLACK);

    startNode->draw(this);

    return true;
}
