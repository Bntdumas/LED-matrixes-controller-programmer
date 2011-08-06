#include <QtGui>
#include <QtOpenGL>
#include "LedsSimulator.h"

LedsSimulator::LedsSimulator(QWidget *parent /*= 0*/, int cubeX, int cubeY, int cubeZ, int spacing /*= 1*/)
    : QGLWidget(parent),  m_spacing(spacing), m_monoChromeLeds(false)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    rotationX = 0.0;
    rotationY = 0.0;
    rotationZ = 0.0;

    m_cubeMatrix[0] = cubeX;
    m_cubeMatrix[1] = cubeY;
    m_cubeMatrix[2] = cubeZ;

    m_spacing+=2;
    m_backColor = Qt::darkGray;
    m_offColor = QColor(220,220,220,40);
   setCubeValues();

}

void LedsSimulator::initializeGL()
{
    qglClearColor(m_backColor);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
}

void LedsSimulator::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width) / height;
    glFrustum(-x, +x, -1.0, +1.0, 4.0, 10000.0);
    glMatrixMode(GL_MODELVIEW);
}

void LedsSimulator::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    draw();
}

void LedsSimulator::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void LedsSimulator::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
    GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();

    if (event->buttons() & Qt::LeftButton) {
        rotationX += 180 * dy;
        rotationY += 180 * dx;
        updateGL();
    } else if (event->buttons() & Qt::RightButton) {
        rotationX += 180 * dy;
        rotationZ += 180 * dx;
        updateGL();
    }
    lastPos = event->pos();
}

void LedsSimulator::setMonochromeLeds(bool flag)
{
    m_monoChromeLeds = flag;
}

bool LedsSimulator::hasMonoChromeLeds()
{
    return m_monoChromeLeds;
}
QColor LedsSimulator::getMonochromeColor()
{
    return m_monochromeCubeColor;
}
void LedsSimulator::setMonoChromeColor(QColor color)
{
   m_monochromeCubeColor = color;
}

void LedsSimulator::setCubeMatrix(int newCubeMatrix[3])
{
    m_cubeMatrix[0] = newCubeMatrix[0];
    m_cubeMatrix[1] = newCubeMatrix[1];
    m_cubeMatrix[2] = newCubeMatrix[2];
    setCubeValues();
}
void LedsSimulator::setXLeds(int leds)
{
    m_cubeMatrix[0] = leds;
    setCubeValues();
}

void LedsSimulator::setYLeds(int leds)
{
    m_cubeMatrix[1] = leds;
    setCubeValues();

}

void LedsSimulator::setZLeds(int leds)
{
    m_cubeMatrix[2] = leds;
    setCubeValues();

}

void LedsSimulator::setLed(int led, QColor color)
{
    if (led >= 0 && led <= m_nbCubes)
    {
        if (color.isValid())
        {
            if(!m_monoChromeLeds)
                cubeColor[led] = color;
            else
                cubeColor[led] = m_monochromeCubeColor;

            emit cubeModified();
            return;
        }
        cubeColor[led] = m_offColor;
        emit cubeModified();
    }
}
void LedsSimulator::setLed(int ledCoor[3], QColor color)
{
    QString coordStr = coorToString(ledCoor);
    int ledNb = mapCoordinates.value(coordStr);
    setLed(ledNb, color);
}

void LedsSimulator::setLed(int ledX, int ledY,int ledZ, QColor color)
{
    int ledCoor[3] ;
    ledCoor[0] = ledX;
    ledCoor[1] = ledY;
    ledCoor[2] = ledZ;
    setLed(ledCoor, color);
}

QString LedsSimulator::coorToString(int coordinates[3])
{
    QString x = QString::number(coordinates[0]);
    QString y = QString::number(coordinates[1]);
    QString z = QString::number(coordinates[2]);

    return QString(x + "," + y + "," + z);

}
void LedsSimulator::setSpacing(int spacing)
{
    m_spacing = spacing;
    m_spacing+=2;
    setCubeValues();
}

int LedsSimulator::getSpacing()
{
    return m_spacing-2;
}

int LedsSimulator::getNbLeds()
{
    return m_nbCubes;
}
QColor LedsSimulator::getColorForLed(int led)
{
    if (led >= 0 && led <= m_nbCubes)
        return  cubeColor[led];
    else return QColor();
}

QColor LedsSimulator::getColorForLed(int ledCoor[3])
{
    QString coordStr = coorToString(ledCoor);
    int ledNb = mapCoordinates.value(coordStr);
    return getColorForLed(ledNb);
}

QColor LedsSimulator::getColorForLed(int ledX, int ledY,int ledZ)
{
    int ledCoor[3] ;
    ledCoor[0] = ledX;
    ledCoor[1] = ledY;
    ledCoor[2] = ledZ;
    return getColorForLed(ledCoor);
}
bool LedsSimulator::isLedON(int ledX, int ledY,int ledZ)
{
    if (getColorForLed(ledX, ledY,ledZ) == m_offColor)
        return false;
    else return true;
}

bool LedsSimulator::isLedON(int ledCoor[3])
{
    if (getColorForLed(ledCoor) == m_offColor)
        return false;
    else return true;
}

bool LedsSimulator::isLedON(int led)
{
    if (getColorForLed(led) == m_offColor)
        return false;
    else return true;
}


int LedsSimulator::getXLeds()
{
    return m_cubeMatrix[0];
}

int LedsSimulator::getYLeds()
{
    return m_cubeMatrix[1];
}
int LedsSimulator::getZLeds()
{
    return m_cubeMatrix[2];
}

int LedsSimulator::getActualZoom()
{
    return m_zoomZ;
}

void LedsSimulator::setOffColor(QColor color)
{
    m_offColor = color;
    allOff();
    updateGL();
}
void LedsSimulator::setBackColor(QColor color)
{
    qglClearColor(color);
    updateGL();
}

QColor LedsSimulator::getdefaultColor()
{
    return m_offColor;
}

void LedsSimulator::allOff()
{
    for (int i = 0; i < m_nbCubes; i++)
        cubeColor[i] = m_offColor;
}
void LedsSimulator::razZoom()
{
    m_zoomZ = 4*(m_cubeMatrix[0]*(2 + m_spacing));
    updateGL();
}

void LedsSimulator::setZoom(int zoom)
{
    m_zoomZ = zoom;
    updateGL();
}

void LedsSimulator::setCubeValues()
{
    int realSpacing = m_spacing-2;
    m_sizeX = (m_cubeMatrix[0]*(2 + realSpacing))-realSpacing;
    m_sizeY = (m_cubeMatrix[1]*(2 + realSpacing))-realSpacing;
    m_sizeZ = (m_cubeMatrix[2]*(2 + realSpacing))-realSpacing;

    m_offsetX = (m_sizeX/2)-1;
    m_offsetY = (m_sizeY/2)-1;
    m_offsetZ = (m_sizeZ/2)-1;

    m_zoomZ = 4*(m_cubeMatrix[0]*(2 + m_spacing));

    int idLed = 0;
    mapCoordinates.clear();
    for (int f = 0; f < m_cubeMatrix[2] ; f++)//Bigcube
        for (int g = 0; g < m_cubeMatrix[1] ; g++)//plane
            for (int h = 0; h < m_cubeMatrix[0] ; h++)
            {
                int cubeCoord[3] = {h, g, f};
                QString cubeStrCoor = coorToString(cubeCoord);
                mapCoordinates.insert(cubeStrCoor, idLed++);
            }
    m_nbCubes = m_cubeMatrix[0] * m_cubeMatrix[1] * m_cubeMatrix[2];
    cubeColor.clear();
    for (int i = 0; i < m_nbCubes; i++)
        cubeColor.append(m_offColor);
    updateGL();
    emit cubeModified();
}
void LedsSimulator::update()
{
    emit cubeReDraw();
    QWidget::update();
}

void LedsSimulator::draw()
{
    static const GLfloat P0[3] = { 1.0f, 1.0f, 1.0f };
    static const GLfloat P1[3] = { 1.0f, 1.0f, -1.0f };
    static const GLfloat P2[3] = { 1.0f, -1.0f, 1.0f };
    static const GLfloat P3[3] = { 1.0f, -1.0f, -1.0f };

    static const GLfloat P4[3] = { -1.0f, 1.0f, 1.0f };
    static const GLfloat P5[3] = { -1.0f, 1.0f, -1.0f };
    static const GLfloat P6[3] = { -1.0f, -1.0f, 1.0f };
    static const GLfloat P7[3] = { -1.0f, -1.0f, -1.0f };

    static const GLfloat * const coords[6][4] = {
        { P5, P1, P3, P7 }, { P0, P4, P6, P2 }, { P1, P0, P2, P3  },
        { P4, P5, P7, P6 }, { P1, P5, P4, P0 }, { P2, P6, P7, P3  }
    };

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -m_zoomZ);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotationZ, 0.0f, 0.0f, 1.0f);

    int idLed=0;
    glTranslatef(0.0f,0.0f, -m_offsetZ);
    for (int f = 0; f < m_cubeMatrix[2] ; f++)//Bigcube
    {
        glTranslatef(0.0f,-m_offsetY, 0.0f);
        for (int g = 0; g < m_cubeMatrix[1] ; g++)//plane
        {
            glTranslatef(-m_offsetX,0.0f, 0.0f); // cubes on x - line
            for (int h = 0; h < m_cubeMatrix[0] ; h++)
            {
                glLoadName(idLed);
                qglColor(cubeColor[idLed]);
                for (int i = 0; i < 6; ++i) {
                    glBegin(GL_QUADS);
                    for (int j = 0; j < 4; ++j)
                        glVertex3f(coords[i][j][0], coords[i][j][1],coords[i][j][2]);
                    glEnd();
                }
                if (h != (m_cubeMatrix[0]-1))
                    glTranslatef(m_spacing, 0.0f, 0.0f);
                idLed++;
            }
            if (g != (m_cubeMatrix[1]-1))
                glTranslatef(-m_offsetX,m_spacing, 0.0f);
        }
        if (f != (m_cubeMatrix[2]-1))
            glTranslatef(-m_offsetX,-m_offsetY, m_spacing);
    }
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -m_zoomZ);
}



