/**************************************
**
** 类名：ContactMsgButton
** 父类：MessageButton
** 作用：个人消息显示按钮
**
** ***********************************/
#ifndef CONTACTMSGBUTTON_H
#define CONTACTMSGBUTTON_H

#include "Button/messagebutton.h"
#include "Profile/contactprofile.h"
#include "protocol.h"

class ContactMsgButton : public MessageButton
{
public:
    ContactMsgButton(M_Message msg);

    void mouseDoubleClickEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    bool operator ==(const ContactMsgButton &rhs){
        return _key == rhs._key;
    }

private:
    int _key;
};

#endif // CONTACTMSGBUTTON_H
