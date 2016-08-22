/*************************************************
**
** 类名：ContactButton
** 父类：ProfileButton
** 作用：在联系人页面显示联系人
**
** ***********************************************/
#ifndef CONTACTBUTTON_H
#define CONTACTBUTTON_H

#include "Button/profilebutton.h"
#include "Profile/contactprofile.h"
#include "Form/chatform.h"

#include "global.h"

class ContactButton : public ProfileButton
{
    Q_OBJECT
public:
    ContactButton();
    ContactButton(ContactProfile contact);

    void mouseDoubleClickEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void newChat(ContactProfile c);

private:
    ContactProfile _contact;
};

#endif // CONTACTBUTTON_H
