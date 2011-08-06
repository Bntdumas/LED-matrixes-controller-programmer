#include "ledCube.h"
#include "ui_ledCube.h"



ledCube::ledCube(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ledCube),
    m_arduino(0)
{
    ui->setupUi(this);
    init();
}

ledCube::~ledCube()
{
    delete ui;
}
void ledCube::init()
{
    m_infoCubeStatusBar = new QLabel();
    m_infoCubeStatusBar->setAlignment(Qt::AlignHCenter);
    updateStatusBar();
    ui->statusbar->addPermanentWidget(m_infoCubeStatusBar);
    connect (ui->wdgLedCube, SIGNAL(cubeModified()), this, SLOT(updateStatusBar()));
    ui->arduinoOutput->hide();
}
QString ledCube::statusBarCubeInfos()
{
    return tr("Leds: ") + QString::number(ui->wdgLedCube->getNbLeds()) +
        tr(" x: ") + QString::number(ui->wdgLedCube->getXLeds()) +
        tr(" y: ") + QString::number(ui->wdgLedCube->getYLeds()) +
        tr(" z: ") + QString::number(ui->wdgLedCube->getZLeds()) +
        tr(" spacing: ") + QString::number(ui->wdgLedCube->getSpacing()) +
        tr(" zoom: ") + QString::number(ui->wdgLedCube->getActualZoom()) +
        tr(" default color: ") + ui->wdgLedCube->getdefaultColor().name();
}
void ledCube::updateStatusBar()
{
    m_infoCubeStatusBar->setText(statusBarCubeInfos());
}

void ledCube::updateStatusBar(const QString& stringToPrepend)
{
    qDebug() << stringToPrepend;
    QString text = statusBarCubeInfos();
    text.prepend("<b>" + stringToPrepend + "</b> ");
    m_infoCubeStatusBar->setText(text.remove("\n"));
}

void ledCube::on_actionConfigure_triggered()
{
    cubeConfiguration *dlgconfig = new cubeConfiguration(ui->wdgLedCube);
    dlgconfig->setAttribute(Qt::WA_DeleteOnClose);
    connect(dlgconfig, SIGNAL(destroyed()), this, SLOT(blockingWindowDestroyed()));
    dlgconfig->show();
    disableActions(true);
}

void ledCube::on_actionOpen_triggered()
{
    scenarioController *controller = new scenarioController(ui->wdgLedCube);
    controller->setAttribute(Qt::WA_DeleteOnClose);
    connect(controller, SIGNAL(destroyed()), this, SLOT(blockingWindowDestroyed()));
    controller->show();
    disableActions(true);
}

void ledCube::on_actionArduino_triggered()
{
    if(m_arduino)
        delete m_arduino;
    m_arduino = 0;
    m_arduino = new arduinoLedSerial(ui->wdgLedCube,ui->arduinoOutput, this, "/dev/ttyACM0", 115200);
    connect(ui->wdgLedCube , SIGNAL(cubeReDraw()), m_arduino, SLOT(updateCube()));
   // connect(m_arduino, SIGNAL(lineAvailable(QString)), this, SLOT(updateStatusBar(QString)));
}

void ledCube::on_actionSystem_triggered()
{
    QMessageBox::information(0,0,tr("this feature is not implemented yet"));
}

void ledCube::on_actionCustom_triggered()
{
    //scenarioCreator customScenario;
    QMessageBox::information(0,0,tr("this feature is not implemented yet"));
}

void ledCube::on_actionMoving_plane_triggered()
{
    scenarioCreator *scenarioMovingPlanes = new scenarioCreator(scenarioCreator::MovingSquares, ui->wdgLedCube);
    scenarioMovingPlanes->setAttribute(Qt::WA_DeleteOnClose);
    connect(scenarioMovingPlanes, SIGNAL(destroyed()), this, SLOT(blockingWindowDestroyed()));
    scenarioMovingPlanes->show();
    disableActions(true);
}

void ledCube::on_actionWaves_triggered()
{
    scenarioCreator *scenarioWaves = new scenarioCreator(scenarioCreator::Waves, ui->wdgLedCube);
    scenarioWaves->setAttribute(Qt::WA_DeleteOnClose);
    connect(scenarioWaves, SIGNAL(destroyed()), this, SLOT(blockingWindowDestroyed()));
    scenarioWaves->show();
    disableActions(true);
}

void ledCube::blockingWindowDestroyed()
{
    disableActions(false);
}

void ledCube::disableActions(bool flag)
{
    ui->actionConfigure->setEnabled(!flag);
    ui->actionArduino->setEnabled(!flag);
    ui->actionCustom->setEnabled(!flag);
    ui->actionMoving_plane->setEnabled(!flag);
    ui->actionOpen->setEnabled(!flag);
    ui->actionSystem->setEnabled(!flag);
    ui->actionWaves->setEnabled(!flag);

}

void ledCube::on_actionSquare_random_suspended_triggered()
{
    scenarioCreator *scenarioWaves = new scenarioCreator(scenarioCreator::squaresRandomSuspended, ui->wdgLedCube);
    scenarioWaves->setAttribute(Qt::WA_DeleteOnClose);
    connect(scenarioWaves, SIGNAL(destroyed()), this, SLOT(blockingWindowDestroyed()));
    scenarioWaves->show();
    disableActions(true);
}

void ledCube::on_actionRandom_triggered()
{
    scenarioCreator *scenarioWaves = new scenarioCreator(scenarioCreator::random, ui->wdgLedCube);
    scenarioWaves->setAttribute(Qt::WA_DeleteOnClose);
    connect(scenarioWaves, SIGNAL(destroyed()), this, SLOT(blockingWindowDestroyed()));
    scenarioWaves->show();
    disableActions(true);
}

void ledCube::on_actionDisconnect_triggered()
{
    if (m_arduino)
        delete m_arduino;
    m_arduino = 0;
    ui->menuArduino->hide();
    ui->arduinoOutput->hide();
}

void ledCube::on_actionShow_log_triggered(bool checked)
{
    ui->arduinoOutput->setVisible(checked);
    ui->actionShow_log->setChecked(checked);
}
