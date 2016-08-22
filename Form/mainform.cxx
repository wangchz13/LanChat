#include "Form/mainform.h"
#include "ui_mainform.h"
#include "Button/messagebutton.h"
#include "databaseconnector.h"
#include "Profile/contactprofile.h"
#include "Button/contactmsgbutton.h"
#include "Network/sendmessage.h"
#include "protocol.h"

#include <QDateTime>
#include <QScrollBar>
#include <QLayout>

#include <qalgorithms.h>

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

void MainForm::newGroup()
{

}

void MainForm::newBuddySlot(M_Login login)
{
    //新建联系人，存储&刷新联系人面板
    ContactButton *cb = new ContactButton(ContactProfile(login._userName,login._computerName,login._ipAddress));

    //如果已经存在，例如本机重复登录
    for(int i = 0; i < _contactVec.size(); i++){
        if(*_contactVec[i] == *cb){
            delete cb;
            return;
        }
    }
    connect(cb, SIGNAL(newChat(ContactProfile)), this, SLOT(newChatSlot(ContactProfile)));
    qDebug() << "new user coming!";
    currentOnline++;
    ui->onlineLabel->setText(tr("当前在线：%1 人").arg(QString::number(currentOnline)));

    _contactVec.push_back(cb);
    if(_contactLayout->isEmpty())
        _contactLayout->insertWidget(0,cb);
    else
        _contactLayout->insertWidget(1,cb);
    if(myIpAddress == login._ipAddress)
        return;

    //向新上线者发送一份自己的login信息
    M_Login my(myUserName, myComputerName,myIpAddress);
    MessageSender sender(my);
    sender.send(QHostAddress(login._ipAddress));
}

void MainForm::newMessageSlot(M_Message msg)
{
    using namespace std;
    ui->msgHintLabel->hide();
    if(msg._type == ProfileType::contact){
        ContactMsgButton *cmb = new ContactMsgButton(msg);
        auto it = std::find_if(_contactMsgVec.begin(), _contactMsgVec.end(),
                               [cmb](ContactMsgButton *i){return *cmb == *i;});
        if(it == _contactMsgVec.end()){
            _contactMsgVec.push_back(cmb);
            it = _contactMsgVec.end() - 1;
        }else{
            (*it)->_data = cmb->_data;
            _msgLayout->removeWidget(*it);
            delete cmb;
        }
        (*it)->refresh();

        _msgLayout->insertWidget(0, *it);

        ChatForm *cf = new ChatForm((*it)->_contact._userName+"["+(*it)->_contact._computerName+"]",
                                    (*it)->_contact._ipAddress,
                                    (*it)->_contact._head,
                                    ProfileType::contact);
        auto cfIt = std::find_if(_currentChatVec.begin(),_currentChatVec.end(),
                                 [cf](ChatForm *i){return *cf == *i;});
        if(cfIt == _currentChatVec.end()){
            _currentChatVec.push_back(cf);
            cfIt = _currentChatVec.end()-1;
        }else{
            delete cf;
        }
        (*cfIt)->newMessageComing(msg);
    }else if(msg._type == ProfileType::group){

    }
}

void MainForm::newChatSlot(ContactProfile c)
{
    using namespace std;
    ChatForm *cf = new ChatForm(c._name, c._data, c._head,ProfileType::contact);
    auto it = find_if(_currentChatVec.begin(), _currentChatVec.end(),
                      [cf](ChatForm *i){return *cf == *i;});
    if(it == _currentChatVec.end()){
        _currentChatVec.push_back(cf);
        it = _currentChatVec.end() - 1;
    }else{
        delete cf;
    }
    (*it)->show();
    (*it)->raise();
}

void MainForm::clearAllMsg()
{
    _contactMsgVec.clear();
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
    if(checked)
        ui->stackedWidget->setCurrentWidget(ui->group_Page);
}
