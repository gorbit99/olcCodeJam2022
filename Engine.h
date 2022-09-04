#pragma once

#include "DialogueSystem/Dialogue.h"
#include "NodeSystem/Board.h"
#include "NodeSystem/Node.h"
#include "NodeSystem/StartNode.h"
#include "NodeSystem/TurnLeftNode.h"
#include "Scene/Field.h"
#include "Utils/FadeOut.h"
#include "olcPixelGameEngine.h"

#include <array>
#include <cstdint>
#include <vector>

class Game : public olc::PixelGameEngine {
public:
    Game();
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

    Board board;
    Field field;

private:
    enum class State {
        Dialoue,
        Game,
    };

    void loadLevels();
    void resetLevel();

    State state = State::Dialoue;
    std::vector<Dialogue> dialogues;
    uint32_t currentDialogue = 0;
    FadeOut fadeOut;

    std::vector<std::pair<std::array<std::array<Field::CloudState, 16>, 16>,
                          std::array<std::array<Field::CloudState, 16>, 16>>>
            levels;
};
