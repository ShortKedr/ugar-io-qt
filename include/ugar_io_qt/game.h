#ifndef UGAR_IO_QT_GAME_H
#define UGAR_IO_QT_GAME_H

#include <array>
#include <memory>

#include <QObject>
#include <QPainter>
#include <QString>

#include "ugar_io_qt/camera.h"
#include "ugar_io_qt/food.h"
#include "ugar_io_qt/line.h"
#include "ugar_io_qt/ugar.h"

class Game : public QObject {
public:
    static const QString START_GAME_LABEL;
    static constexpr float FONT_SIZE = 28.0f;
    static constexpr float GAME_FIELD_WIDTH = 4000.0f;
    static constexpr float GAME_FIELD_HEIGHT = 4000.0f;
    static constexpr int UGAR_AMOUNT = 75;
    static constexpr int FOOD_AMOUNT = 750;
    static constexpr int VERT_LINE_AMOUNT = 21;
    static constexpr int HORZ_LINE_AMOUNT = 21;
    static constexpr float CAMERA_LERP = 0.05f;
    static constexpr float SCALE_LERP = 0.05f;
    static constexpr float NORMAL_SCALE_RESOLUTION = 768.0f;
    static constexpr float NORMAL_SCALE_RADIUS = 60.0f;

    explicit Game(QObject* parent = nullptr);
    ~Game() override = default;

    std::unique_ptr<Camera> cam;
    std::array<std::unique_ptr<Ugar>, UGAR_AMOUNT> ugars;
    std::array<std::unique_ptr<Food>, FOOD_AMOUNT> foods;
    std::array<std::unique_ptr<Line>, VERT_LINE_AMOUNT> vertLines;
    std::array<std::unique_ptr<Line>, HORZ_LINE_AMOUNT> horzLines;

    void ObjectControlUpdate();
    bool IsStarted() const;
    void Start();
    void Update();
    void Draw(QPainter* painter);

private:
    static constexpr int OBJ_CONTROL_UPDATE_TIME = 300;

    int objectControlTimer = 0;
    bool isStarted = false;
    std::array<Ugar*, UGAR_AMOUNT> ugarRefs{};
    std::array<Food*, FOOD_AMOUNT> foodRefs{};

    void SyncUgarRef(int index);
    void SyncFoodRef(int index);
    void SyncAllRefs();
    void FollowCamera(const Ugar& target);
};

#endif // UGAR_IO_QT_GAME_H
