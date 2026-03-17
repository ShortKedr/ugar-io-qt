#ifndef UGAR_IO_QT_UGARPLAYER_H
#define UGAR_IO_QT_UGARPLAYER_H

#include <QKeyEvent>
#include <QPointF>
#include <Qt>

#include "ugar_io_qt/ugar.h"

class UgarPlayer : public Ugar {
public:
    static const int UP_KEY = Qt::Key_W;
    static const int DOWN_KEY = Qt::Key_S;
    static const int LEFT_KEY = Qt::Key_A;
    static const int RIGHT_KEY = Qt::Key_D;

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
};

#endif // UGAR_IO_QT_UGARPLAYER_H
