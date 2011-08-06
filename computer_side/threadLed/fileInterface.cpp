#include "fileInterface.h"
#include <QDebug>

fileInterface::fileInterface(const QString & filename, QObject *parent) :
    QObject(parent), m_filename(filename)
{
    m_scenario.clear();
    m_picture.clear();
    m_delay.clear();
}
void fileInterface::setCubeData(int x, int y, int z, int spacing, QColor defaultColor)
{
    QString cubeData = QString::number(x) + "," + QString::number(y) + "," + QString::number(z) + "," + QString::number(spacing);
    setCubeData(cubeData, defaultColor);
}
void fileInterface::setCubeData(const QString & data, QColor offColor)
{
    m_cubeData = data;

    QString colorName = offColor.name();
    colorName.remove("#");
    colorName.prepend("#" + QString::number(offColor.alpha(),16));
    m_cubeData.append(","+ colorName + "\n");

}
void fileInterface::startPicture()
{
    m_picture.clear();
}

void fileInterface::endPicture(int delay)
{
    if (!m_picture.isEmpty())
        m_scenario.append(m_picture);
    m_delay.append(delay);
}

void fileInterface::addLedState(LedState led)
{
    m_picture.append(led);
}


void fileInterface::writeScenario()
{
   qDebug() << "write scenario";
    QFile newScenarioFile (m_filename);
    if(!newScenarioFile.open(QIODevice::WriteOnly)){
        QMessageBox::critical(0, tr("Error"), tr("Couldn't open file %s.\n.", qPrintable(m_filename)), QMessageBox::Abort);
        return ;
    }
    newScenarioFile.write(tr("Begin LED Scenario\n").toAscii());
    newScenarioFile.write(m_cubeData.toAscii());
    int pictureDelay = 0;
    Q_FOREACH(QList<LedState> picture, m_scenario)
    {
       newScenarioFile.write(tr("Begin Picture\n").toAscii());
       Q_FOREACH(LedState Led, picture)
       {

       newScenarioFile.write(QString(QString::number(Led.x) + "," +
                             QString::number(Led.y) + "," +
                             QString::number(Led.z) + "," +
                             QString::number(Led.red) + "," +
                             QString::number(Led.green) + "," +
                             QString::number(Led.blue) + "\n").toAscii());
       }

       newScenarioFile.write(tr("Delay\n").toAscii());
       newScenarioFile.write(QString(QString::number(m_delay.at(pictureDelay)) + "\n").toAscii());
   }
    m_scenario.clear();
    m_picture.clear();
    m_delay.clear();
    m_cubeData.clear();
}

void fileInterface::readScenario()
{

    QFile scenarioFile (m_filename);
    if(!scenarioFile.open(QIODevice::ReadOnly)){
        QMessageBox::critical(0, tr("Error"), tr("Couldn't open file %s.\n.", qPrintable(m_filename)), QMessageBox::Abort);
        return ;
    }

    QString line = scenarioFile.readLine();
    line.chop(1);
    QStringList strDataLed;
    if (line != tr("Begin LED Scenario"))
    {
        QMessageBox::critical(0, tr("Error"), tr("invalid Scenario data"), QMessageBox::Abort);
        return;
    }
    m_cubeData = scenarioFile.readLine();
    while (!scenarioFile.atEnd())
    {
        line = scenarioFile.readLine();
        line.chop(1);
        if (line != tr("Begin Picture"))
        {
            QMessageBox::critical(0, tr("Error"), tr("invalid Picture data"), QMessageBox::Abort);
            return;
        }
        m_picture.clear();
        while (line != tr("Delay"))
        {
            line = scenarioFile.readLine();
            line.chop(1);
            if(line == tr("Delay"))
                break;
            strDataLed = line.split(",");
            if (strDataLed.count() != 6)
            {
                QMessageBox::critical(0, tr("Error"), tr("invalid LED data"), QMessageBox::Abort);
                return;
            }
            LedState Led;
            Led.x = strDataLed[0].toInt();
            Led.y = strDataLed[1].toInt();
            Led.z = strDataLed[2].toInt();

            Led.red = strDataLed[3].toInt();
            Led.green = strDataLed[4].toInt();
            Led.blue = strDataLed[5].toInt();

            m_picture.append(Led);
        }
        line = scenarioFile.readLine();
        line.chop(1);
        m_delay.append(line.toInt());
        m_scenario.append(m_picture);
    }
    emit scenarioLoaded(m_scenario, m_delay, m_cubeData);

    m_scenario.clear();
    m_picture.clear();
    m_delay.clear();
    m_cubeData.clear();
}


QString fileInterface::getFileName()
{
    return m_filename;
}

