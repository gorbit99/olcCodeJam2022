#include <iostream>
#define OLC_PGE_APPLICATION
#include "Engine.h"

int main() {
    Game game;
    if (game.Construct(1024, 512, 1, 1)) {
        game.Start();
    } else {
        std::cerr << "Couldn't start application!\n";
    }
    return 0;
}
