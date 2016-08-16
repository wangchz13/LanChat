#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QVector>

#include "protocol.h"
#include "global.h"
#include "messagebutton.h"
#include "contactbutton.h"
#include "contactmsgbutton.h"
#include "groupbutton.h"
#include "groupmsgbutton.h"

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
    void newContact( QString userName, QString computerName, QString ipAddress,QPixmap *head=NULL);
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
