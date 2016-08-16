#include "mainpanel.h"

#include <QApplication>
#include <QFile>
#include <QTextCodec>
#include <QDebug>
#include <QImage>
#include "protocol.h"
#include "global.h"
#include "receivemessage.h"
#include "sendmessage.h"

#include "mainform.h"
#include "chatform.h"
#include <QDebug>

int currentOnline;
QString myUserName;
QString myComputerName;
QString myIpAddress;
QImage defaultHead;
QImage contactHead;
QImage groupHead;
QPixmap *head;
QVector<ChatForm*> currentChatVec;
void initGlobalEnvironment(){
    currentOnline = 0;
    myUserName = getUserName();
    myComputerName = getComputerName();
    myIpAddress = getIp();
    head = new QPixmap(":/source/head.png");
    defaultHead = QImage(":/source/g40.png");
    contactHead = QImage(":/source/g40.png");
    groupHead = QImage(":/source/g40.png");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QFile qss(":/qss/stylesheet.qss");
    qss.open(QFile::ReadOnly);
    QString s(qss.readAll());
    a.setStyleSheet(s);
    qss.close();

    initGlobalEnvironment();
    MainForm *mainForm = new MainForm;
    mainForm->show();

    MessageReceiver *rcv = new MessageReceiver;
    rcv->listen();

    M_Login login(myUserName, myComputerName,myIpAddress);
    MessageSender sender(login);
    sender.send();


    QObject::connect(rcv,SIGNAL(newBuddy(M_Login)),mainForm,SLOT(newBuddySlot(M_Login)));
    QObject::connect(rcv,SIGNAL(newMessage(M_Message)),mainForm,SLOT(newMessageSlot(M_Message)));
    return a.exec();
}
