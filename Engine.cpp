#include "Engine.h"

#include "DialogueSystem/Dialogue.h"
#include "Scene/Field.h"

#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <variant>
#include <vector>

Game::Game() {
    sAppName = "WeatherBringer ltd.";
}

bool Game::OnUserCreate() {
    loadLevels();
    board.init(this);
    field.init(levels.at(currentDialogue).first,
               levels.at(currentDialogue).second);
    return true;
}

bool run = false;

bool Game::OnUserUpdate(float) {
    switch (state) {
    case State::Game: {
        board.update(this);
        if (run) {
            if (field.update(this)) {
                board.evaluateStep(field);
            }
        }

        auto planePosition = field.getPlanePosition();

        if (planePosition.x < 0 || planePosition.y < 0 || planePosition.x >= 16
            || planePosition.y >= 16) {
            run = false;
            resetLevel();
            // TODO: win or lose condition
        }

        if (GetKey(olc::SPACE).bPressed) {
            run = !run;
            if (!run) {
                resetLevel();
            }
        }

        board.draw(this);
        field.draw(this);

        auto startButtonSprite = run ? SpriteManager::SpriteAssets::StopButton
                                     : SpriteManager::SpriteAssets::StartButton;
        auto &startButtonGraphic =
                SpriteManager::getInstance().getSprite(startButtonSprite);
        olc::vi2d startButtonPos{
                (512 + 600) / 2 - startButtonGraphic.Sprite()->width / 2,
                100 - startButtonGraphic.Sprite()->height / 2,
        };

        if (GetMouse(0).bPressed) {
            auto mousePos = GetMousePos();
            if (mousePos.x >= startButtonPos.x
                && mousePos.x <= startButtonPos.x
                                         + startButtonGraphic.Sprite()->width
                && mousePos.y >= startButtonPos.y
                && mousePos.y
                           <= startButtonPos.y
                                      + startButtonGraphic.Sprite()->height) {
                run = !run;
                if (!run) {
                    resetLevel();
                }
            }
        }

        FillRectDecal({512, 0}, {600 - 512, 512}, olc::GREY);
        DrawDecal(startButtonPos, startButtonGraphic.Decal());
        break;
    }
    case State::Dialoue:
        if (dialogues.at(currentDialogue).update(this)) {
            fadeOut.start(1, [&]() { state = State::Game; });
        }
        dialogues.at(currentDialogue).draw(this);
        break;
    }

    fadeOut.update(this);
    fadeOut.draw(this);

    return true;
}

void Game::loadLevels() {
    std::vector<Field::CloudState> states{
            Field::CloudState::None,
            Field::CloudState::Regular,
            Field::CloudState::Rain,
            Field::CloudState::Red,
            Field::CloudState::Green,
            Field::CloudState::Blue,
    };

    std::ifstream levelsFile;
    levelsFile.open("res/levels/levels.txt");
    std::string line;
    while (std::getline(levelsFile, line)) {
        std::ifstream levelFile;
        levelFile.open(line);

        std::string customer;
        std::getline(levelFile, customer);

        std::string numberOfLinesStr;
        std::getline(levelFile, numberOfLinesStr);
        auto numberOfLines = std::stoi(numberOfLinesStr);

        std::vector<std::string> lines;
        for (auto i = 0; i < numberOfLines; i++) {
            std::string text;
            std::getline(levelFile, text);
            lines.push_back(text);
        }

        std::array<std::array<Field::CloudState, 16>, 16> initialState;
        std::array<std::array<Field::CloudState, 16>, 16> targetState;

        for (auto y = 0; y < 16; y++) {
            std::string fieldLine;
            std::getline(levelFile, fieldLine);
            std::stringstream ss{fieldLine};
            for (auto x = 0; x < 16; x++) {
                std::string cloud;
                std::getline(ss, cloud, ',');
                int cloudId = std::stoi(cloud);
                initialState[y][x] = states[cloudId];
            }
        }

        for (auto y = 0; y < 16; y++) {
            std::string fieldLine;
            std::getline(levelFile, fieldLine);
            std::stringstream ss{fieldLine};
            for (auto x = 0; x < 16; x++) {
                std::string cloud;
                std::getline(ss, cloud, ',');
                int cloudId = std::stoi(cloud);
                targetState[y][x] = states[cloudId];
            }
        }

        Dialogue::Character dialogueCharacter = Dialogue::Character::Javid;
        if (customer == "Javid") {
            dialogueCharacter = Dialogue::Character::Javid;
        } else if (customer == "Moros") {
            dialogueCharacter = Dialogue::Character::Moros;
        } else if (customer == "Gorbit") {
            dialogueCharacter = Dialogue::Character::Gorbit;
        }

        dialogues.push_back({
                dialogueCharacter,
                lines,
        });
        levels.push_back(std::make_pair(initialState, targetState));
    }
}

void Game::resetLevel() {
    field.reset();
    board.reset();
}
