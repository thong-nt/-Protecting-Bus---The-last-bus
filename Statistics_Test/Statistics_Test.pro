QT += testlib
QT -= gui
TARGET = tst_statistics_test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += tst_statistics_test.cpp \
    ../Game/statistics.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../Game/statistics.hh

INCLUDEPATH += \
           ../Game/
DEPENDPATH  += \
           ../Game/
