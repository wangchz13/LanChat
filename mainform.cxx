#include "mainform.h"
#include "ui_mainform.h"
#include "messagebutton.h"
#include "databaseconnector.h"
#include "contactprofile.h"
#include "contactmsgbutton.h"

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
    qDebug() << "Heer";
    ui->msgHintLabel->hide();
    if(msg._type == ProfileType::contact){
        ContactMsgButton *cmb = new ContactMsgButton(msg);
        bool flag = true;
        for(int i = 0; i < _contactMsgVec.size(); i++){
            if(*_contactMsgVec[i] == *cmb){//有此消息
                _contactMsgVec.move(i, 0);
                _contactMsgVec[0]->_data = cmb->_data;
                _msgLayout->removeWidget(_contactMsgVec[0]);
                flag = false;
                break;
            }
        }
        if(flag){
            _contactMsgVec.insert(0, cmb);
            qDebug() << "1";
        }
        qDebug() << "2";
        _msgLayout->insertWidget(0,_contactMsgVec[0]);
        qDebug() << "3";
        _contactMsgVec[0]->newMessageComing();
        qDebug() << "4";
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
