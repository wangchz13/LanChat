#ifndef CONTACTMSGBUTTON_H
#define CONTACTMSGBUTTON_H

#include "messagebutton.h"
#include "contact.h"
#include "protocol.h"

class ContactMsgButton : public MessageButton
{
public:
    ContactMsgButton();
    ContactMsgButton(M_Message msg);

    void mouseDoubleClickEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

};

#endif // CONTACTMSGBUTTON_H
