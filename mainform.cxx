#include "mainform.h"
#include "ui_mainform.h"
#include "messagebutton.h"
#include "databaseconnector.h"
#include "contactprofile.h"
#include "contactmsgbutton.h"
#include "sendmessage.h"
#include "protocol.h"

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
    if(_contactMsgVec.isEmpty()){
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

void MainForm::newContact(QString userName, QString computerName, QString ipAddress, QPixmap *head)
{
    ContactProfile c(userName + "[" + computerName + "]",ipAddress, ipAddress);
    ContactButton *button = new ContactButton(c);
    _contactVec.insert(0,button);
    _contactLayout->insertWidget(0,_contactVec[0]);
}

void MainForm::newGroup()
{

}

void MainForm::newBuddySlot(M_Login login)
{
    ContactButton *cb = new ContactButton(ContactProfile(login._userName,login._ipAddress,login._ipAddress));
    for(int i = 0; i < _contactVec.size(); i++){
        if(*_contactVec[i] == *cb){
            delete cb;
            return;
        }
    }

    qDebug() << "new user coming!";
    currentOnline++;
    ui->onlineLabel->setText(tr("当前在线：%1 人").arg(QString::number(currentOnline)));
//    newContact(login._userName,login._computerName,login._ipAddress);
    _contactVec.push_front(cb);
    _contactLayout->insertWidget(0,_contactVec[0]);
    if(myIpAddress == login._ipAddress)
        return;
    M_Login my(myUserName, myComputerName,myIpAddress);
    MessageSender sender(my);
    sender.send(QHostAddress(login._ipAddress));
}

void MainForm::newMessageSlot(M_Message msg)
{
    ui->msgHintLabel->hide();
    if(msg._type == ProfileType::contact){
        ContactMsgButton *cmb = new ContactMsgButton(msg);
        bool flag = false;
        for(int i = 0; i < _contactMsgVec.size(); i++){
            if(*_contactMsgVec[i] == *cmb){//有此消息
                _contactMsgVec.move(i, 0);
                _contactMsgVec[0]->_data = cmb->_data;
                _msgLayout->removeWidget(_contactMsgVec[0]);
                delete cmb;
                cmb = _contactMsgVec[i];
                flag = true;
                break;
            }
        }
        if(!flag){
            _contactMsgVec.insert(0, cmb);
        }
        _msgLayout->insertWidget(0, cmb);
        cmb->refresh();
        ChatForm *cf = new ChatForm(cmb->_profile->_name,cmb->_profile->_data,cmb->_profile->_head, ProfileType::contact);
        flag = false;
        for(int i = 0; i < currentChatVec.size(); ++i){
            if(*currentChatVec[i] == *cf){
                delete cf;
                cf = currentChatVec[i];
                flag = true;
                break;
            }
        }
        if(!flag){
            currentChatVec.push_back(cf);
        }
        cf->newMessageComing(msg);
    }else if(msg._type == ProfileType::group){

    }
}

void MainForm::clearAllMsg()
{
    while(_contactMsgVec.size()){
        _msgLayout->removeWidget(_contactMsgVec.first());
        _contactMsgVec.removeFirst();
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
