#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QVector>

#include "protocol.h"
#include "global.h"
#include "Button/messagebutton.h"
#include "Button/contactbutton.h"
#include "Button/contactmsgbutton.h"
#include "Button/groupbutton.h"
#include "Button/groupmsgbutton.h"
#include "Form/chatform.h"
#include "Profile/baseprofile.h"

namespace Ui {
class MainForm;
}


class QVBoxLayout;
class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
    void initMsgVector();
    void initContactVector();
    void initGroupVector();

    void initMsgPage();
    void initContactPage();
    void initGroupPage();

    void initBottomWidget();

    friend class ContactButton;
    friend class ContactMsgButton;
    friend class GroupButton;

public slots:

    void newGroup();

    void newBuddySlot(M_Login login);
    void newMessageSlot(M_Message msg);
    void fileRequestSlot(M_FileRequest request);
    void fileRefusedSlot(M_FileRequest refuse);

    void newChatSlot(BaseProfile c, ProfileType t);
    void clearAllMsg();

private slots:
    void on_msgPushButton_toggled(bool checked);

    void on_contactPushButton_toggled(bool checked);

    void on_settingPushButton_toggled(bool checked);


private:
    Ui::MainForm *ui;
    QVBoxLayout *_msgLayout;
    QVBoxLayout *_contactLayout;
    QVBoxLayout *_groupLayout;

    //消息页
    QVector<ContactMsgButton *> _contactMsgVec; //存放私聊消息Button
    //联系人页
    QVector<ContactButton*> _contactVec;        //存放联系人Button
    //群组页
    QVector<GroupButton*> _groupVec;

    QVector<ChatForm*> _currentChatVec; //存放当前正在进行的会话Form
};

#endif // MAINFORM_H
