﻿#include "Button/contactmsgbutton.h"

#include "Form/chatform.h"

ContactMsgButton::ContactMsgButton(M_Message msg):
    MessageButton(msg),
    _contact(msg._sender)
{
    this->_count = 0;
    int peer = _contact._ipAddress.right(3).toInt();
    int my = myIpAddress.right(3).toInt();
    _key = my * 256 + peer;
    qDebug() << _key << endl;
}

void ContactMsgButton::mouseDoubleClickEvent(QMouseEvent *e)
{
    this->_count = 0;
    this->_countLabel->setText("");
    //emit newChat(this->_title, this->_profile->_data,"");//TODO:
}

void ContactMsgButton::mouseReleaseEvent(QMouseEvent *e)
{

}
