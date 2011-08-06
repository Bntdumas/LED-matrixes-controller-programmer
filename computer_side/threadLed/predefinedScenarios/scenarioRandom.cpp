#include "scenarioRandom.h"

scenarioRandom::scenarioRandom()
{
}

void scenarioRandom::makeScenario(QList< QList<LedState> > * scenario, QList<int> *delay)
{
    int x = 0;
    int y = 0;
    int z = 0;


    int red = qrand()%255;
    int green = qrand()%255;
    int blue = qrand()%255;

    for (int i=0;i<10;i++)
    {
        QList<LedState> picture;
        for (int count=0;count<32;count++)
        {
                LedState led = {qrand()%8,qrand()%8,0,red,green,blue};
                picture.append(led);
        }
        scenario->append(picture);
        delay->append(1000);
        picture.clear();
    }

    emit doneCreating();
}
