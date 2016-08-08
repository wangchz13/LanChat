#-------------------------------------------------
#
# Project created by QtCreator 2016-05-09T21:45:52
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cxx\
    protocol.cxx \
    sendmessage.cxx \
    receivemessage.cxx \
    messagebutton.cxx \
    mainform.cxx \
    chatform.cxx \
    databaseconnector.cxx \
    basebutton.cxx \
    contactmsgbutton.cxx \
    groupmsgbutton.cxx \
    contactbutton.cxx \
    groupbutton.cxx \
    contact.cxx \
    group.cxx \
    baseprofile.cxx \
    contactprofile.cxx \
    groupprofile.cxx \
    profilebutton.cxx

HEADERS  += \
    protocol.h \
    sendmessage.h \
    receivemessage.h \
    messagebutton.h \
    mainform.h \
    chatform.h \
    databaseconnector.h \
    global.h \
    basebutton.h \
    contactmsgbutton.h \
    groupmsgbutton.h \
    contactbutton.h \
    groupbutton.h \
    contact.h \
    group.h \
    baseprofile.h \
    contactprofile.h \
    groupprofile.h \
    profilebutton.h

FORMS += \
    mainform.ui \
    chatform.ui

RESOURCES += \
    src.qrc

SUBDIRS += \
    ../../Button/Button.pro
