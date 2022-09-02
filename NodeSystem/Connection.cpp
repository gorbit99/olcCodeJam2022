#include "Connection.h"

#include "Node.h"
#include "NodeSystem/InputPin.h"
#include "NodeSystem/OutputPin.h"

#include <algorithm>
#include <iostream>
#include <tuple>

Connection::Connection(OutputPin &sourcePin,
                       InputPin &targetPin,
                       PinType pinType)
        : sourcePin{sourcePin},
          targetPin{targetPin},
          pinType{pinType} {
    targetPin.connectTo(sourcePin);
}

Connection::~Connection() {
    targetPin.disconnect();
}

void Connection::sendData(PinData data) {
    targetPin.setData(data);
}

void Connection::draw(olc::PixelGameEngine *pge) const {
    auto color = pinTypeColors.at(pinType);

    auto [sourceStartPos, sourceEndPos, targetEndPos, targetStartPos] =
            getPoints();

    drawThickLine(pge, sourceStartPos, sourceEndPos, 4, color);
    drawThickLine(pge, targetEndPos, targetStartPos, 4, color);

    if (&sourcePin.getParent() == &targetPin.getParent()) {
        auto nodeCenter = sourcePin.getParent().getCenter();

        auto bottomHeight =
                nodeCenter.y + sourcePin.getParent().getSize().y / 2.0f;

        auto leftPoint = olc::vf2d{targetEndPos.x, bottomHeight + 14};
        auto rightPoint = olc::vf2d{sourceEndPos.x, bottomHeight + 14};

        drawThickLine(pge, sourceEndPos, rightPoint, 4, color);
        drawThickLine(pge, rightPoint, leftPoint, 4, color);
        drawThickLine(pge, leftPoint, targetEndPos, 4, color);

        return;
    }

    drawThickLine(pge, sourceEndPos, targetEndPos, 4, color);
}

std::tuple<olc::vf2d, olc::vf2d, olc::vf2d, olc::vf2d>
        Connection::getPoints() const {
    auto sourceStartPos = sourcePin.getPosition();
    auto sourceEndPos = sourceStartPos + olc::vf2d{10, 0};
    auto targetStartPos = targetPin.getPosition();
    auto targetEndPos = targetStartPos + olc::vf2d{-10, 0};

    return std::make_tuple(sourceStartPos,
                           sourceEndPos,
                           targetEndPos,
                           targetStartPos);
}

bool Connection::isPointOver(olc::vf2d point) const {
    auto [sourceStartPos, sourceEndPos, targetEndPos, targetStartPos] =
            getPoints();

    auto len = (targetEndPos - sourceEndPos).mag();
    if (len == 0) {
        return false;
    }

    auto dirVector = (targetEndPos - sourceEndPos) / len;

    auto t = std::max(0.0f,
                      std::min(len, (point - sourceEndPos).dot(dirVector)));

    auto projectedPoint = sourceEndPos + t * (dirVector);
    return (point - projectedPoint).mag() < 7;
}
