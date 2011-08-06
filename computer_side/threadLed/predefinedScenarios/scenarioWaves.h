#ifndef SCENARIOWAVES_H
#define SCENARIOWAVES_H

#include "abstractPredefinedScenario.h"

class scenarioWaves : public abstractPredefinedScenario
{
public:
    scenarioWaves();
    void makeScenario(QList< QList<LedState> > * scenario, QList<int> *delay);

private:

};

#endif // SCENARIOWAVES_H
