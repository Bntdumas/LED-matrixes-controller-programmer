#-------------------------------------------------
#
# Project created by QtCreator 2011-04-15T09:04:10
#
#-------------------------------------------------

QT       += gui

TARGET = CommArduino
TEMPLATE = lib

DEFINES += LIBCOMMARDUINO_LIBRARY

SOURCES += LibCommArduino.cpp \
    portSettings.cpp

HEADERS += LibCommArduino.h\
        libCommArduino_global.h \
    portSettings.h

LIBS += ./qextserialport/src/build/libqextserialport.so

FORMS += \
    portSettings.ui
