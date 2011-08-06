#include "scenarioCreator.h"
#include "ui_scenarioCreator.h"

scenarioCreator::scenarioCreator(ScenarioType type, LedsSimulator *cube, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::scenarioCreator),
    m_ledCube(cube),
    m_type(type)
{
    ui->setupUi(this);
    init();
}

void scenarioCreator::init()
{
    resetScenario();

    if (m_type == Custom)
        ui->stackedWidget->setCurrentIndex(wdgCustom);
    else
        ui->stackedWidget->setCurrentIndex(wdgPredefined);
    ui->lblScenarioStatus->setText(tr("no scenario available") );
    m_filename= QString();

    ui->bt_preview->setEnabled(false);
}

scenarioCreator::~scenarioCreator()
{
    delete ui;
}

void scenarioCreator::resetPicture()
{
    m_picture.clear();
}

void scenarioCreator::resetScenario()
{
    m_scenario.clear();
    m_delay.clear();
    resetPicture();
}

void scenarioCreator::writeScenario()
{
    fileInterface fileWriter(m_filename + tr(".csv"));
    fileWriter.setCubeData(m_ledCube->getXLeds(),
                           m_ledCube->getYLeds(),
                           m_ledCube->getZLeds(),
                           m_ledCube->getSpacing(),
                           m_ledCube->getdefaultColor());

    Q_FOREACH(QList<LedState> picture, m_scenario )
    {
        fileWriter.startPicture();
        Q_FOREACH(LedState led, picture )
            fileWriter.addLedState(led);
        fileWriter.endPicture(100);
    }
    fileWriter.writeScenario();
    QMessageBox::information(0, tr("Info"), tr("the scenario have been written in \n %1").arg(m_filename + tr(".csv")) );
    resetScenario();
}

void scenarioCreator::createMovingSquaresScenario()
{
    ui->bt_preview->setEnabled(false);
    ui->lblScenarioStatus->setText(tr("processing scenario...") );
    resetScenario();
    scenarioMovingCubes movingCubes;
    connect(&movingCubes, SIGNAL(doneCreating()), this, SLOT(scenarioAvailable()));
    movingCubes.setCubeInfos(m_ledCube->getXLeds(), m_ledCube->getYLeds(), m_ledCube->getZLeds(), m_ledCube->hasMonoChromeLeds(),  m_ledCube->getMonochromeColor());
    movingCubes.makeScenario(&m_scenario, &m_delay);
}

void scenarioCreator::createWavesScenario()
{
    ui->bt_preview->setEnabled(false);
    ui->lblScenarioStatus->setText(tr("processing scenario...") );
    resetScenario();
    scenarioWaves waves;
    connect(&waves, SIGNAL(doneCreating()), this, SLOT(scenarioAvailable()));
    waves.setCubeInfos(m_ledCube->getXLeds(), m_ledCube->getYLeds(), m_ledCube->getZLeds(), m_ledCube->hasMonoChromeLeds(),  m_ledCube->getMonochromeColor());
    waves.makeScenario(&m_scenario, &m_delay);
}
void scenarioCreator::createsMovingSquareRandSuspended()
{
    ui->bt_preview->setEnabled(false);
    ui->lblScenarioStatus->setText(tr("processing scenario...") );
    resetScenario();
    scenarioMovingSquareRandSuspended squaresSuspended;
    connect(&squaresSuspended, SIGNAL(doneCreating()), this, SLOT(scenarioAvailable()));
    squaresSuspended.setCubeInfos(m_ledCube->getXLeds(), m_ledCube->getYLeds(), m_ledCube->getZLeds(), m_ledCube->hasMonoChromeLeds(),  m_ledCube->getMonochromeColor());
    squaresSuspended.makeScenario(&m_scenario, &m_delay);
}

void scenarioCreator::createsRandom()
{
    ui->bt_preview->setEnabled(false);
    ui->lblScenarioStatus->setText(tr("processing scenario...") );
    resetScenario();
    scenarioRandom randomLeds;
    connect(&randomLeds, SIGNAL(doneCreating()), this, SLOT(scenarioAvailable()));
    randomLeds.setCubeInfos(m_ledCube->getXLeds(), m_ledCube->getYLeds(), m_ledCube->getZLeds(), m_ledCube->hasMonoChromeLeds(),  m_ledCube->getMonochromeColor());
    randomLeds.makeScenario(&m_scenario, &m_delay);
}

void scenarioCreator::scenarioAvailable()
{
    ui->lblScenarioStatus->setText(tr("a scenario is available \n  for preview/save.") );
    ui->bt_preview->setEnabled(true);
}

void scenarioCreator::on_bt_preview_clicked()
{

    QString cubeData = QString::number(m_ledCube->getXLeds()) + tr(",") +
                       QString::number(m_ledCube->getYLeds()) + tr(",") +
                       QString::number(m_ledCube->getZLeds()) + tr(",") +
                       QString::number( m_ledCube->getSpacing());

    QColor offColor = m_ledCube->getdefaultColor();
    QString colorName = offColor.name();
    colorName.remove("#");
    colorName.prepend("#" + QString::number(offColor.alpha(),16));
    cubeData.append(","+ colorName + "\n");

    scenarioController *controller = new scenarioController(m_ledCube, false);
    controller->setAttribute(Qt::WA_DeleteOnClose);
    connect(controller, SIGNAL(destroyed()), this, SLOT(previewDialogReturned()));
    controller->getThreadPtr()->setScenario(m_scenario,m_delay,cubeData);
    controller->show();
    hide();
}
void scenarioCreator::previewDialogReturned()
{
    show();
}

void scenarioCreator::on_btScenarioFile_clicked()
{
    m_filename = QFileDialog::getOpenFileName(0, tr("Select scenario file"), "./scenario", tr("CSV files (*.csv)"));
    ui->lblScenarioFile->setText(m_filename);
}

void scenarioCreator::on_btGenerate_clicked()
{
    switch (m_type)
    {
    case MovingSquares:
        createMovingSquaresScenario();
        break;

    case Waves:
        createWavesScenario();
        break;

    case squaresRandomSuspended:
        createsMovingSquareRandSuspended();
        break;

    default:
        break;
    }
}

void scenarioCreator::on_btSave_clicked()
{
    writeScenario();
}
