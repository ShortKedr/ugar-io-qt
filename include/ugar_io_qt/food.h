#ifndef UGAR_IO_QT_FOOD_H
#define UGAR_IO_QT_FOOD_H

#include <QColor>
#include <QPainter>
#include <QPointF>
#include <QRectF>

class Food {
public:
    float radius = 0.5f;
    QPointF position{0.0, 0.0};
    QColor color{0, 0, 0};
    QRectF drawingRect{0.0, 0.0, 0.0, 0.0};

    Food() = default;
    Food(float radius, const QPointF& position);
    ~Food() = default;

    void UpdateDrawingRect(float xoffset, float yoffset, float scale);

    float GetSquare() const;

    void Draw(QPainter* painter) const;
};

#endif // UGAR_IO_QT_FOOD_H
