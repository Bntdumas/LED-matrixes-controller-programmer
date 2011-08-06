#include "scenarioMovingCubes.h"

scenarioMovingCubes::scenarioMovingCubes()
{
}

void scenarioMovingCubes::makeScenario(QList< QList<LedState> > * scenario, QList<int> *delay)
{

    /*int red = qrand()%255;
    int green = qrand()%255;
    int blue = qrand()%255;*/

    QList<LedState> picture;

    /* for (z =0; z < m_xSize ; z++)
    {
        for(y =0; y < m_ySize ; y++)
            for(x =0; x < m_zSize ; x++) //paints a line
            {
                LedState led = {x,y,z,red,green,blue};
                picture.append(led);
            }
        scenario->append(picture);
        delay->append(200);
        picture.clear();
    }*/
 /*   for (int y =0; y < m_ySize ; y++)
    {
        for(int x =0; x < m_xSize ; x++) //paints a line
        {
            LedState led = {x,y,0,255,0,0};
            picture.append(led);

            scenario->append(picture);
            delay->append(40);
            picture.clear();
        }
    }

    for (int j =0; j < 100 ; j++)
    {
        LedState led = {qrand()%m_xSize,qrand()%m_ySize,0,255,0,0};
        picture.append(led);

        scenario->append(picture);
        delay->append(60);
        picture.clear();
    }
*/
    for (int j =0; j < 150 ; j++)
    {
        for (int i =0; i < 22 ; i++)
        {
            LedState led = {qrand()%m_xSize,qrand()%m_ySize,0,255,0,0};
            picture.append(led);
        }
            scenario->append(picture);
            delay->append(30);
            picture.clear();
    }

    for (int j =0; j < 150 ; j++)
    {
        LedState led = {qrand()%m_xSize,qrand()%m_ySize,0,255,0,0};
        picture.append(led);
        scenario->append(picture);
        delay->append(50);
        //picture.clear();
    }


    emit doneCreating();
}
