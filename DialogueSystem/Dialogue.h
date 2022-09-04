#pragma once

#include "AssetSystem/SpriteManager.h"
#include "olcPixelGameEngine.h"

#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Dialogue {
public:
    enum class Character {
        Javid,
        Moros,
        Gorbit,
    };

    Dialogue(Character character, std::vector<std::string> lines);
    bool update(olc::PixelGameEngine *pge);
    void draw(olc::PixelGameEngine *pge) const;
    void reset();

private:
    Character character;
    std::vector<std::string> lines;
    uint32_t currentLine = 0;
    float currentTimer = 0;
    bool done = false;

    static const float timePerLetter;
    static const std::unordered_set<char> doubleTimeLetters;
    static const std::unordered_map<Character, SpriteManager::SpriteAssets>
            characterSprites;
};
