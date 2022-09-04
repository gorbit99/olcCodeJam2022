#include "Dialogue.h"

#include <unordered_map>
#include <unordered_set>
#include <vector>

Dialogue::Dialogue(Character character, std::vector<std::string> lines)
        : character{character},
          lines{lines} {
}

bool Dialogue::update(olc::PixelGameEngine *pge) {
    if (done) {
        return false;
    }
    currentTimer += pge->GetElapsedTime();
    if (pge->GetKey(olc::ENTER).bPressed || pge->GetKey(olc::SPACE).bPressed) {
        auto lineTime = 0.0f;
        for (auto c : lines.at(currentLine)) {
            if (doubleTimeLetters.find(c) != doubleTimeLetters.end()) {
                lineTime += timePerLetter * 2;
            } else {
                lineTime += timePerLetter;
            }
        }
        if (lineTime <= currentTimer) {
            if (currentLine == lines.size() - 1) {
                done = true;
                return true;
            } else {
                currentLine++;
                currentTimer = 0;
            }
        } else {
            currentTimer = lineTime;
        }
    }

    return false;
}

void Dialogue::draw(olc::PixelGameEngine *pge) const {
    auto line = currentLine;
    if (line >= lines.size()) {
        line = lines.size() - 1;
    }

    std::string said = "";
    auto timeCopy = currentTimer;
    for (auto c : lines.at(line)) {
        if (doubleTimeLetters.find(c) != doubleTimeLetters.end()) {
            timeCopy -= timePerLetter * 2;
        } else {
            timeCopy -= timePerLetter;
        }

        said += c;

        if (timeCopy <= 0) {
            break;
        }
    }

    auto &characterGraphic = SpriteManager::getInstance().getSprite(
            characterSprites.at(character));

    olc::vf2d characterSize{
            static_cast<float>(characterGraphic.Sprite()->width),
            static_cast<float>(characterGraphic.Sprite()->height),
    };

    int wantedHeight = pge->ScreenHeight() * 0.75f;

    olc::vi2d screenSize{
            pge->ScreenWidth(),
            pge->ScreenHeight(),
    };

    auto scale = wantedHeight / static_cast<float>(characterSize.y);

    auto decalPos = screenSize / 2 - characterSize * scale / 2;

    pge->DrawDecal(decalPos, characterGraphic.Decal(), {scale, scale});
    pge->FillRectDecal({0, screenSize.y / 4.0f * 3},
                       {static_cast<float>(screenSize.x), screenSize.y / 4.0f},
                       olc::GREY);

    auto textSize = pge->GetTextSizeProp(lines.at(currentLine));
    olc::vi2d textPos{
            screenSize.x / 2 - textSize.x,
            static_cast<int>(screenSize.y / 4.0f * 3.5f - textSize.y),
    };
    pge->DrawStringPropDecal(textPos, said, olc::BLACK, {2, 2});
}

void Dialogue::reset() {
    currentLine = 0;
    currentTimer = 0;
    done = false;
}

const float Dialogue::timePerLetter = 0.025f;
const std::unordered_set<char> Dialogue::doubleTimeLetters = {
        '.',
        ',',
        '!',
        '?',
};
const std::unordered_map<Dialogue::Character, SpriteManager::SpriteAssets>
        Dialogue::characterSprites = {
                {Character::Javid, SpriteManager::SpriteAssets::JavidCharacter},
                {Character::Moros, SpriteManager::SpriteAssets::MorosCharacter},
                {Character::Gorbit,
                 SpriteManager::SpriteAssets::GorbitCharacter},
};
