#include "portSettings.h"
#include "ui_portSettings.h"

portSettings::portSettings(const  QStringList &avPorts,const QList<int> avBaudRates, const QString &port , int &baudRate , QWidget *parent /*= 0*/) :
    QDialog(parent),
    ui(new Ui::portSettings),
    m_port(port),
    m_baudRate(baudRate)
{
    ui->setupUi(this);
    ui->cbxPort->addItems(avPorts);
    foreach(int baudRate, avBaudRates)
        ui->cbxBaud->addItem(QString::number(baudRate));

    int indexPort = ui->cbxPort->findText(m_port);
    if (indexPort != -1)
        ui->cbxPort->setCurrentIndex(indexPort);

    int indexBaudrate = ui->cbxPort->findText(QString::number(m_baudRate));
    if (indexBaudrate != -1)
        ui->cbxBaud->setCurrentIndex(indexBaudrate);

}

portSettings::~portSettings()
{
    delete ui;
}



void portSettings::on_cbxPort_currentIndexChanged(const QString currentPort)
{
    m_port = currentPort;
}

void portSettings::on_cbxBaud_currentIndexChanged(const QString currentBaudRate)
{
    m_baudRate= currentBaudRate.toInt();
}

QString portSettings::getPort()
{
    return m_port;
}

int portSettings::getBaudRate()
{
    return m_baudRate;
}

