#ifndef UGAR_IO_QT_CAMERA_H
#define UGAR_IO_QT_CAMERA_H

#include <QPointF>

class Camera {
public:
    QPointF viewportSize{0.0, 0.0};
    QPointF observedPosition{0.0, 0.0};
    float scale = 1.0f;

    Camera() = default;
    Camera(const QPointF& vs, const QPointF& op, float scale = 1.0f);

    float GetNormalXOffset() const;
    float GetNormalYOffset() const;

    void SetCamera(const QPointF& vs, const QPointF& op);
    void SetCamera(const QPointF& vs, const QPointF& op, float scale);
};

#endif // UGAR_IO_QT_CAMERA_H
