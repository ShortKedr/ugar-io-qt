#ifndef UGAR_IO_QT_UGAR_H
#define UGAR_IO_QT_UGAR_H

#include <QColor>
#include <QPainter>
#include <QPointF>
#include <QRectF>

#include "ugar_io_qt/food.h"

class Ugar {
public:
    QPointF position{0.0, 0.0};
    float radius = 0.5f;
    float showedRadius = 0.5f;
    QPointF currentSpeed{0.0, 0.0};
    float currentSpeedInc = 0.5f;
    QColor color{0, 0, 0};
    QRectF drawingRect{0.0, 0.0, 0.0, 0.0};

    Ugar() = default;
    Ugar(const QPointF& position, float radius);
    virtual ~Ugar() = default;

    virtual void Update();
    void UpdateSize();
    void UpdateDrawingRect(float xoffset, float yoffset, float scale);
    void UpdateSpeedInc();

    bool CheckCollision(Ugar* target, bool* isLesser) const;
    bool CheckFoodCollision(Food* target) const;

    void Move(float x, float y);
    void MoveDirection(float direction);

    float GetSquare() const;
    void SetSquare(float square);
    void Draw(QPainter* painter) const;

private:
    static constexpr bool INVERT_X = false;
    static constexpr bool INVERT_Y = true;

    static constexpr float U_DIFFERENCE = 0.00001f;
    static constexpr float SIZE_LERP = 0.1f;
    static constexpr float FRICTION = 0.1f;
    static constexpr float MAX_SPEED_INC = 0.4f;
    static constexpr float MAX_SPEED_SIZE_DEC = 0.35f;
    static constexpr float SPEED_SIZE_DEC = 0.005f;
};

#endif // UGAR_IO_QT_UGAR_H
