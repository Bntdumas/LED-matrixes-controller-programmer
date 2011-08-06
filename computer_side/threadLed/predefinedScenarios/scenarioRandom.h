#ifndef SCENARIORANDOM_H
#define SCENARIORANDOM_H
#include "abstractPredefinedScenario.h"

class scenarioRandom : public abstractPredefinedScenario
{
public:
    scenarioRandom();
    virtual void makeScenario(QList< QList<LedState> > * scenario, QList<int> *delay);
};

#endif // SCENARIORANDOM_H
