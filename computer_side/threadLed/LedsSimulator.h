#ifndef LedsSimulator_H
#define LedsSimulator_H

#include <QGLWidget>

class LedsSimulator : public QGLWidget
{
    Q_OBJECT

public:
    LedsSimulator(QWidget *parent = 0, int cubeX = 8, int cubeY = 8, int cubeZ = 1, int spacing = 5);

    void setCubeMatrix(int newCubeMatrix[3]);
    void setXLeds(int leds);
    void setYLeds(int leds);
    void setZLeds(int leds);
    void setLed(int ledNb, QColor color);
    void setLed(int ledCoor[3], QColor color);
    void setLed(int ledX, int ledY,int ledZ, QColor color);

    void setSpacing(int spacing);
    void setZoom(int zoom);


    QColor getColorForLed(int led);
    QColor getColorForLed(int ledCoor[3]);
    QColor getColorForLed(int ledX, int ledY,int ledZ);

    bool isLedON(int ledX, int ledY,int ledZ);
    bool isLedON(int ledCoor[3]);
    bool isLedON(int led);

    int getSpacing();
    QColor getdefaultColor();

    int getXLeds();
    int getYLeds();
    int getZLeds();
    int getNbLeds();

    int getActualZoom();

    void allOff();
    void razZoom();

    void setMonochromeLeds(bool flag);
    bool hasMonoChromeLeds();

    QColor getMonochromeColor();

    virtual void update();

public slots:
    void setOffColor(QColor);
    void setBackColor(QColor);
    void setMonoChromeColor(QColor);
signals:
    void cubeModified();
    void cubeReDraw();
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    void draw();
    QString coorToString(int coordinates[3]);
    void setCubeValues();

    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    QList<QColor> cubeColor;
    int m_nbCubes;
    int m_cubeMatrix[3];
    GLfloat m_spacing;
    bool m_monoChromeLeds;
    QColor m_monochromeCubeColor;


    QPoint lastPos;
    QMap<QString, int> mapCoordinates;

    GLfloat m_sizeX ;
    GLfloat m_sizeY ;
    GLfloat m_sizeZ ;

    GLfloat m_offsetX ;
    GLfloat m_offsetY ;
    GLfloat m_offsetZ ;

    GLfloat m_zoomZ ;

    QColor m_offColor;
    QColor m_backColor;


};

#endif // LedsSimulator_H
