#ifndef FILEINTERFACE_H
#define FILEINTERFACE_H

#include <QObject>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QColor>

struct LedState {
    int x ;
    int y ;
    int z ;

    int red ;
    int green ;
    int blue ;
};

class fileInterface : public QObject
{
    Q_OBJECT
public:
    explicit fileInterface(const QString & filename, QObject *parent = 0);
    void startPicture();
    void endPicture(int delay);
    void addLedState(LedState led);
    void writeScenario();
    void readScenario();
    void setCubeData(int x, int y, int z, int spacing, QColor defaultColor);
    QString getCubeData();
    QString getFileName();
    void setFileName(const QString &);


signals:
    void scenarioLoaded(QList< QList<LedState> >, QList<int>, QString &);
    void infoMessage(const QString &);

public slots:

private:   
    void setCubeData(const QString & data, QColor offColor);

    QList<LedState> m_picture;
    QList<int> m_delay;
    QList< QList<LedState> > m_scenario;
    QString m_filename;
    QString m_cubeData;



};

#endif // FILEINTERFACE_H
