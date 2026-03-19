#ifndef UGAR_IO_QT_UGARPLAYER_H
#define UGAR_IO_QT_UGARPLAYER_H

#include <QKeyEvent>
#include <QPointF>
#include <Qt>

#include "ugar_io_qt/ugar.h"

class UgarPlayer : public Ugar {
public:
    static constexpr int UP_KEY = Qt::Key_W;
    static constexpr int DOWN_KEY = Qt::Key_S;
    static constexpr int LEFT_KEY = Qt::Key_A;
    static constexpr int RIGHT_KEY = Qt::Key_D;
    static constexpr quint32 UP_SCANCODE = 0x11;
    static constexpr quint32 LEFT_SCANCODE = 0x1E;
    static constexpr quint32 DOWN_SCANCODE = 0x1F;
    static constexpr quint32 RIGHT_SCANCODE = 0x20;

    UgarPlayer() = default;
    UgarPlayer(const QPointF& position, float radius);
    ~UgarPlayer() override = default;

    void Update() override;
    void event(QKeyEvent* event);

private:
    bool upKey = false;
    bool downKey = false;
    bool leftKey = false;
    bool rightKey = false;

    bool handleScanCode(quint32 scanCode, bool press);
};

#endif // UGAR_IO_QT_UGARPLAYER_H
