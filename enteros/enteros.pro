QT += core
QT -= gui
QT += opengl
CONFIG += c++11
LIBS += -lglut -lGLU
TARGET = enteros
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    matriz.cpp
