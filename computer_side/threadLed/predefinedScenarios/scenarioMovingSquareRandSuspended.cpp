#include "scenarioMovingSquareRandSuspended.h"

scenarioMovingSquareRandSuspended::scenarioMovingSquareRandSuspended()
{
}

void scenarioMovingSquareRandSuspended::makeScenario(QList< QList<LedState> > * scenario, QList<int> *delay)
{

    int x = 0;
    int y = 0;
    int z = 0;


    int red = qrand()%255;
    int green = qrand()%255;
    int blue = qrand()%255;

    QList<LedState> picture;

    int nbSuspended = (m_xSize*m_ySize)/10;
;
    for (int zPlane =0; zPlane < m_zSize ; zPlane++)
    {
        for (z =0; z < m_zSize ; z++)
        {
            if (z == zPlane)
            {
            for(y =0; y < m_ySize ; y++)
                for(x =0; x < m_xSize ; x++) //paints a line
                {
                    LedState led = {x,y,z,red,green,blue};
                    picture.append(led);
                }
            }
            else
                for (int i = 0; i < zPlane; i++)
                {
                    for (int ii=0; ii < nbSuspended; ii++)
                    {
                        int xSuspended = qrand()%m_xSize;
                        int ySuspended = qrand()%m_ySize;

                        LedState led = {xSuspended,ySuspended,i,red,green,blue};
                        picture.append(led);
                    }
                }
        }
        scenario->append(picture);
        if (zPlane != m_zSize-1)
        delay->append(80);
        else delay->append(2000);
        picture.clear();
    }
    emit doneCreating();
}
