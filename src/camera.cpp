#include "ugar_io_qt/camera.h"

Camera::Camera(const QPointF& vs, const QPointF& op, float scale)
    : viewportSize(vs), observedPosition(op), scale(scale) {
}

float Camera::GetNormalXOffset() const {
    return static_cast<float>(observedPosition.x() * scale - (viewportSize.x() / 2.0));
}

float Camera::GetNormalYOffset() const {
    return static_cast<float>(observedPosition.y() * scale - (viewportSize.y() / 2.0));
}
