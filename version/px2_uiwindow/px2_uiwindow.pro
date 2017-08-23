#-------------------------------------------------
#
# Project created by QtCreator 2017-06-11T21:54:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = px2_uiwindow
TEMPLATE = lib

LIBS += -L /home/nvidia/px2_uiwindow/qt_lib/json -ljsoncpp



SOURCES += main.cpp\
        mainwindow.cpp \
    data_agent.cpp

HEADERS  += mainwindow.h \
    ui_commtype.h \
    data_agent.h \
    qt_lib/json/include/allocator.h \
    qt_lib/json/include/assertions.h \
    qt_lib/json/include/autolink.h \
    qt_lib/json/include/config.h \
    qt_lib/json/include/features.h \
    qt_lib/json/include/forwards.h \
    qt_lib/json/include/json.h \
    qt_lib/json/include/reader.h \
    qt_lib/json/include/value.h \
    qt_lib/json/include/version.h \
    qt_lib/json/include/writer.h

FORMS    += mainwindow.ui


INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
