#include "LibCommArduino.h"

LibCommArduino::LibCommArduino(QObject *parent /*= 0*/, const QString & port /*= 0*/, int baudRate /*=0*/):
        QThread(parent),
        m_port(port),
        m_intBaudRate(baudRate),
        settings(0)
{
    setBaudRatesMap();
    initConnection();
}
void LibCommArduino::setBaudRatesMap()
{
#ifdef Q_OS_UNIX
    IntToBaud.insert(50, BAUD50);                //POSIX ONLY
    IntToBaud.insert(75, BAUD75);                //POSIX ONLY
#endif

    IntToBaud.insert(110, BAUD110);

#ifdef Q_OS_UNIX
    IntToBaud.insert(134, BAUD134);               //POSIX ONLY
    IntToBaud.insert(150, BAUD150);               //POSIX ONLY
    IntToBaud.insert(200, BAUD200);               //POSIX ONLY
#endif

    IntToBaud.insert(300, BAUD300);
    IntToBaud.insert(600, BAUD600);
    IntToBaud.insert(1200, BAUD1200);

#ifdef Q_OS_UNIX
    IntToBaud.insert(1800, BAUD1800);              //POSIX ONLY
#endif

    IntToBaud.insert(2400, BAUD2400);
    IntToBaud.insert(4800, BAUD4800);
    IntToBaud.insert(9600, BAUD9600);

#ifdef Q_OS_WIN
    IntToBaud.insert(14400, BAUD14400);             //WINDOWS ONLY
#endif

    IntToBaud.insert(19200, BAUD19200);
    IntToBaud.insert(38400, BAUD38400);

#ifdef Q_OS_WIN
    IntToBaud.insert(56000, BAUD56000);             //WINDOWS ONLY
#endif

    IntToBaud.insert(57600, BAUD57600);

#ifdef Q_OS_UNIX
    IntToBaud.insert(76800, BAUD76800);             //POSIX ONLY
#endif

    IntToBaud.insert(115200, BAUD115200);

#ifdef Q_OS_WIN
    IntToBaud.insert(128000, BAUD128000);            //WINDOWS ONLY
    IntToBaud.insert(256000, BAUD256000 );            //WINDOWS ONLY
#endif

}

void LibCommArduino::initConnection()
{
    if (m_port == 0 || m_intBaudRate == 0)
        askForSettings();

    serialPort = new QextSerialPort(m_port);

    serialPort->setBaudRate(IntToBaud.value(m_intBaudRate));
    serialPort->setFlowControl(FLOW_OFF);
    serialPort->setParity(PAR_NONE);
    serialPort->setDataBits(DATA_8);
    serialPort->setStopBits(STOP_1);
    serialPort->setTimeout(500);
    serialPort->open(QIODevice::ReadWrite);
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(readyRead()));

    recievedData.clear();

}

void LibCommArduino::askForSettings()
{

    QStringList availablePorts;
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    foreach( QextPortInfo port, ports )
        availablePorts.append(port.physName);

    settings = new portSettings(availablePorts, IntToBaud.keys(), m_port, m_intBaudRate);
    connect (settings, SIGNAL(accepted()), this , SLOT(settingsDialogAccepted()));
    connect (settings, SIGNAL(rejected()), this , SLOT(settingsDialosRejected()));
    settings->show();
}
void LibCommArduino::settingsDialogAccepted()
{
   m_port =  settings->getPort();
   m_intBaudRate = settings->getBaudRate();
   initConnection();
}

void LibCommArduino::settingsDialosRejected()
{

}

LibCommArduino::~LibCommArduino()
{
    serialPort->close();
}

void LibCommArduino::run()
{

}

void LibCommArduino::readyRead()
{
    int avBytes = serialPort->bytesAvailable();
    recievedData += QString(serialPort->read(avBytes));
    if (recievedData.endsWith(QString("\n")))
    {
        emit lineAvailable(recievedData);
        recievedData.clear();
    }
}

void LibCommArduino::sendData(const QString & strDataToWrite)
{
    serialPort->write(strDataToWrite.toAscii());
}

bool LibCommArduino::isOpen()
{
    return serialPort->isOpen();
}

void LibCommArduino::reConnect( bool keepSettings /*= true*/, const QString & port /*= 0*/, int baudRate /*= 0*/)
{
    if (!keepSettings)
    {
        m_port = port;
        m_intBaudRate = baudRate ;
    }
    if (serialPort->isOpen())
        serialPort->close();
    initConnection();
}

QString LibCommArduino::port()
{
    return m_port;
}

int LibCommArduino::baudRate()
{
    return m_intBaudRate;
}

void LibCommArduino::close()
{
    serialPort->close();
}
