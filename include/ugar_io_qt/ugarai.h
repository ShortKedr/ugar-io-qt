#ifndef UGAR_IO_QT_UGARAI_H
#define UGAR_IO_QT_UGARAI_H

#include <QPointF>

#include "ugar_io_qt/food.h"
#include "ugar_io_qt/ugar.h"

class UgarAI : public Ugar {
public:
    bool isAgressive = false;

    UgarAI() = default;
    UgarAI(const QPointF& position, float radius);
    ~UgarAI() override = default;

    void Update() override;
    void AssignAIData(Food** foods, int foodsCount, Ugar** ugars, int ugarsCount);

private:
    static constexpr int AGRESSIVE_UPDATE_PERIOD = 15000;

    int agressiveTimer = 0;
    Food** foods = nullptr;
    int foods_count = 0;
    Ugar** ugars = nullptr;
    int ugars_count = 0;

    static float pointDist(const QPointF& first, const QPointF& second);
};

#endif // UGAR_IO_QT_UGARAI_H
