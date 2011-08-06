#ifndef SCENARIOMOVINGSQUARERANDSUSPENDED_H
#define SCENARIOMOVINGSQUARERANDSUSPENDED_H
#include "abstractPredefinedScenario.h"


class scenarioMovingSquareRandSuspended : public abstractPredefinedScenario
{
public:
    scenarioMovingSquareRandSuspended();
    virtual void makeScenario(QList< QList<LedState> > * scenario, QList<int> *delay);

};

#endif // SCENARIOMOVINGSQUARERANDSUSPENDED_H
