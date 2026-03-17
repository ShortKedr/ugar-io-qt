#ifndef UGAR_IO_QT_GAMEWINDOW_H
#define UGAR_IO_QT_GAMEWINDOW_H

#include <memory>

#include <QBackingStore>
#include <QEvent>
#include <QExposeEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QTimer>
#include <QWindow>

#include "ugar_io_qt/game.h"

class GameWindow : public QWindow {
public:
    static constexpr int DEFAULT_WIDTH = 800;
    static constexpr int DEFAULT_HEIGHT = 600;

    explicit GameWindow(QWindow* parent = nullptr);
    ~GameWindow() override = default;

    void render(QPainter* painter);

    void renderLater();
    void renderNow();

protected:
    bool event(QEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void exposeEvent(QExposeEvent* event) override;

private:
    std::unique_ptr<Game> game;
    std::unique_ptr<QBackingStore> backingStore;
};

#endif // UGAR_IO_QT_GAMEWINDOW_H
