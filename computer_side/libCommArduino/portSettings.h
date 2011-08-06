#ifndef PORTSETTINGS_H
#define PORTSETTINGS_H

#include <QDialog>


namespace Ui {
    class portSettings;
}

class portSettings : public QDialog
{
    Q_OBJECT

public:
    explicit portSettings( const QStringList &avPorts, const QList<int> avBaudRates,const QString &port, int &baudrate, QWidget *parent = 0);
    ~portSettings();
    QString getPort();
    int getBaudRate();

private:
    Ui::portSettings *ui;
    QString m_port;
    int m_baudRate;

private slots:
    void on_cbxBaud_currentIndexChanged(QString );
    void on_cbxPort_currentIndexChanged(QString );
};

#endif // PORTSETTINGS_H
