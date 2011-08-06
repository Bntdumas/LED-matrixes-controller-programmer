#include "cubeConfiguration.h"
#include "ui_cubeConfiguration.h"

cubeConfiguration::cubeConfiguration(LedsSimulator *cube, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cubeConfiguration),
    m_cube(cube)
{
    ui->setupUi(this);
    init();
}
void cubeConfiguration::init()
{
    ui->sBx_ledX->setValue(m_cube->getXLeds());
    ui->sBx_ledY->setValue(m_cube->getYLeds());
    ui->sBx_ledZ->setValue(m_cube->getZLeds());

    ui->sBx_spacing->setValue(m_cube->getSpacing());
    ui->sBx_zoom->setValue(m_cube->getActualZoom());

    ui->btMonoChromeColor->hide();
}

cubeConfiguration::~cubeConfiguration()
{
    delete ui;
}
void cubeConfiguration::on_bt_defaultColor_clicked()
{
    QColorDialog *colorDialog = new QColorDialog(m_cube->getdefaultColor(), this);
    colorDialog->setOption ( QColorDialog::ShowAlphaChannel);
    connect(colorDialog, SIGNAL(currentColorChanged(QColor)), m_cube, SLOT(setOffColor(QColor)));
    colorDialog->show();

}

void cubeConfiguration::on_bt_backColor_clicked()
{
    QColorDialog *colorDialog = new QColorDialog(m_cube->getdefaultColor(), this);
    connect(colorDialog, SIGNAL(currentColorChanged(QColor)), m_cube, SLOT(setBackColor(QColor)));
    colorDialog->show();

}

void cubeConfiguration::on_sBx_ledX_valueChanged(int value)
{
    m_cube->setXLeds(value);
}

void cubeConfiguration::on_sBx_ledY_valueChanged(int value)
{
    m_cube->setYLeds(value);
}

void cubeConfiguration::on_sBx_ledZ_valueChanged(int value)
{
    m_cube->setZLeds(value);
}

void cubeConfiguration::on_sBx_spacing_valueChanged(int value)
{
    m_cube->setSpacing(value);
}

void cubeConfiguration::on_sBx_zoom_valueChanged(int value)
{
    m_cube->setZoom(value);
}


void cubeConfiguration::on_RazZoom_clicked()
{
    m_cube->razZoom();
}

void cubeConfiguration::on_btMonoChromeColor_clicked()
{
    QColorDialog *colorDialog = new QColorDialog(m_cube->getdefaultColor(), this);
    colorDialog->setOption ( QColorDialog::ShowAlphaChannel);
    connect(colorDialog, SIGNAL(currentColorChanged(QColor)), m_cube, SLOT(setMonoChromeColor(QColor)));
    colorDialog->show();
}

void cubeConfiguration::on_chbMonochrome_clicked(bool checked)
{
   m_cube->setMonochromeLeds(checked);
}
