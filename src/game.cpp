#include "ugar_io_qt/game.h"

#include <cstdlib>
#include <ctime>

#include <QFont>
#include <QPen>

#include "ugar_io_qt/ugarai.h"
#include "ugar_io_qt/ugarplayer.h"

const QString Game::START_GAME_LABEL = "Press Space to Play";

Game::Game(QObject* parent)
    : QObject(parent),
      cam(std::make_unique<Camera>(QPointF(640.0, 480.0), QPointF(320.0, 240.0), 1.0f)) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < VERT_LINE_AMOUNT; i++) {
        const QColor color = (i == 0 || i == VERT_LINE_AMOUNT - 1) ? QColor(0, 0, 0) : QColor(240, 240, 240);
        vertLines[i] = std::make_unique<Line>(QPointF(i * 200.0, 0.0), QPointF(i * 200.0, GAME_FIELD_HEIGHT), color);
    }

    for (int i = 0; i < HORZ_LINE_AMOUNT; i++) {
        const QColor color = (i == 0 || i == HORZ_LINE_AMOUNT - 1) ? QColor(0, 0, 0) : QColor(240, 240, 240);
        horzLines[i] = std::make_unique<Line>(QPointF(0.0, i * 200.0), QPointF(GAME_FIELD_WIDTH, i * 200.0), color);
    }

    for (int i = 1; i < UGAR_AMOUNT; i++) {
        const QPointF aiPosition(
            std::rand() % static_cast<int>(GAME_FIELD_WIDTH / 2.0f) + GAME_FIELD_WIDTH / 2.0f,
            std::rand() % static_cast<int>(GAME_FIELD_HEIGHT / 2.0f) + GAME_FIELD_HEIGHT / 2.0f);
        ugars[i] = std::make_unique<UgarAI>(aiPosition, 5.0f);
    }

    for (int i = 0; i < FOOD_AMOUNT; i++) {
        const QPointF foodPosition(
            std::rand() % static_cast<int>(GAME_FIELD_WIDTH),
            std::rand() % static_cast<int>(GAME_FIELD_HEIGHT));
        foods[i] = std::make_unique<Food>(2.0f, foodPosition);
    }

    SyncAllRefs();
    for (int i = 1; i < UGAR_AMOUNT; i++) {
        static_cast<UgarAI*>(ugars[i].get())->AssignAIData(foodRefs.data(), FOOD_AMOUNT, ugarRefs.data(), UGAR_AMOUNT);
    }
}

void Game::SyncUgarRef(int index) {
    ugarRefs[index] = ugars[index].get();
}

void Game::SyncFoodRef(int index) {
    foodRefs[index] = foods[index].get();
}

void Game::SyncAllRefs() {
    for (int i = 0; i < UGAR_AMOUNT; i++) {
        SyncUgarRef(i);
    }
    for (int i = 0; i < FOOD_AMOUNT; i++) {
        SyncFoodRef(i);
    }
}

void Game::Update() {
    if (ugars[0] != nullptr && isStarted) {
        cam->observedPosition.setX(cam->observedPosition.x() + (ugars[0]->position.x() - cam->observedPosition.x()) * CAMERA_LERP);
        cam->observedPosition.setY(cam->observedPosition.y() + (ugars[0]->position.y() - cam->observedPosition.y()) * CAMERA_LERP);

        float requiredScale = 0.0f;
        if (ugars[0]->radius < NORMAL_SCALE_RADIUS) {
            requiredScale = static_cast<float>(cam->viewportSize.y() / NORMAL_SCALE_RESOLUTION);
        } else {
            requiredScale = static_cast<float>((cam->viewportSize.y() / NORMAL_SCALE_RESOLUTION) * (NORMAL_SCALE_RADIUS / ugars[0]->radius));
        }
        cam->scale += (requiredScale - cam->scale) * SCALE_LERP;
    } else if (ugars[1] != nullptr) {
        cam->observedPosition.setX(cam->observedPosition.x() + (ugars[1]->position.x() - cam->observedPosition.x()) * CAMERA_LERP);
        cam->observedPosition.setY(cam->observedPosition.y() + (ugars[1]->position.y() - cam->observedPosition.y()) * CAMERA_LERP);

        float requiredScale = 0.0f;
        if (ugars[1]->radius < NORMAL_SCALE_RADIUS) {
            requiredScale = static_cast<float>(cam->viewportSize.y() / NORMAL_SCALE_RESOLUTION);
        } else {
            requiredScale = static_cast<float>((cam->viewportSize.y() / NORMAL_SCALE_RESOLUTION) * (NORMAL_SCALE_RADIUS / ugars[1]->radius));
        }
        cam->scale += (requiredScale - cam->scale) * SCALE_LERP;
    }

    for (int i = 0; i < UGAR_AMOUNT; i++) {
        if (ugars[i] == nullptr) {
            continue;
        }
        ugars[i]->Update();
        if (ugars[i]->position.x() - ugars[i]->radius < 0.0) {
            ugars[i]->position.setX(ugars[i]->radius);
        }
        if (ugars[i]->position.x() + ugars[i]->radius > GAME_FIELD_WIDTH) {
            ugars[i]->position.setX(GAME_FIELD_WIDTH - ugars[i]->radius);
        }
        if (ugars[i]->position.y() - ugars[i]->radius < 0.0) {
            ugars[i]->position.setY(ugars[i]->radius);
        }
        if (ugars[i]->position.y() + ugars[i]->radius > GAME_FIELD_HEIGHT) {
            ugars[i]->position.setY(GAME_FIELD_HEIGHT - ugars[i]->radius);
        }

        for (int j = 0; j < UGAR_AMOUNT; j++) {
            if (ugars[j] == nullptr || ugars[i] == nullptr || ugars[j].get() == ugars[i].get()) {
                continue;
            }
            bool isLesser = false;
            if (ugars[i]->CheckCollision(ugars[j].get(), &isLesser)) {
                if (isLesser) {
                    ugars[j]->SetSquare(ugars[j]->GetSquare() + ugars[i]->GetSquare());
                    if (i == 0) {
                        isStarted = false;
                    }
                    ugars[i].reset();
                    SyncUgarRef(i);
                } else {
                    ugars[i]->SetSquare(ugars[j]->GetSquare() + ugars[i]->GetSquare());
                    if (j == 0) {
                        isStarted = false;
                    }
                    ugars[j].reset();
                    SyncUgarRef(j);
                }
            }
        }

        for (int j = 0; j < FOOD_AMOUNT; j++) {
            if (foods[j] == nullptr) {
                continue;
            }
            if (ugars[i] != nullptr && ugars[i]->CheckFoodCollision(foods[j].get())) {
                ugars[i]->SetSquare(ugars[i]->GetSquare() + foods[j]->GetSquare());
                foods[j].reset();
                SyncFoodRef(j);
            }
        }
    }

    if (objectControlTimer > OBJ_CONTROL_UPDATE_TIME) {
        ObjectControlUpdate();
        objectControlTimer = 0;
    } else {
        objectControlTimer++;
    }
}

void Game::ObjectControlUpdate() {
    int count = 0;
    for (int i = 0; i < FOOD_AMOUNT; i++) {
        if (foods[i] == nullptr && count < 50) {
            const QPointF foodPosition(
                std::rand() % static_cast<int>(GAME_FIELD_WIDTH),
                std::rand() % static_cast<int>(GAME_FIELD_HEIGHT));
            foods[i] = std::make_unique<Food>(2.0f, foodPosition);
            SyncFoodRef(i);
            count++;
        }
    }

    count = 0;
    if (ugars[0] == nullptr && isStarted) {
        const QPointF playerPosition(
            std::rand() % static_cast<int>(GAME_FIELD_WIDTH / 2.0f) + GAME_FIELD_WIDTH / 2.0f,
            std::rand() % static_cast<int>(GAME_FIELD_HEIGHT / 2.0f) + GAME_FIELD_HEIGHT / 2.0f);
        ugars[0] = std::make_unique<UgarPlayer>(playerPosition, 5.0f);
        SyncUgarRef(0);
    }
    for (int i = 1; i < UGAR_AMOUNT; i++) {
        if (ugars[i] == nullptr && count < 2) {
            const QPointF aiPosition(
                std::rand() % static_cast<int>(GAME_FIELD_WIDTH / 2.0f) + GAME_FIELD_WIDTH / 2.0f,
                std::rand() % static_cast<int>(GAME_FIELD_HEIGHT / 2.0f) + GAME_FIELD_HEIGHT / 2.0f);
            ugars[i] = std::make_unique<UgarAI>(aiPosition, 5.0f);
            SyncUgarRef(i);
            static_cast<UgarAI*>(ugars[i].get())->AssignAIData(foodRefs.data(), FOOD_AMOUNT, ugarRefs.data(), UGAR_AMOUNT);
            count++;
        }
    }
}

bool Game::IsStarted() const {
    return isStarted;
}

void Game::Start() {
    if (isStarted) {
        return;
    }
    isStarted = true;
    ObjectControlUpdate();
}

void Game::Draw(QPainter* painter) {
    for (int i = 0; i < VERT_LINE_AMOUNT; i++) {
        if (vertLines[i] == nullptr) {
            continue;
        }
        vertLines[i]->UpdateDrawableLine(cam->GetNormalXOffset(), cam->GetNormalYOffset(), cam->scale);
        vertLines[i]->Draw(painter);
    }

    for (int i = 0; i < HORZ_LINE_AMOUNT; i++) {
        if (horzLines[i] == nullptr) {
            continue;
        }
        horzLines[i]->UpdateDrawableLine(cam->GetNormalXOffset(), cam->GetNormalYOffset(), cam->scale);
        horzLines[i]->Draw(painter);
    }

    for (int i = 0; i < UGAR_AMOUNT; i++) {
        if (ugars[i] == nullptr) {
            continue;
        }
        ugars[i]->UpdateDrawingRect(cam->GetNormalXOffset(), cam->GetNormalYOffset(), cam->scale);
        ugars[i]->Draw(painter);
    }

    for (int i = 0; i < FOOD_AMOUNT; i++) {
        if (foods[i] == nullptr) {
            continue;
        }
        foods[i]->UpdateDrawingRect(cam->GetNormalXOffset(), cam->GetNormalYOffset(), cam->scale);
        foods[i]->Draw(painter);
    }

    if (!isStarted) {
        const QRectF mainRect(0.0, 20.0, cam->viewportSize.x(), 100.0);
        const QRectF shadowRect(3.0, 23.0, cam->viewportSize.x(), 100.0);
        const QFont mainFont("Arial", static_cast<int>(FONT_SIZE));
        const QFont shadowFont("Arial", static_cast<int>(FONT_SIZE));
        const QPen mainPen(QColor(0, 0, 0, 255));
        const QPen shadowPen(QColor(0, 0, 0, 67));

        painter->setFont(shadowFont);
        painter->setPen(shadowPen);
        painter->drawText(shadowRect, Qt::AlignHCenter | Qt::AlignTop, START_GAME_LABEL);

        painter->setFont(mainFont);
        painter->setPen(mainPen);
        painter->drawText(mainRect, Qt::AlignHCenter | Qt::AlignTop, START_GAME_LABEL);
    }
}
