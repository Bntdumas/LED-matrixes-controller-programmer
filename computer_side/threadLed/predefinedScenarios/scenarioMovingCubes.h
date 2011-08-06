#ifndef SCENARIOMOVINGCUBES_H
#define SCENARIOMOVINGCUBES_H
#include "abstractPredefinedScenario.h"



class scenarioMovingCubes : public abstractPredefinedScenario
{


public:
    scenarioMovingCubes();
    virtual void makeScenario(QList< QList<LedState> > * scenario, QList<int> *delay);

};

#endif // SCENARIOMOVINGCUBES_H
