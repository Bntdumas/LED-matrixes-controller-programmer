#ifndef SCENARIOCREATOR_H
#define SCENARIOCREATOR_H

#include <QWidget>
#include "fileInterface.h"
#include "LedsSimulator.h"
#include "threadLedCube.h"
#include "scenarioController.h"

#include "./predefinedScenarios/scenarioMovingCubes.h"
#include "./predefinedScenarios/scenarioWaves.h"
#include "./predefinedScenarios/scenarioMovingSquareRandSuspended.h"
#include "predefinedScenarios/scenarioRandom.h"

namespace Ui {
    class scenarioCreator;
}

class scenarioCreator : public QWidget
{
    Q_OBJECT

public:
    enum ScenarioType {
        Custom,
        MovingSquares,
        Waves,
        squaresRandomSuspended,
        random
    };

    explicit scenarioCreator(ScenarioType type, LedsSimulator *cube,  QWidget *parent = 0);
    ~scenarioCreator();

private slots:

    void on_bt_preview_clicked();
    void on_btScenarioFile_clicked();
    void on_btGenerate_clicked();

    void on_btSave_clicked();

    void previewDialogReturned();

    void scenarioAvailable();


private:
    enum WidgetPage {
        wdgCustom,
        wdgPredefined
    };

    void init();

    Ui::scenarioCreator *ui;
    threadLedCube *m_thread;
    LedsSimulator *m_ledCube;

    QList<LedState> m_picture;
    QList<int> m_delay;
    QList< QList<LedState> > m_scenario;

    QString m_filename;

    ScenarioType m_type;


    void resetPicture();
    void resetScenario();
    void writeScenario();

    void createMovingSquaresScenario();
    void createWavesScenario();
    void createsMovingSquareRandSuspended();
    void createsRandom();

};

#endif // SCENARIOCREATOR_H
