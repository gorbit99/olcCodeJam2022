#pragma once

#include <array>
class Field {
public:
private:
    enum class CloudState {
        None,
        Regular,
        Rain,
    };

    std::array<std::array<CloudState, 16>, 16> clouds;
};
