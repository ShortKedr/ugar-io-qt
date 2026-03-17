#include "ugar_io_qt/gamewindow.h"

#include <QGuiApplication>
#include <QScreen>

#include "ugar_io_qt/ugarplayer.h"

GameWindow::GameWindow(QWindow* parent)
    : QWindow(parent),
      game(std::make_unique<Game>()),
      backingStore(std::make_unique<QBackingStore>(this)) {
    const QSize screenSize = screen() != nullptr ? screen()->size() : QSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setGeometry(screenSize.width() / 2 - DEFAULT_WIDTH / 2,
                screenSize.height() / 2 - DEFAULT_HEIGHT / 2,
                DEFAULT_WIDTH,
                DEFAULT_HEIGHT);
    setTitle(QStringLiteral("Ugar.io Qt"));

    auto* renderTimer = new QTimer(this);
    connect(renderTimer, &QTimer::timeout, this, &GameWindow::renderNow);
    renderTimer->start(16);

    auto* updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, game.get(), &Game::Update);
    updateTimer->start(16);
}

void GameWindow::render(QPainter* painter) {
    game->cam->viewportSize.setX(width());
    game->cam->viewportSize.setY(height());
    game->Draw(painter);
}

void GameWindow::renderLater() {
    requestUpdate();
}

void GameWindow::renderNow() {
    if (!isExposed()) {
        return;
    }

    const QRect rect(0, 0, width(), height());
    backingStore->beginPaint(rect);

    QPaintDevice* device = backingStore->paintDevice();
    QPainter painter(device);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(0, 0, width(), height(), QBrush(Qt::white));
    render(&painter);
    painter.end();

    backingStore->endPaint();
    backingStore->flush(rect);
}

bool GameWindow::event(QEvent* event) {
    if (event->type() == QEvent::UpdateRequest) {
        renderNow();
        return true;
    }

    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
        auto* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Space && event->type() == QEvent::KeyPress) {
            game->Start();
        } else if (game->ugars[0] != nullptr) {
            if (auto* player = dynamic_cast<UgarPlayer*>(game->ugars[0].get())) {
                player->event(keyEvent);
            }
        }
        return true;
    }

    return QWindow::event(event);
}

void GameWindow::resizeEvent(QResizeEvent* event) {
    backingStore->resize(event->size());
}

void GameWindow::exposeEvent(QExposeEvent*) {
    if (isExposed()) {
        renderNow();
    }
}
