/*************************************************
**
** 类名：ContactButton
** 父类：ProfileButton
** 作用：在联系人页面显示联系人
**
** ***********************************************/
#ifndef CONTACTBUTTON_H
#define CONTACTBUTTON_H

#include "profilebutton.h"
#include "contact.h"

class ContactButton : public ProfileButton
{
public:
    ContactButton();
    ContactButton(Contact contact);

    void mouseDoubleClickEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // CONTACTBUTTON_H
