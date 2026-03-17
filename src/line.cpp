#include "ugar_io_qt/line.h"

Line::Line(const QPointF& start, const QPointF& end, const QColor& color)
    : start(start), end(end), color(color) {
}

void Line::UpdateDrawableLine(float xoffset, float yoffset, float scale) {
    drawableStart.setX((start.x() * scale) - xoffset);
    drawableStart.setY((start.y() * scale) - yoffset);
    drawableEnd.setX((end.x() * scale) - xoffset);
    drawableEnd.setY((end.y() * scale) - yoffset);
}

void Line::Draw(QPainter* painter) const {
    painter->setPen(QPen(color));
    painter->drawLine(drawableStart, drawableEnd);
}
