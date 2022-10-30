QT += testlib
QT -= gui
TARGET = tst_statistics_test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += tst_score_test.cpp \
    ../Game/Object_Drawing/score.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../Game/Object_Drawing/score.hh

INCLUDEPATH += \
           ../Game/Object_Drawing/
DEPENDPATH  += \
           ../Game/Object_Drawing/
