#ifndef SCENARIOCONTROLLER_H
#define SCENARIOCONTROLLER_H

#include <QDialog>
#include <QDebug>

#include "LedsSimulator.h"
#include "threadLedCube.h"


namespace Ui {
    class scenarioController;
}

class scenarioController : public QDialog
{
    Q_OBJECT

public:
    explicit scenarioController(LedsSimulator * cube,bool fileBased = true ,  QWidget *parent = 0);
    ~scenarioController();
    threadLedCube * getThreadPtr();

private slots:

    void on_btPlay_clicked();
    void on_btStop_clicked();
    void on_horizontalSlider_valueChanged(int value);

    void staticScenarioInfos(int totalFrames, int totalTime);
    void currentScenarioInfos(int currentFrame, int currentTime);

    void on_btScenarioFile_clicked();

    void on_chbLoop_toggled(bool checked);

    void on_cbManualSeek_toggled(bool checked);

private:
    Ui::scenarioController *ui;
    threadLedCube *m_cubeEngine;

    QString m_filename;

    void initScenario();
    void init();
    void setCommandsEnabled(bool flag);

    bool m_fileBased;
    bool m_sliderMovedManually;

    int m_totalFrames;

};

#endif // SCENARIOCONTROLLER_H
