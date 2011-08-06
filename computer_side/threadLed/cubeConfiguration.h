#ifndef CUBECONFIGURATION_H
#define CUBECONFIGURATION_H

#include <QDialog>
#include <QColorDialog>

#include "LedsSimulator.h"

namespace Ui {
    class cubeConfiguration;
}

class cubeConfiguration : public QDialog
{
    Q_OBJECT

public:
    explicit cubeConfiguration(LedsSimulator *cube, QWidget *parent = 0);
    ~cubeConfiguration();

private slots:
    void on_sBx_ledX_valueChanged(int );
    void on_sBx_ledY_valueChanged(int );
    void on_sBx_ledZ_valueChanged(int );
    void on_sBx_spacing_valueChanged(int );
    void on_sBx_zoom_valueChanged(int );
    void on_bt_defaultColor_clicked();
    void on_bt_backColor_clicked();

    void on_RazZoom_clicked();

    void on_btMonoChromeColor_clicked();

    void on_chbMonochrome_clicked(bool checked);

private:
    Ui::cubeConfiguration *ui;
    LedsSimulator *m_cube;

    void init();
};

#endif // CUBECONFIGURATION_H
