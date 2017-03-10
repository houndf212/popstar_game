#-------------------------------------------------
#
# Project created by QtCreator 2017-03-09T16:53:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = popstar_game
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    graphicsview.cpp \
    matrix.cpp \
    pos.cpp \
    matrixgame.cpp \
    matrixgenerator.cpp \
    matrixslice.cpp \
    scorecalc.cpp \
    graphicmatrix.cpp \
    staritem.cpp \
    starboard.cpp \
    flagval.cpp

HEADERS  += \
    graphicsview.h \
    basic_matrix.h \
    basic_pos.h \
    matrix.h \
    pos.h \
    matrixgame.h \
    matrixgenerator.h \
    matrixslice.h \
    scorecalc.h \
    graphicmatrix.h \
    staritem.h \
    starboard.h \
    flagval.h
