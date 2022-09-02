#include "Engine.h"

#include <memory>

Game::Game() {
    sAppName = "WeatherBringer ltd.";
}

bool Game::OnUserCreate() {
    board.init();
    return true;
}

bool Game::OnUserUpdate(float fElapsedTime) {
    Clear(olc::BLACK);

    board.update(this);

    board.draw(this);
    field.draw(this);

    return true;
}
