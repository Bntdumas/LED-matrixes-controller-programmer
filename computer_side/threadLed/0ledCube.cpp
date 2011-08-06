#include "ledCube.h"
#include "ui_ledCube.h"

ledCube::ledCube(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ledCube)
{
    ui->setupUi(this);
    updateLedCubeInfos();
    resetSpinBoxes();
    m_threadLedCube = new threadLedCube(this, ui->wdgLedCube);
    ui->wdgScenarioCreator->setThread(m_threadLedCube);
    ui->wdgScenarioCreator->setLedCubeWidget(ui->wdgLedCube);

}

ledCube::~ledCube()
{
    delete ui;
}

void ledCube::updateLedCubeInfos()
{
    ui->lbl_nbLed->setText(QString::number(ui->wdgLedCube->getNbLeds()));

    ui->lbl_ledX->setText(QString::number(ui->wdgLedCube->getXLeds()));
    ui->lbl_ledY->setText(QString::number(ui->wdgLedCube->getYLeds()));
    ui->lbl_ledZ->setText(QString::number(ui->wdgLedCube->getZLeds()));

    ui->lbl_spacing->setText(QString::number(ui->wdgLedCube->getSpacing()));
    ui->lbl_zoom->setText(QString::number(ui->wdgLedCube->getActualZoom()));

    ui->lbl_defaultColor->setText(ui->wdgLedCube->getdefaultColor().name());

    ui->wdgLedCube->update();
}

void ledCube::resetSpinBoxes()
{
   ui->sBx_ledX->setValue(ui->lbl_ledX->text().toInt());
   ui->sBx_ledY->setValue(ui->lbl_ledX->text().toInt());
   ui->sBx_ledZ->setValue(ui->lbl_ledX->text().toInt());

   ui->sBx_spacing->setValue(ui->lbl_spacing->text().toInt());
   ui->sBx_zoom->setValue(ui->lbl_zoom->text().toInt());
}

void ledCube::on_sBx_ledX_valueChanged(int leds)
{
    ui->wdgLedCube->setXLeds(leds);
    updateLedCubeInfos();

}

void ledCube::on_sBx_ledY_valueChanged(int leds)
{
    ui->wdgLedCube->setYLeds(leds);
    updateLedCubeInfos();
}

void ledCube::on_sBx_ledZ_valueChanged(int leds)
{
    ui->wdgLedCube->setZLeds(leds);
    updateLedCubeInfos();

}

void ledCube::on_sBx_spacing_valueChanged(int spacing)
{
    ui->wdgLedCube->setSpacing(spacing);
    updateLedCubeInfos();

}

void ledCube::on_sBx_zoom_valueChanged(int zoom)
{
    ui->wdgLedCube->changeZoom(zoom);
    updateLedCubeInfos();
}

void ledCube::on_bt_defaultColor_clicked()
{
    QColorDialog *colorDialog = new QColorDialog(ui->wdgLedCube->getdefaultColor(), this);
    colorDialog->setOption ( QColorDialog::ShowAlphaChannel);
    connect(colorDialog, SIGNAL(currentColorChanged(QColor)), ui->wdgLedCube, SLOT(setOffColor(QColor)));
    connect(colorDialog, SIGNAL(finished(int)), this, SLOT(updateLedCubeInfos()));
    colorDialog->show();
}

void ledCube::on_bt_backColor_clicked()
{
    QColorDialog *colorDialog = new QColorDialog(ui->wdgLedCube->getdefaultColor(), this);
    colorDialog->setOption ( QColorDialog::ShowAlphaChannel);
    connect(colorDialog, SIGNAL(currentColorChanged(QColor)), ui->wdgLedCube, SLOT(setBackColor(QColor)));
    connect(colorDialog, SIGNAL(finished(int)), this, SLOT(updateLedCubeInfos()));
    colorDialog->show();
}
