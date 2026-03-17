#include "ugar_io_qt/ugarplayer.h"

UgarPlayer::UgarPlayer(const QPointF& position, float radius)
    : Ugar(position, radius) {
}

bool UgarPlayer::handleScanCode(quint32 scanCode, bool press) {
    switch (scanCode) {
    case UP_SCANCODE:
        upKey = press;
        return true;
    case DOWN_SCANCODE:
        downKey = press;
        return true;
    case LEFT_SCANCODE:
        leftKey = press;
        return true;
    case RIGHT_SCANCODE:
        rightKey = press;
        return true;
    default:
        return false;
    }
}

void UgarPlayer::Update() {
    Ugar::Update();
    if (upKey) {
        if (leftKey) {
            MoveDirection(135.0f);
        } else if (rightKey) {
            MoveDirection(45.0f);
        } else {
            MoveDirection(90.0f);
        }
    } else if (downKey) {
        if (leftKey) {
            MoveDirection(225.0f);
        } else if (rightKey) {
            MoveDirection(315.0f);
        } else {
            MoveDirection(270.0f);
        }
    } else if (leftKey) {
        MoveDirection(180.0f);
    } else if (rightKey) {
        MoveDirection(0.0f);
    }
}

void UgarPlayer::event(QKeyEvent* event) {
    if (event->isAutoRepeat()) {
        return;
    }

    bool press = false;
    if (event->type() == QEvent::KeyPress) {
        press = true;
    } else if (event->type() != QEvent::KeyRelease) {
        return;
    }

    if (handleScanCode(event->nativeScanCode(), press)) {
        return;
    }

    switch (event->key()) {
    case UP_KEY:
        upKey = press;
        break;
    case DOWN_KEY:
        downKey = press;
        break;
    case LEFT_KEY:
        leftKey = press;
        break;
    case RIGHT_KEY:
        rightKey = press;
        break;
    default:
        break;
    }
}
