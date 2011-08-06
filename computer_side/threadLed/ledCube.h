#ifndef LEDCUBE_H
#define LEDCUBE_H

#include <QMainWindow>
#include <QColorDialog>
#include <QLabel>

#include "arduinoLedSerial.h"
#include "threadLedCube.h"
#include "cubeConfiguration.h"
#include "scenarioCreator.h"
#include "scenarioController.h"

//#include "LedsSimulator.h"

//#include "fileInterface.h"

//

namespace Ui {
    class ledCube;
}

class ledCube : public QMainWindow
{
    Q_OBJECT

public:
    explicit ledCube(QWidget *parent = 0);
    ~ledCube();

private slots:
    void updateStatusBar();
    void updateStatusBar(const QString& stringToPrepend);
    void blockingWindowDestroyed();

    void on_actionConfigure_triggered();

    void on_actionOpen_triggered();

    void on_actionCustom_triggered();

    void on_actionWaves_triggered();
    void on_actionMoving_plane_triggered();

    void on_actionArduino_triggered();
    void on_actionSystem_triggered();

    void on_actionSquare_random_suspended_triggered();

    void on_actionRandom_triggered();

    void on_actionDisconnect_triggered();

    void on_actionShow_log_triggered(bool checked);

private:

    void init();
    QString statusBarCubeInfos();
    void disableActions(bool flag);
    Ui::ledCube *ui;
    arduinoLedSerial *m_arduino;
    QLabel *m_infoCubeStatusBar;

};

#endif // LEDCUBE_H
