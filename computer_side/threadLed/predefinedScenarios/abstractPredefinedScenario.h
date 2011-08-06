#ifndef ABSTRACTPREDEFINEDSCENARIO_H
#define ABSTRACTPREDEFINEDSCENARIO_H

#include <QObject>
#include <QColor>

#include "fileInterface.h"
#include "coordinates_functions.h"


class abstractPredefinedScenario : public QObject
{
    Q_OBJECT
public:
    explicit abstractPredefinedScenario(QObject *parent = 0);
    void setCubeInfos(int x, int y, int z, bool monochrome, QColor monochromeColor);

protected:
    virtual void makeScenario(QList< QList<LedState> > * scenario, QList<int> *delay) = 0;

    int m_xSize;
    int m_ySize;
    int m_zSize;

    bool m_monochrome;
    QColor m_monochromeColor;

signals:
    void doneCreating();


};

#endif // ABSTRACTPREDEFINEDSCENARIO_H
