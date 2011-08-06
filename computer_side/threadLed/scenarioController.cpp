#include "scenarioController.h"
#include "ui_scenarioController.h"

scenarioController::scenarioController(LedsSimulator *cube,bool fileBased /* = true */,  QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scenarioController),
    m_fileBased(fileBased)
{
    ui->setupUi(this);
    m_cubeEngine = new threadLedCube(cube);
    connect (m_cubeEngine, SIGNAL(currentInfos(int,int)), this, SLOT(currentScenarioInfos(int,int)));
    connect (m_cubeEngine, SIGNAL(staticInfos(int,int)), this, SLOT(staticScenarioInfos(int,int)));
    connect (m_cubeEngine, SIGNAL(singleLoopFinished()), this, SLOT(on_btStop_clicked()));

    init();
}
void scenarioController::init()
{
    m_filename = QString();
    m_sliderMovedManually= 0;
    m_totalFrames= 0;
    if (!m_fileBased)
    {
        ui->gBoxFile->hide();
        ui->checkBox->hide();
        ui->gBControls->setEnabled(false);
    }
    else ui->gBControls->setEnabled(true);

    ui->chbLoop->setEnabled(true);
    ui->cbManualSeek->setEnabled(true);
    ui->btStop->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);

    ui->lblScenarioFile->setText(("no file selected"));
}

threadLedCube * scenarioController::getThreadPtr()
{
    return m_cubeEngine;
}

void scenarioController::staticScenarioInfos(int totalFrames,int totalTime)
{
    m_totalFrames = totalFrames;
    ui->lblNbFrames->setText(QString::number(m_totalFrames));
    ui->lblTotalTime->setText(QString::number(totalTime/1000.0) + tr("s"));
    ui->horizontalSlider->setMaximum(m_totalFrames);
    ui->gBControls->setEnabled(true);
}

void scenarioController::currentScenarioInfos(int currentFrame, int currentTime)
{
    ui->lblFrame->setText(QString::number(currentFrame+1));
    ui->lblCurrentTime->setText(QString::number(currentTime/1000.0)+ tr("s"));
    if (!ui->cbManualSeek->isChecked())
        ui->horizontalSlider->setValue(currentFrame+1);

}

void scenarioController::on_btScenarioFile_clicked()
{
    m_filename = QFileDialog::getOpenFileName(0, tr("Select scenario file"), "./scenario", tr("CSV files (*.csv)"));
    ui->lblScenarioFile->setText(m_filename);
}

scenarioController::~scenarioController()
{
    m_cubeEngine->prepareDelete();
    QMessageBox msgBox;
    msgBox.setText(tr("closing the cube playing engine, please wait..."));
    msgBox.setStandardButtons(QMessageBox::NoButton);
    msgBox.show();
    while (!m_cubeEngine->wait());
    delete m_cubeEngine;
    delete ui;
}
void scenarioController::initScenario()
{
    if (m_fileBased)
    {
        m_cubeEngine->loadScenarioFromFile(m_filename);

        ui->gBoxFile->hide();
        ui->checkBox->hide();
        ui->gBControls->setEnabled(false);
        ui->gBControls->setEnabled(true);

        ui->chbLoop->setEnabled(false);
        ui->cbManualSeek->setEnabled(false);
        ui->btStop->setEnabled(false);
        ui->horizontalSlider->setEnabled(false);
    }

}

void scenarioController::on_btPlay_clicked()
{
    m_cubeEngine->setCurrentFrame(-1);
    m_cubeEngine->setLoopMode(ui->chbLoop->isChecked());

    threadState cubeEngineState = m_cubeEngine->getState();
    switch (cubeEngineState)
    {
    case stopped:
        if (m_fileBased)
            initScenario();
        m_cubeEngine->setCurrentFrame(0);
        m_cubeEngine->setState(playing);
        ui->btPlay->setText(tr("pause"));
        ui->btStop->setEnabled(true);
        break;

    case playing:
        m_cubeEngine->setState(paused);
        ui->btPlay->setText(tr("play"));
        ui->btStop->setEnabled(true);
        break;

    case paused:
        m_cubeEngine->setState(playing);
        ui->btPlay->setText(tr("pause"));
        ui->btStop->setEnabled(true);
        break;

    }
    ui->chbLoop->setEnabled(false);
    ui->checkBox->setEnabled(false);
}

void scenarioController::on_btStop_clicked()
{
    ui->chbLoop->setEnabled(true);
    ui->checkBox->setEnabled(true);
    threadState cubeEngineState = m_cubeEngine->getState();
    if(cubeEngineState == playing || cubeEngineState == paused)
    {
        m_cubeEngine->resetCube();
        ui->btPlay->setText(tr("play"));
        m_cubeEngine->setState(stopped);
    }
    ui->btStop->setEnabled(false);
    ui->horizontalSlider->setValue(1);
}

void scenarioController::on_horizontalSlider_valueChanged(int value)
{
    if (ui->cbManualSeek->isChecked())
    {
        m_cubeEngine->setCurrentFrame(value);
        m_sliderMovedManually = false;
    }
}

void scenarioController::on_chbLoop_toggled(bool checked)
{
    m_cubeEngine->setLoopMode(checked);
    on_btStop_clicked();
}


void scenarioController::on_cbManualSeek_toggled(bool checked)
{
    on_btStop_clicked();
    ui->horizontalSlider->setEnabled(checked);
    ui->chbLoop->setChecked(false);
    ui->chbLoop->setEnabled(!checked);
    m_cubeEngine->setCurrentFrame(1);
    if (checked)
    {
        ui->btPlay->setEnabled(false);
        m_cubeEngine->setState(playing);
    }
    else ui->btPlay->setEnabled(true);
}
