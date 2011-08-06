#include "arduinoLedSerial.h"
#include <QDebug>
#include <QPlainTextEdit>
#include <QDateTime>

arduinoLedSerial::arduinoLedSerial(LedsSimulator *ledSim, QTextEdit *textEdit, QObject *parent /*= 0*/, const QString & port /*= 0*/, int baudRate /*= 0*/) :
    LibCommArduino(parent, port, baudRate),
    m_ledSimulator(ledSim),
    m_textEdit(textEdit),
    m_lastFrame(QString())
{
    connect (this, SIGNAL(lineAvailable(QString)), this, SLOT(lineAvailableFromArduino(QString)));
}

arduinoLedSerial::~arduinoLedSerial()
{

}

void arduinoLedSerial::addInfoLogEntry( const QString & logEntry )
{
    addLogEntry( logEntry,QColor( Qt::darkGray) );
}

void arduinoLedSerial::addFailedLogEntry( const QString & logEntry )
{
    addLogEntry( logEntry,QColor( Qt::darkRed ) );
}

void arduinoLedSerial::addOkLogEntry( const QString & logEntry )
{
    addLogEntry( logEntry, QColor( Qt::darkGreen ) );
}

void arduinoLedSerial::addPictureStartLogEntry( const QString & logEntry )
{
    addLogEntry( logEntry, QColor( Qt::darkBlue ) );
}

void arduinoLedSerial::addPictureEndLogEntry( const QString & logEntry )
{
    addLogEntry( logEntry, QColor( Qt::darkCyan ) );
}

void arduinoLedSerial::addLogEntry( const QString & logEntry, const QColor& color )
{
    m_textEdit->setTextColor( color );
    const QString formatLogEntry = QString::fromLatin1( "<b> [%1] %2 </b>" ).arg(QTime::currentTime().toString()).arg( logEntry );
    m_textEdit->append( formatLogEntry );
    m_textEdit->repaint();
}

void arduinoLedSerial::lineAvailableFromArduino(const QString & line)
{
    QStringList frame = line.split(",");
    if (frame.count() >= 2)
    {
        switch(frame.at(0).toInt())
        {
        case 0:
            addFailedLogEntry(frame.at(1));
            break;

        case 1:
            addInfoLogEntry(frame.at(1));
            break;

        case 2:
            addInfoLogEntry(frame.at(1));
            break;

        case 3:
            addInfoLogEntry(frame.at(1));
            break;

        case 4:
            addPictureStartLogEntry(frame.at(1));
            break;

        case 5:
            addOkLogEntry(frame.at(1));
            break;

        case 6:
            addPictureEndLogEntry(frame.at(1));
            break;

        default:

            break;
        }

        recievedData.clear();
    }
}
void arduinoLedSerial::updateCube()
{
    QString frame = "4;";
    for (int i = 0; i < 8; i++)
        for (int j = 0; j< 8; j++)
            if(m_ledSimulator->isLedON(i, j, 0))
                frame += tr("5,%1,%2;").arg(QString::number(i)).arg(QString::number(j));
    frame+="6;\n";
    if (frame == m_lastFrame)
        return;
    m_lastFrame = frame;
    sendData(frame);
}
