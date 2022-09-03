#include "Engine.h"

#include <memory>

Game::Game() {
    sAppName = "WeatherBringer ltd.";
}

bool Game::OnUserCreate() {
    board.init(this);
    field.init();
    return true;
}

bool run = false;

bool Game::OnUserUpdate(float) {
    Clear(olc::BLACK);

    board.update(this);
    if (run) {
        if (field.update(this)) {
            board.evaluateStep(field);
        }
    }

    if (GetKey(olc::SPACE).bPressed) {
        run = true;
    }

    board.draw(this);
    field.draw(this);

    return true;
}
