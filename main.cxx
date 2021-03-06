﻿#include <QApplication>
#include <QFile>
#include <QTextCodec>
#include <QDebug>
#include <QImage>
#include <QStyle>
#include <QStyleFactory>

#include "protocol.h"
#include "global.h"
#include "Network/messagereceiver.h"
#include "Network/messagesender.h"
#include "Form/mainform.h"
#include "Form/chatform.h"
#include "facetableview.h"

#include <QDebug>

int currentOnline;
QString myUserName;
QString myComputerName;
QString myIpAddress;
QImage defaultHead;
QImage contactHead;
QImage groupHead;
QPixmap *head;
ContactProfile myProfile;

void initGlobalEnvironment(){
    currentOnline = 0;
    myUserName = getUserName();
    myComputerName = getComputerName();
    myIpAddress = getIp();
    head = new QPixmap(":/source/head.png");
    defaultHead = QImage(":/source/head/contacthead.png");
    contactHead = QImage(":/source/head/contacthead.png");
    contactHead = contactHead.scaled(40,40);
    groupHead = QImage(":/source/head/grouphead.png");
    groupHead = groupHead.scaled(40,40);

    myProfile = ContactProfile(myUserName, myComputerName, myIpAddress);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QFile qss(":/qss/stylesheet.qss");
    qss.open(QFile::ReadOnly);
    QString s(qss.readAll());
    a.setStyleSheet(s);
    qss.close();

    //初始化一些全局量
    initGlobalEnvironment();

    FaceTableView view;
    view.show();


    //主窗体显示
    MainForm *mainForm = new MainForm;
    mainForm->show();

    //开始接受消息
    MessageReceiver *rcv = new MessageReceiver;
    rcv->listen();

    //发送本机登录信息
    M_Login login(myUserName, myComputerName,myIpAddress);
    MessageSender sender(login);
    sender.send();


    QObject::connect(rcv, SIGNAL(newBuddy(M_Login)), mainForm, SLOT(newBuddySlot(M_Login)));
    QObject::connect(rcv, SIGNAL(newMessage(M_Message)), mainForm, SLOT(newMessageSlot(M_Message)));

    QObject::connect(rcv, SIGNAL(fileRequest(M_File)), mainForm, SLOT(fileRequestSlot(M_File)));
    QObject::connect(rcv, SIGNAL(fileRefused(M_File)), mainForm, SLOT(fileRefusedSlot(M_File)));
    QObject::connect(rcv, SIGNAL(fileReceive(M_File)), mainForm, SLOT(fileReceiveSlot(M_File)));
    return a.exec();
}
