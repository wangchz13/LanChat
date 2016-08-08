﻿#include "mainform.h"
#include "ui_mainform.h"
#include "messagebutton.h"
#include "databaseconnector.h"

#include <QDateTime>
#include <QScrollBar>
#include <QLayout>

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->msg_Page);
    initMsgVector();
    initContactVector();

    initMsgPage();
    initContactPage();
    initBottomWidget();
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::initMsgVector()
{
    DatabaseConnector dc;
}

void MainForm::initContactVector()
{
    DatabaseConnector dc;
}

void MainForm::initMsgPage()
{
    _msgLayout = new QVBoxLayout;
    _msgLayout->setSpacing(0);
    ui->msgHintLabel->hide();
    if(_msgVector.isEmpty()){
        ui->msgHintLabel->show();
    }
    _msgLayout->addStretch();
    ui->scrollAreaWidgetContents->setLayout(_msgLayout);

//    ui->msg_Page->setContextMenuPolicy(Qt::ActionsContextMenu);
//    QAction *clearAll = new QAction(tr("清空会话列表"), ui->msg_Page);
//    connect(clearAll, SIGNAL(triggered(bool)),this,SLOT(clearAllMsg()));
//    ui->msg_Page->addAction(clearAll);//应该放在setmenu里实现
}

void MainForm::initContactPage()
{
    _contactLayout = new QVBoxLayout;
    _contactLayout->setSpacing(0);
    _contactLayout->addStretch();
    ui->scrollAreaWidgetContents_2->setLayout(_contactLayout);
}

void MainForm::initBottomWidget()
{
    ui->onlineLabel->setText(tr("当前在线：%1人").arg(QString::number(currentOnline)));
}

void MainForm::newMessage(QString title, QString data, QString time, QPixmap *head)
{
    ui->msgHintLabel->hide();
    MessageButton *msgButton = new MessageButton(title, data, time);
    bool flag = true;
    for(int i = 0; i < _msgVector.size(); i++){
        if(*_msgVector[i] == *msgButton){//有此消息
            _msgVector.move(i, 0);
            _msgVector[0]->_data = msgButton->_data;
            _msgLayout->removeWidget(_msgVector[0]);
            flag = false;
            break;
        }
    }
    if(flag){
        _msgVector.insert(0, msgButton);
    }
    _msgLayout->insertWidget(0,_msgVector[0]);
    _msgVector[0]->newMessageComing();
}

void MainForm::newContact(QString userName, QString computerName, QString ipAddress, QPixmap *head)
{
    Contact c(userName + "[" + computerName + "]",ipAddress);
    ContactButton *button = new ContactButton(c);
    _contactVector.insert(0,button);
    _contactLayout->insertWidget(0,_contactVector[0]);
}

void MainForm::newGroup()
{

}

void MainForm::newBuddySlot(M_Login login)
{
    qDebug() << "new user coming!";
    currentOnline++;
    ui->onlineLabel->setText(tr("当前在线：%1 人").arg(QString::number(currentOnline)));
    newContact(login._userName,login._computerName,login._ipAddress);
}

void MainForm::newMessageSlot(M_Message msg)
{
    newMessage(msg._userName,msg._content,QTime::currentTime().toString());
}

void MainForm::clearAllMsg()
{
    while(_msgVector.size()){
        _msgLayout->removeWidget(_msgVector.first());
        _msgVector.removeFirst();
    }
}

void MainForm::on_msgPushButton_toggled(bool checked)
{
    if(checked)
        ui->stackedWidget->setCurrentWidget(ui->msg_Page);
}

void MainForm::on_contactPushButton_toggled(bool checked)
{
    if(checked)
        ui->stackedWidget->setCurrentWidget(ui->contact_Page);
}

void MainForm::on_settingPushButton_toggled(bool checked)
{

}
