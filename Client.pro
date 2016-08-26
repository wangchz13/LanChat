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
    databaseconnector.cxx \
    Button/basebutton.cxx \
    Button/contactbutton.cxx \
    Button/contactmsgbutton.cxx \
    Button/groupbutton.cxx \
    Button/groupmsgbutton.cxx \
    Button/messagebutton.cxx \
    Button/profilebutton.cxx \
    Form/chatform.cxx \
    Form/mainform.cxx \
    Profile/baseprofile.cxx \
    Profile/contactprofile.cxx \
    Profile/groupprofile.cxx \
    Network/filereceiver.cxx \
    Network/filesender.cxx \
    Network/messagereceiver.cxx \
    Network/messagesender.cxx \
    Widget/filewidget.cxx \
    facetableview.cxx \
    msgtextedit.cxx

HEADERS  += \
    protocol.h \
    databaseconnector.h \
    global.h \
    Button/basebutton.h \
    Button/contactbutton.h \
    Button/contactmsgbutton.h \
    Button/groupbutton.h \
    Button/groupmsgbutton.h \
    Button/messagebutton.h \
    Button/profilebutton.h \
    Form/chatform.h \
    Form/mainform.h \
    Profile/baseprofile.h \
    Profile/contactprofile.h \
    Profile/groupprofile.h \
    Network/filereceiver.h \
    Network/filesender.h \
    Network/messagereceiver.h \
    Network/messagesender.h \
    Widget/filewidget.h \
    facetableview.h \
    msgtextedit.h

FORMS += \
    mainform.ui \
    chatform.ui

RESOURCES += \
    src.qrc

SUBDIRS += \
    ../../Button/Button.pro

DISTFILES += \
    .gitattributes \
    .gitignore \
    README.md \
    Button/1.txt
