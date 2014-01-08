#-------------------------------------------------
#
# Project created by QtCreator 2013-11-15T19:56:10
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DOTC_Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        QDOTCSocket.cpp \
    addoffer.cpp \
    addchannel.cpp \
    dotcsettings.cpp \
    settingsdialog.cpp

HEADERS  += mainwindow.h \
            QDOTCSocket.h \
    addoffer.h \
    addchannel.h \
    dotcsettings.h \
    settingsdialog.h


FORMS    += mainwindow.ui \
    addoffer.ui \
    addchannel.ui \
    settingsdialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../qjsonrpc/src/release/ -lqjsonrpc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../qjsonrpc/src/debug/ -lqjsonrpc
else:unix: LIBS += -L$$OUT_PWD/../qjsonrpc/src/ -lqjsonrpc

INCLUDEPATH += $$PWD/../qjsonrpc/src
DEPENDPATH += $$PWD/../qjsonrpc/src

RESOURCES += \
    res.qrc
