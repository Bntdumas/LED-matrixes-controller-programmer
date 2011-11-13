#-------------------------------------------------
#
# Project created by QtCreator 2011-05-01T21:07:26
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = threadLed
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../libCommArduino/

LIBS += ../libCommArduino/libCommArduino.so \
../libCommArduino/qextserialport/src/build/libqextserialport.so

SOURCES += main.cpp \
    threadLedCube.cpp \
    LedsSimulator.cpp \
    scenarioCreator.cpp \
    fileInterface.cpp \
    ledCube.cpp \
    cubeConfiguration.cpp \
    scenarioController.cpp \
    ./predefinedScenarios/abstractPredefinedScenario.cpp \
    ./predefinedScenarios/scenarioMovingCubes.cpp \
    ./predefinedScenarios/scenarioWaves.cpp \
    ./predefinedScenarios/scenarioMovingSquareRandSuspended.cpp \
    coordinates_functions.cpp \
    customScenario.cpp \
    arduinoLedSerial.cpp \
    predefinedScenarios/scenarioRandom.cpp

HEADERS += \
    threadLedCube.h \
    LedsSimulator.h \
    scenarioCreator.h \
    fileInterface.h \
    ledCube.h \
    cubeConfiguration.h \
    scenarioController.h \
    ./predefinedScenarios/abstractPredefinedScenario.h \
    ./predefinedScenarios/scenarioMovingCubes.h \
    ./predefinedScenarios/scenarioWaves.h \
    ./predefinedScenarios/scenarioMovingSquareRandSuspended.h \
    coordinates_functions.h \
    customScenario.h \
    arduinoLedSerial.h \
    predefinedScenarios/scenarioRandom.h

FORMS += \
    scenarioCreator.ui \
    ledCube.ui \
    cubeConfiguration.ui \
    scenarioController.ui \
    customScenario.ui
