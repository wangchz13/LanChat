#ifndef GROUPMSGBUTTON_H
#define GROUPMSGBUTTON_H

#include "basebutton.h"
#include "group.h"
#include "protocol.h"
class GroupMsgButton : BaseButton
{
public:
    GroupMsgButton();
    GroupMsgButton(M_Message msg);

    void mouseDoubleClickEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
public:
    QString _time;
    quint16 _count;

private:
    QLabel *_timeLabel;
    QLabel *_countLabel;
    Group _group;
};

#endif // GROUPMSGBUTTON_H
