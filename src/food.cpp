#include "ugar_io_qt/food.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
Food::Food(float radius, const QPointF& position)
    : radius(radius), position(position), color(std::rand() % 50, std::rand() % 50, std::rand() % 50) {
}

void Food::UpdateDrawingRect(float xoffset, float yoffset, float scale) {
    drawingRect.setX((position.x() - radius) * scale - xoffset);
    drawingRect.setY((position.y() - radius) * scale - yoffset);
    drawingRect.setWidth(radius * 2.0f * scale);
    drawingRect.setHeight(radius * 2.0f * scale);
}

float Food::GetSquare() const {
    return static_cast<float>(M_PI) * radius * radius;
}

void Food::SetSquare(float square) {
    radius = std::sqrt(square / static_cast<float>(M_PI));
}

void Food::Draw(QPainter* painter) const {
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(drawingRect);
}
