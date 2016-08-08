#include "contactmsgbutton.h"

ContactMsgButton::ContactMsgButton()
{

}

ContactMsgButton::ContactMsgButton(M_Message msg):
    BaseButton(msg._sender._name,msg._sender._data/*,msg._sender._head*/),
    _time(msg._time),
    _count(0)
{
    _contact._name = msg._sender._name;
    _contact._data = msg._sender._data;
    /*头像未设置*/
    _timeLabel = new QLabel(_time);
    _countLabel = new QLabel;

    _titleHLayout->addStretch();
    _titleHLayout->addWidget(_timeLabel);

    _dataHLayout->addStretch();
    _dataHLayout->addWidget(_countLabel);
}

void ContactMsgButton::mouseDoubleClickEvent(QMouseEvent *e)
{

}

void ContactMsgButton::mouseReleaseEvent(QMouseEvent *e)
{

}
