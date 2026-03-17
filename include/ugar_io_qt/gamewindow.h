#ifndef UGAR_IO_QT_GAMEWINDOW_H
#define UGAR_IO_QT_GAMEWINDOW_H

#include <memory>

#include <QKeyEvent>
#include <QOpenGLWindow>
#include <QPainter>
#include <QTimer>

#include "ugar_io_qt/game.h"

class GameWindow : public QOpenGLWindow {
public:
    static constexpr int DEFAULT_WIDTH = 800;
    static constexpr int DEFAULT_HEIGHT = 600;

    explicit GameWindow(QWindow* parent = nullptr);
    ~GameWindow() override = default;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    std::unique_ptr<Game> game;
    QTimer frameTimer;

    void handleKeyEvent(QKeyEvent* event);
};

#endif // UGAR_IO_QT_GAMEWINDOW_H
