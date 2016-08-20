#-------------------------------------------------
#
# Project created by QtCreator 2016-08-20T12:21:25
#
#-------------------------------------------------
DEPTH = ..

include($${DEPTH}/qjsonrpc/qjsonrpc.pri)

INCLUDEPATH += $${QJSONRPC_INCLUDEPATH} \
               $${QJSONRPC_INCLUDEPATH}/json \
               $${PWD}/common

LIBS += -L../build-qjsonrpc-Qt_5_3_1_clang_64-Release/src $${QJSONRPC_LIBS}

QT = core network testlib

CONFIG -= app_bundle
CONFIG += testcase no_testcase_installs

HEADERS += \
    $${PWD}/common/signalspy.h \
    cocoservicemanager.h \
    cocoservice.h \
    usbaspdetector.h

unix:!macx:QMAKE_RPATHDIR += $${OUT_PWD}/$${DEPTH}/src
macx {
    QMAKE_RPATHDIR += @loader_path/$${DEPTH}/src
    QMAKE_LFLAGS += -Wl,-rpath,@loader_path/$${DEPTH}/src
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


QT       += core gui
TARGET = CocoBlockServer
TEMPLATE = app
SOURCES += main.cpp\
        mainwindow.cpp \
    cocoservicemanager.cpp \
    cocoservice.cpp \
    usbaspdetector.cpp
HEADERS  += mainwindow.h
FORMS    += mainwindow.ui

RESOURCES += \
    cocoresource.qrc

DISTFILES += \
    ../../../../Downloads/Cocomakey-packaging--mock-up.png
