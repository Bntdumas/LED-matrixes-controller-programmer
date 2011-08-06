#ifndef CUSTOMSCENARIO_H
#define CUSTOMSCENARIO_H

#include <QWidget>

namespace Ui {
    class customScenario;
}

class customScenario : public QWidget
{
    Q_OBJECT

public:
    explicit customScenario(QWidget *parent = 0);
    ~customScenario();

private:
    Ui::customScenario *ui;
};

#endif // CUSTOMSCENARIO_H
