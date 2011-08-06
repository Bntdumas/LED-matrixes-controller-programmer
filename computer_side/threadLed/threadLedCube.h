#ifndef THREADLEDCUBE_H
#define THREADLEDCUBE_H

#include <QThread>
#include <QObject>
#include <QMutex>
#include <QWaitCondition>

#include <QMessageBox>

#include "LedsSimulator.h"
#include "fileInterface.h"

enum threadState{
    stopped,
    playing,
    paused
};

class threadLedCube : public QThread
{
    Q_OBJECT
public:

    explicit threadLedCube(LedsSimulator *ledCube, QObject *parent = 0);
    ~threadLedCube();
    void setState(threadState state);
    threadState getState();
    void loadScenarioFromFile(const QString & filename);
    void setCurrentFrame(int frame);
    void setLoopMode (bool flag);
    void setManual(bool flag);
    void resetCube();

    void prepareDelete();

    void resetThread();

protected:
    void run();

public slots:
    void setScenario(QList<QList<LedState> > ,QList<int>,QString &);
signals:
    void staticInfos(int totalFrames,int totalTime);
    void currentInfos(int currentFrame, int currentTime);
    void singleLoopFinished();
    void pictureDrawn();

private:

    void setPausedPicture(int *);

    LedsSimulator *m_LedsSimulator;
    bool m_readyPlay;
    threadState m_state;

    bool m_loopMode;
    bool m_manual;

    bool m_toBeDeleted;

    int m_indexOfWantedFrame;

    QList<int> m_delay;
    QList< QList<LedState> > m_scenario;
    QString m_cubeData;

    QMutex m_mutex;
    QWaitCondition m_condition;



};

#endif // THREADLEDCUBE_H
