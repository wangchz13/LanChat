#include "Form/mainform.h"
#include "ui_mainform.h"
#include "Button/messagebutton.h"
#include "Button/contactmsgbutton.h"
//#include "Button/groupbutton.h"
#include "databaseconnector.h"
#include "Profile/contactprofile.h"
#include "Network/messagesender.h"
#include "protocol.h"

#include <QDateTime>
#include <QScrollBar>
#include <QLayout>
#include <QMessageBox>

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
    initGroupPage();

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

void MainForm::initGroupPage()
{
    _groupLayout = new QVBoxLayout;
    _groupLayout->setSpacing(0);
    _groupLayout->addStretch();
    ui->scrollAreaWidgetContents_3->setLayout(_groupLayout);
}

void MainForm::initBottomWidget()
{
    ui->onlineLabel->setText(tr("当前在线：%1人").arg(QString::number(currentOnline)));
}

void MainForm::newGroup()
{
    GroupProfile lanGroup("大厅", "哈哈快来聊天吧！", QDateTime::currentDateTime().time().toString());
    GroupButton *gb = new GroupButton(lanGroup);
    connect(gb, SIGNAL(newChat(BaseProfile,ProfileType)), this, SLOT(newChatSlot(BaseProfile,ProfileType)));
    _groupVec.push_back(gb);
    _groupLayout->insertWidget(0,gb);
}

void MainForm::newBuddySlot(M_Login login)
{
    //新建联系人，存储&刷新联系人面板

    ContactButton *cb = new ContactButton(ContactProfile(login._userName,login._computerName,login._ipAddress));

    for(int i = 0; i < _contactVec.size(); i++){
        if(*_contactVec[i] == *cb){

            delete cb;
            return;
        }
    }
    connect(cb, SIGNAL(newChat(BaseProfile,ProfileType)), this, SLOT(newChatSlot(BaseProfile,ProfileType)));
    qDebug() << "new user coming!";
    currentOnline++;
    ui->onlineLabel->setText(tr("当前在线：%1 人").arg(QString::number(currentOnline)));

    _contactVec.push_back(cb);
    if(_contactLayout->isEmpty())
        _contactLayout->insertWidget(0,cb);
    else
        _contactLayout->insertWidget(1,cb);


    if(myIpAddress == login._ipAddress){
        newGroup();
        return;
    }

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
            connect(cmb, SIGNAL(newChat(BaseProfile,ProfileType)), this, SLOT(newChatSlot(BaseProfile,ProfileType)));
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

void MainForm::fileRequestSlot(M_File request)
{
    qDebug() << "fileRequestSlot:" << request._fileName;
    using namespace std;
    QString sender = request._sender._fullName;
    auto it = find_if(_currentChatVec.begin(), _currentChatVec.end(),
                      [&sender](ChatForm *i){return sender == i->_title;});
    if(it == _currentChatVec.end()){
        ChatForm *cf = new ChatForm(sender, request._sender._ipAddress,request._sender._head, ProfileType::contact);
        _currentChatVec.push_back(cf);
        it = _currentChatVec.end()-1;
    }
    ChatForm *curr = *it;
    curr->show();
    curr->fileRequest(request);
}

void MainForm::fileRefusedSlot(M_File refused)
{
    using namespace std;
    QString sender = refused._sender._fullName;
    auto it = find_if(_currentChatVec.begin(), _currentChatVec.end(),
                      [&sender](ChatForm *i){return sender == i->_title;});
    if(it == _currentChatVec.end()){
        ChatForm *cf = new ChatForm(sender, refused._sender._ipAddress,refused._sender._head,ProfileType::contact);
        _currentChatVec.push_back(cf);
        it = _currentChatVec.end()-1;
    }
    ChatForm *curr = *it;
    curr->show();
    curr->fileRefused(refused);
}

void MainForm::fileReceiveSlot(M_File receive)
{
    using namespace std;
    QString sender = receive._sender._fullName;
    auto it = find_if(_currentChatVec.begin(), _currentChatVec.end(),
                      [&sender](ChatForm *i){return sender == i->_title;});
    if(it == _currentChatVec.end()){
        ChatForm *cf = new ChatForm(sender, receive._sender._ipAddress, receive._sender._head, ProfileType::contact);
        _currentChatVec.push_back(cf);
        it = _currentChatVec.end()-1;
    }
    ChatForm *curr = *it;
    curr->fileReceive(receive);
}

void MainForm::newChatSlot(BaseProfile c, ProfileType t)
{
    using namespace std;

    ChatForm *cf = new ChatForm(c._name, c._data, c._head, t);

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
