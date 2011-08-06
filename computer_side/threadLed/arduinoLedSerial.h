#ifndef ARDUINOLEDSERIAL_H
#define ARDUINOLEDSERIAL_H

#include "LibCommArduino.h"
#include "LedsSimulator.h"
class QTextEdit;
class arduinoLedSerial : public LibCommArduino
{
    Q_OBJECT
public slots:
    void updateCube();
public:
    explicit arduinoLedSerial(LedsSimulator *ledSim,QTextEdit* textEdit,  QObject *parent = 0, const QString & port = 0, int baudRate = 0);
    ~arduinoLedSerial();

public Q_SLOTS:
    void addFailedLogEntry( const QString & logEntry );
    void addOkLogEntry( const QString & logEntry );
    void addInfoLogEntry( const QString & logEntry );
    void addPictureStartLogEntry( const QString & logEntry );
    void addPictureEndLogEntry( const QString & logEntry );
    void addLogEntry( const QString & logEntry, const QColor& color );

    void lineAvailableFromArduino(const QString &);
private:
    LedsSimulator * m_ledSimulator;
    QString m_lastFrame;
    QTextEdit *m_textEdit;
};

#endif // ARDUINOLEDSERIAL_H
