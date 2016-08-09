﻿#ifndef GROUPMSGBUTTON_H
#define GROUPMSGBUTTON_H

#include "messagebutton.h"
#include "group.h"
#include "protocol.h"
class GroupMsgButton : MessageButton
{
public:
    GroupMsgButton();
    GroupMsgButton(M_Message msg);

    void mouseDoubleClickEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // GROUPMSGBUTTON_H
