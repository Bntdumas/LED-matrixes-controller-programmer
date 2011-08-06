#include "customScenario.h"
#include "ui_customScenario.h"

customScenario::customScenario(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::customScenario)
{
    ui->setupUi(this);
}

customScenario::~customScenario()
{
    delete ui;
}
