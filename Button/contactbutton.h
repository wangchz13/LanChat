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
public:
    ContactButton();
    ContactButton(ContactProfile contact);

    void mouseDoubleClickEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

};

#endif // CONTACTBUTTON_H
