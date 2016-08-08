#ifndef CONTACTMSGBUTTON_H
#define CONTACTMSGBUTTON_H

#include "basebutton.h"
#include "contact.h"
#include "protocol.h"

class ContactMsgButton : public BaseButton
{
public:
    ContactMsgButton();
    ContactMsgButton(M_Message msg);

    void mouseDoubleClickEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
public:
    QString _time;
    quint16 _count;

private:
    QLabel *_timeLabel;
    QLabel *_countLabel;
    Contact _contact;
};

#endif // CONTACTMSGBUTTON_H
