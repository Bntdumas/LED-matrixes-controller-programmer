#include "threadLedCube.h"
#include <QDebug>


threadLedCube::threadLedCube(LedsSimulator *ledCube, QObject *parent /*= 0*/):
    QThread(parent),
    m_LedsSimulator(ledCube),
    m_readyPlay(false),
    m_state(stopped),
    m_loopMode(false),
    m_manual(false),
    m_toBeDeleted(false),
    m_indexOfWantedFrame(-1)
{

}
void threadLedCube::prepareDelete()
{
    m_toBeDeleted = true;
    m_state = playing;
    m_condition.wakeAll();
}

threadLedCube::~threadLedCube()
{
    m_LedsSimulator->allOff();
    m_LedsSimulator->update();
}

void threadLedCube::resetCube()
{
    m_LedsSimulator->allOff();
    m_LedsSimulator->update();
}

void threadLedCube::setState(threadState state)
{

    switch (state)
    {
    case stopped:
        m_mutex.lock();
        m_state = state;
        m_mutex.unlock();
        if (m_loopMode)
        {
            m_LedsSimulator->allOff();
            m_LedsSimulator->update();
        }
        break;

    case playing:
        m_mutex.lock();
        m_state = state;
        if (!isRunning())
            start(LowPriority);
        else m_condition.wakeOne();
        m_mutex.unlock();
        break;

    case paused:
        m_mutex.lock();
        m_state = state;
        if (!isRunning())
            start(LowPriority);
        else m_condition.wakeOne();
        m_mutex.unlock();
        break;
    }
}
threadState threadLedCube::getState()
{
    return m_state;
}

void threadLedCube::loadScenarioFromFile(const QString & filename)
{
    m_readyPlay = false;

   fileInterface *scenarioFileLoad = new fileInterface(filename);

   scenarioFileLoad->setCubeData(m_LedsSimulator->getXLeds(),
                                 m_LedsSimulator->getYLeds(),
                                 m_LedsSimulator->getZLeds(),
                                 m_LedsSimulator->getSpacing(),
                                 m_LedsSimulator->getdefaultColor());

   connect (scenarioFileLoad, SIGNAL(scenarioLoaded(QList<QList<LedState> >,QList<int>,QString &)), this, SLOT(setScenario(QList<QList<LedState> >,QList<int>,QString &)));
   scenarioFileLoad->readScenario();
}
void threadLedCube::setCurrentFrame(int frame)
{
   m_mutex.lock();
    if (frame > 0 && frame <= m_scenario.count())
    {
        m_indexOfWantedFrame = frame-1;
        m_loopMode = true;
    }
    else m_indexOfWantedFrame = -1;
    m_mutex.unlock();

}

void threadLedCube::setLoopMode (bool flag)
{
   m_mutex.lock();
   m_loopMode = flag;
   m_mutex.unlock();
}
void threadLedCube::setManual(bool flag)
{
    m_mutex.lock();
    m_manual = flag;
    m_loopMode = !flag;
    m_mutex.unlock();
}
void threadLedCube::run()
{
    while(!m_toBeDeleted){

        int currentTime = 0;

        int nbrOfFrames;
        if (m_indexOfWantedFrame == -1)
            nbrOfFrames = m_scenario.count();
        else nbrOfFrames = 1;

        if (!m_scenario.isEmpty())
            for (int currentFrame = 0 ; currentFrame <  nbrOfFrames; currentFrame++)
            {
                int currentIndex = currentFrame;
                if (m_indexOfWantedFrame != -1)
                    currentIndex = m_indexOfWantedFrame;

                m_mutex.lock();
                QList<LedState> picture = m_scenario.at(currentIndex);
                int delay = m_delay.at(currentIndex);
                m_mutex.unlock();

                m_LedsSimulator->allOff();
                Q_FOREACH(LedState led, picture)
                {
                    QColor color = QColor(led.red, led.green, led.blue, 120);
                    m_LedsSimulator->setLed(led.x,led.y,led.z,color);
                }
                m_LedsSimulator->update();

                m_mutex.lock();


                emit currentInfos(currentIndex, currentTime += delay );


                if (m_state == paused)
                {
                    //setPausedPicture(&currentIndex);
                    //emit currentInfos(currentIndex, currentTime += delay );
                    m_condition.wait(&m_mutex);
                }

                else if (m_state == stopped)
                {
                    m_LedsSimulator->allOff();
                    m_LedsSimulator->update();
                    currentIndex = 0;
                    break;

                }
                m_mutex.unlock();

                msleep(delay);

            }
        m_mutex.lock();
        if (!m_loopMode && !m_toBeDeleted || m_state == stopped)
        {
            emit singleLoopFinished();
            m_condition.wait(&m_mutex);
        }
        m_mutex.unlock();
    }
}

void threadLedCube::setPausedPicture(int * currentIndex)
{
    //todo
}

void threadLedCube::setScenario(QList< QList<LedState> > scenario ,QList<int> delay, QString & cubeData)
{
    m_cubeData = cubeData;
    m_readyPlay = false;

    m_delay.clear();
    m_scenario.clear();

    cubeData.chop(1);
    QStringList cubeDataList = cubeData.split(",");
    if (cubeDataList.count() != 5)
    {
        QMessageBox::critical(0,0,tr("cube informations from file seems corrupted \n aborting..."));
        return;
    }

    m_LedsSimulator->setXLeds(cubeDataList.at(0).toInt());
    m_LedsSimulator->setYLeds(cubeDataList.at(1).toInt());
    m_LedsSimulator->setZLeds(cubeDataList.at(2).toInt());

    m_LedsSimulator->setSpacing(cubeDataList.at(3).toInt());

    QString colorName = cubeDataList.at(4);
    colorName.remove("#");
    QRgb colorWithAlpha = colorName.toUInt(0,16);
    QColor qcolorWithAlpha;
    qcolorWithAlpha.setRgba(colorWithAlpha);
    m_LedsSimulator->setOffColor(QColor(qcolorWithAlpha));

    m_delay = delay;
    m_scenario = scenario;

    int totalTime = 0.0;
    QListIterator<int> i(m_delay);
    while (i.hasNext())
        totalTime += i.next();

    m_readyPlay = true;
    setState(paused);
    emit staticInfos((int)m_scenario.count(), totalTime);
}

