#include "ugar_io_qt/gamewindow.h"

#include <QColor>
#include <QOpenGLFunctions>
#include <QScreen>

#include "ugar_io_qt/ugarplayer.h"

GameWindow::GameWindow(QWindow* parent)
    : QOpenGLWindow(NoPartialUpdate, parent),
      game(std::make_unique<Game>()) {
    setFlags(flags() | Qt::Window);
    const QSize screenSize = screen() != nullptr ? screen()->size() : QSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setGeometry(screenSize.width() / 2 - DEFAULT_WIDTH / 2,
                screenSize.height() / 2 - DEFAULT_HEIGHT / 2,
                DEFAULT_WIDTH,
                DEFAULT_HEIGHT);
    setTitle(QStringLiteral("Ugar.io Qt"));
    setSurfaceType(QSurface::OpenGLSurface);

    frameTimer.setParent(this);
    frameTimer.setTimerType(Qt::PreciseTimer);
    connect(&frameTimer, &QTimer::timeout, this, [this]() {
        game->Update();
        update();
    });
    frameTimer.start(16);
    QTimer::singleShot(0, this, [this]() {
        requestActivate();
    });
}

void GameWindow::initializeGL() {
    if (auto* functions = context() != nullptr ? context()->functions() : nullptr) {
        functions->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        functions->glEnable(GL_MULTISAMPLE);
    }
}

void GameWindow::resizeGL(int w, int h) {
    game->cam->viewportSize.setX(w);
    game->cam->viewportSize.setY(h);
}

void GameWindow::paintGL() {
    game->cam->viewportSize.setX(width());
    game->cam->viewportSize.setY(height());

    if (auto* functions = context() != nullptr ? context()->functions() : nullptr) {
        functions->glViewport(0, 0, width(), height());
        functions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillRect(QRect(0, 0, width(), height()), QColor(Qt::white));
    game->Draw(&painter);
    painter.end();
}

void GameWindow::handleKeyEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Space && event->type() == QEvent::KeyPress) {
        game->Start();
    } else if (game->ugars[0] != nullptr) {
        if (auto* player = dynamic_cast<UgarPlayer*>(game->ugars[0].get())) {
            player->event(event);
        }
    }
}

void GameWindow::keyPressEvent(QKeyEvent* event) {
    handleKeyEvent(event);
    event->accept();
}

void GameWindow::keyReleaseEvent(QKeyEvent* event) {
    handleKeyEvent(event);
    event->accept();
}
