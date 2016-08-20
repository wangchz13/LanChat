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
public slots:

    void newGroup();

    void newBuddySlot(M_Login login);
    void newMessageSlot(M_Message msg);
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

    QVector<ContactMsgButton *> _contactMsgVec;

    QVector<ContactButton*> _contactVec;
    QVector<GroupButton*> _groupVec;
};

#endif // MAINFORM_H
