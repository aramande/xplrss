#-------------------------------------------------
#
# Project created by QtCreator 2013-02-03T14:35:42
#
#-------------------------------------------------

QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = xplrss
TEMPLATE = app


SOURCES += main.cpp\
        xplrss.cpp \
    feedtree.cpp \
    htmldelegate.cpp \
    rssmodel.cpp \
    rssitem.cpp \
    util.cpp \
    addfeedwidget.cpp

HEADERS  += xplrss.h \
    feedtree.h \
    htmldelegate.h \
    rssmodel.h \
    rssitem.h \
    util.h \
    addfeedwidget.h

FORMS    += xplrss.ui

OTHER_FILES += \
    tree.txt

RESOURCES += \
    res.qrc
