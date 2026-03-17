#include "ugar_io_qt/ugar.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>

Ugar::Ugar(const QPointF& position, float radius)
    : position(position), radius(radius), showedRadius(radius), color(std::rand() % 256, std::rand() % 256, std::rand() % 256) {
}

void Ugar::Update() {
    UpdateSize();
    UpdateSpeedInc();
    position.setX(position.x() + currentSpeed.x());
    position.setY(position.y() + currentSpeed.y());
    currentSpeed.setX(currentSpeed.x() - currentSpeed.x() * FRICTION);
    currentSpeed.setY(currentSpeed.y() - currentSpeed.y() * FRICTION);
}

void Ugar::UpdateDrawingRect(float xoffset, float yoffset, float scale) {
    drawingRect.setX((position.x() - showedRadius) * scale - xoffset);
    drawingRect.setY((position.y() - showedRadius) * scale - yoffset);
    drawingRect.setWidth(showedRadius * 2.0f * scale);
    drawingRect.setHeight(showedRadius * 2.0f * scale);
}

void Ugar::UpdateSpeedInc() {
    const float decrement = radius * SPEED_SIZE_DEC;
    currentSpeedInc = MAX_SPEED_INC - ((decrement < MAX_SPEED_SIZE_DEC) ? decrement : MAX_SPEED_SIZE_DEC);
}

void Ugar::UpdateSize() {
    if (std::fabs(radius - showedRadius) <= U_DIFFERENCE) {
        return;
    }
    showedRadius += (radius - showedRadius) * SIZE_LERP;
}

bool Ugar::CheckFoodCollision(Food* target) const {
    const float xDist = static_cast<float>(position.x() - target->position.x());
    const float yDist = static_cast<float>(position.y() - target->position.y());
    const float dist = std::sqrt(xDist * xDist + yDist * yDist);
    const float collisionDist = radius + (target->radius * 0.6f);
    return dist <= collisionDist;
}

void Ugar::SetPosition(float x, float y) {
    position.setX(x);
    position.setY(y);
}

void Ugar::Move(float x, float y) {
    UpdateSpeedInc();
    const float sum = std::fabs(x) + std::fabs(y);
    currentSpeed.setX(currentSpeed.x() + ((sum != 0.0f) ? x / sum : 0.0f) * currentSpeedInc);
    currentSpeed.setY(currentSpeed.y() + ((sum != 0.0f) ? y / sum : 0.0f) * currentSpeedInc);
}

void Ugar::MoveDirection(float direction) {
    const float radians = direction * static_cast<float>(M_PI) / 180.0f;
    const float xmul = INVERT_X ? -std::cos(radians) : std::cos(radians);
    const float ymul = INVERT_Y ? -std::sin(radians) : std::sin(radians);

    UpdateSpeedInc();
    currentSpeed.setX(currentSpeed.x() + currentSpeedInc * xmul);
    currentSpeed.setY(currentSpeed.y() + currentSpeedInc * ymul);
}

float Ugar::GetSquare() const {
    return static_cast<float>(M_PI) * radius * radius;
}

void Ugar::SetSquare(float square) {
    radius = std::sqrt(square / static_cast<float>(M_PI));
}

void Ugar::Draw(QPainter* painter) const {
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(drawingRect);
}

bool Ugar::CheckCollision(Ugar* target, bool* isLesser) const {
    const float xDist = static_cast<float>(position.x() - target->position.x());
    const float yDist = static_cast<float>(position.y() - target->position.y());
    const float dist = std::sqrt(xDist * xDist + yDist * yDist);
    const float collisionDist = (radius > target->radius) ? radius + (target->radius * 0.6f) : (radius * 0.6f) + target->radius;
    *isLesser = radius < target->radius;
    return dist <= collisionDist;
}
