#-------------------------------------------------
#
# Project created by QtCreator 2012-01-02T22:18:10
#
#-------------------------------------------------
QT      += core gui widgets
CONFIG  += c++17

TARGET = pmkemu
TEMPLATE = app


SOURCES += \
    main.cpp\
    mainwindow.cpp \
    cmcu13.cpp \
    cmem.cpp \
    cdebugdlg.cpp \
    cvaluedlg.cpp \
    emulator.cpp

HEADERS += \
    mainwindow.h \
    cmcu13.h \
    cmem.h \
    ucommands.h \
    cdebugdlg.h \
    synchro.h \
    mcommands.h \
    cvaluedlg.h \
    emulator.h

FORMS   += \
    mainwindow.ui \
    cdebugdlg.ui \
    cvaluedlg.ui

RESOURCES += \
    rsrc.qrc
