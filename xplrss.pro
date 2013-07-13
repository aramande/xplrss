#-------------------------------------------------
#
# Project created by QtCreator 2013-02-03T14:35:42
#
#-------------------------------------------------

QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = xplrss
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
        xplrss.cpp \
    feedtree.cpp \
    htmldelegate.cpp \
    rssmodel.cpp \
    rssitem.cpp \
    util.cpp \
    addfeedwidget.cpp \
    feed.cpp \
    branch.cpp \
    feedtreeview.cpp \
    feedlistview.cpp \
    sorter.cpp \
    #compoundmodelscrapped.cpp
    #mergedmodel.cpp \
    feedlistitemmodel.cpp

HEADERS  += xplrss.h \
    feedtree.h \
    htmldelegate.h \
    rssmodel.h \
    rssitem.h \
    util.h \
    addfeedwidget.h \
    feed.h \
    branch.h \
    feedtreeview.h \
    feedlistview.h \
    sorter.h \
    feedlistitemmodel.h \
    #compoundmodelscrapped.h
    #mergedmodel.h

FORMS += xplrss.ui

OTHER_FILES += \
    tree.txt \
    README.md
