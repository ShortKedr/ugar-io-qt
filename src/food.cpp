#include "ugar_io_qt/food.h"

#include <cmath>
#include <cstdlib>
#include <numbers>

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
    return std::numbers::pi_v<float> * radius * radius;
}

void Food::Draw(QPainter* painter) const {
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(drawingRect);
}
