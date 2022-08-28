#include "Engine.h"

Game::Game() {
    sAppName = "WeatherBringer ltd.";
}

bool Game::OnUserCreate() {
    return true;
}

bool Game::OnUserUpdate(float fElapsedTime) {
    Clear(olc::BLACK);

    startNode.draw(this, {20, 20});

    return true;
}
