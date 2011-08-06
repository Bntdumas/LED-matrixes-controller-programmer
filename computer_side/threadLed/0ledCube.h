#ifndef LEDCUBE_H
#define LEDCUBE_H

#include <QWidget>
#include <QColorDialog>
#include "threadLedCube.h"

namespace Ui {
    class ledCube;
}

class ledCube : public QWidget
{
    Q_OBJECT

public:
    explicit ledCube(QWidget *parent = 0);
    ~ledCube();

private slots:

    void on_sBx_ledX_valueChanged(int );
    void on_sBx_ledY_valueChanged(int );
    void on_sBx_ledZ_valueChanged(int );
    void on_sBx_spacing_valueChanged(int );
    void on_sBx_zoom_valueChanged(int );
    void on_bt_defaultColor_clicked();
    void updateLedCubeInfos();
    void on_bt_backColor_clicked();

private:
    Ui::ledCube *ui;
    threadLedCube *m_threadLedCube;
    void resetSpinBoxes();

};

#endif // LEDCUBE_H
