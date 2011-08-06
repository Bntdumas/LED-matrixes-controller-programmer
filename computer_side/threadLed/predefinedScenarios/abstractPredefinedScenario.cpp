#include "abstractPredefinedScenario.h"

abstractPredefinedScenario::abstractPredefinedScenario(QObject *parent) :
    QObject(parent)
{
}

void abstractPredefinedScenario::setCubeInfos(int x, int y, int z, bool monochrome, QColor monochromeColor)
{
    m_xSize = x;
    m_ySize = y;
    m_zSize = z;

    m_monochrome = monochrome;
    m_monochromeColor = monochromeColor;
}
