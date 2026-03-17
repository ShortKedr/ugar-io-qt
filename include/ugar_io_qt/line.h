#ifndef UGAR_IO_QT_LINE_H
#define UGAR_IO_QT_LINE_H

#include <QColor>
#include <QPainter>
#include <QPointF>

class Line {
public:
    QPointF start;
    QPointF end;
    QColor color;
    QPointF drawableStart;
    QPointF drawableEnd;

    Line() = default;
    Line(const QPointF& start, const QPointF& end, const QColor& color);
    ~Line() = default;

    void UpdateDrawableLine(float xoffset, float yoffset, float scale);
    void Draw(QPainter* painter) const;
};

#endif // UGAR_IO_QT_LINE_H
