#include "scenarioWaves.h"

scenarioWaves::scenarioWaves()
{
}

void scenarioWaves::makeScenario(QList< QList<LedState> > * scenario, QList<int> *delay)
{
    int x = 0;
    int y = 0;
    int z = 0;


    int red = qrand()%255;
    int green = qrand()%255;
    int blue = qrand()%255;

    float distance, height, ripple_interval;
    int i;

    for (i=0;i<2000;i++)
    {
        QList<LedState> picture;
        for (x=0;x<m_xSize;x++)
        {
            for (z=0;z<m_ySize;z++)
            {
                distance = distance2d((float)m_ySize/2,(float)m_ySize/2,x,z)/9.899495*m_ySize;
                ripple_interval =1.3;
                height = (float)(m_zSize/2)+sin(distance/ripple_interval+(float) i/50)*(float)(m_zSize/2);

                LedState led = {x,(int)height, z,red,green,blue};
                picture.append(led);
            }
        }
        scenario->append(picture);
        delay->append(3);
        picture.clear();
    }

    emit doneCreating();
}

