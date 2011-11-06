#ifndef ABSTRACTCOMMARDUINO_H
#define ABSTRACTCOMMARDUINO_H

#include <QThread>
#include <QInputDialog>
#include <QMap>
#include "./qextserialport/src/qextserialport.h"
#include "./qextserialport/src/qextserialenumerator.h"

#include "portSettings.h"


class LibCommArduino : public QThread
{
    Q_OBJECT
public:

    enum msgInfoType {
        info,
        valid,
        invalid
    };
    explicit LibCommArduino(QObject *parent = 0, const QString & port = 0, int baudRate = 0);
    ~LibCommArduino();
    virtual void sendData(const QString &);
    bool isOpen();
    void reConnect(bool keepSettings = true, const QString & port = 0, int baudRate = 0);
    QString port();
    int baudRate();
    void close();


protected:
    void run();

signals:
    void serialInfo(const QString&, const msgInfoType);
    void dataReceived(const QVariant&);
    void lineAvailable(const QString &);

public slots:
    void readyRead();
private slots:
    void settingsDialogAccepted();
    void settingsDialosRejected();
protected:
    QextSerialPort *serialPort;
    QString m_port;
    int m_intBaudRate;
    QString recievedData;
    QMap<int, BaudRateType> IntToBaud;
    portSettings *settings;

    void initConnection();
    void askForSettings();
    void setBaudRatesMap();


};

#endif // ABSTRACTCOMMARDUINO_H
