#include "ugar_io_qt/ugarai.h"

#include <cmath>
#include <cstdlib>

UgarAI::UgarAI(const QPointF& position, float radius)
    : Ugar(position, radius) {
}

void UgarAI::Update() {
    Ugar::Update();

    if (agressiveTimer > AGRESSIVE_UPDATE_PERIOD) {
        isAgressive = (std::rand() % 101) >= 80;
        agressiveTimer = 0;
    } else {
        agressiveTimer++;
    }

    if (foods == nullptr || ugars == nullptr) {
        return;
    }

    Food* nearFood = nullptr;
    float minFoodDist = 10000.0f;
    for (int i = 0; i < foods_count; i++) {
        if (foods[i] == nullptr) {
            continue;
        }
        const float dist = pointDist(foods[i]->position, position);
        if (minFoodDist > dist) {
            nearFood = foods[i];
            minFoodDist = dist;
        }
    }

    Ugar* nearUgar = nullptr;
    float minUgarDist = 10000.0f;
    Ugar* nearDUgar = nullptr;
    float minDUgarDist = 10000.0f;

    for (int i = 0; i < ugars_count; i++) {
        if (ugars[i] == nullptr || ugars[i] == this) {
            continue;
        }
        const float dist = pointDist(ugars[i]->position, position) - ugars[i]->radius - radius;
        if (ugars[i]->radius < radius && minUgarDist > dist) {
            nearUgar = ugars[i];
            minUgarDist = dist;
        } else if (ugars[i]->radius > radius && minDUgarDist > dist) {
            nearDUgar = ugars[i];
            minDUgarDist = dist;
        }
    }

    if (isAgressive) {
        if (minDUgarDist < minUgarDist) {
            if (nearDUgar != nullptr) {
                Move(static_cast<float>(position.x() - nearDUgar->position.x()), static_cast<float>(position.y() - nearDUgar->position.y()));
            }
        } else if (nearUgar != nullptr) {
            Move(static_cast<float>(nearUgar->position.x() - position.x()), static_cast<float>(nearUgar->position.y() - position.y()));
        }
    } else if (minDUgarDist < minUgarDist && minDUgarDist < minFoodDist) {
        if (nearDUgar != nullptr) {
            Move(static_cast<float>(position.x() - nearDUgar->position.x()), static_cast<float>(position.y() - nearDUgar->position.y()));
        }
    } else if (minUgarDist < minFoodDist) {
        if (nearUgar != nullptr) {
            Move(static_cast<float>(nearUgar->position.x() - position.x()), static_cast<float>(nearUgar->position.y() - position.y()));
        }
    } else if (nearFood != nullptr) {
        Move(static_cast<float>(nearFood->position.x() - position.x()), static_cast<float>(nearFood->position.y() - position.y()));
    }
}

void UgarAI::AssignAIData(Food** foodsData, int foodsCount, Ugar** ugarsData, int ugarsCount) {
    foods = foodsData;
    foods_count = foodsCount;
    ugars = ugarsData;
    ugars_count = ugarsCount;
}

float UgarAI::pointDist(const QPointF& first, const QPointF& second) {
    const float dx = static_cast<float>(first.x() - second.x());
    const float dy = static_cast<float>(first.y() - second.y());
    return std::sqrt(dx * dx + dy * dy);
}
