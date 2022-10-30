TEMPLATE = subdirs

SUBDIRS += \
        CourseLib \
        Game \
    Score_Test \
    Statistics_Test



CourseLib.subdir = Course/CourseLib
Game.depends = CourseLib
