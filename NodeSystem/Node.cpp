#include "Node.h"

#include "../AssetSystem/SpriteManager.h"

#include <vector>

Node::Node(olc::Renderable &graphic, olc::vf2d position)
        : graphic{graphic},
          position{position} {
}

void Node::draw(olc::PixelGameEngine *pge) {
    auto halfSize = olc::vi2d{
            graphic.get().Sprite()->width,
            graphic.get().Sprite()->height,
    };

    pge->DrawDecal(position - halfSize, graphic.get().Decal(), {2, 2});
}

olc::vf2d Node::getCenter() const {
    return position;
}
