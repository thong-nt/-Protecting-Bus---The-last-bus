TEMPLATE = app
TARGET = NYSSE

QT += core gui widgets network multimedia

CONFIG += c++14

SOURCES += \
    Graphics/gameplaywindow.cpp \
    Graphics/initialize_dialog.cpp \
    Object_Drawing/alien.cpp \
    Object_Drawing/bullet.cpp \
    Object_Drawing/logic.cpp \
    Object_Drawing/bus.cpp \
    main.cc \
    Graphics/startwindow.cpp \
    Object_Drawing/player.cpp \
    Object_Drawing/score.cpp \
    statistics.cpp \

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

RESOURCES += \
    offlinedata/Data_files.qrc

FORMS += \
    Graphics/gameplaywindow.ui \
    Graphics/initialize_dialog.ui \
    Graphics/startwindow.ui

HEADERS += \
    Graphics/gameplaywindow.hh \
    Graphics/initialize_dialog.hh \
    Graphics/startwindow.hh \
    Object_Drawing/alien.hh \
    Object_Drawing/bullet.hh \
    Object_Drawing/logic.hh \
    Object_Drawing/bus.hh \
    Object_Drawing/player.hh \
    Object_Drawing/score.hh \
    statistics.hh \
