#include "messagebutton.h"

MessageButton::MessageButton(M_Message msg):
    BaseButton(msg._sender._userName+"["+ msg._sender._computerName +"]",
               msg._data),
    _time(msg._time),
    _count(0)
{
    _timeLabel = new QLabel(_time);
    _timeLabel->setObjectName("timeLabel");

    _countLabel = new QLabel;
    _countLabel->setObjectName("countLabel");

    _titleHLayout->addStretch();
    _titleHLayout->addWidget(_timeLabel);

    _dataHLayout->addStretch();
    _dataHLayout->addWidget(_countLabel);
}

MessageButton::MessageButton(QString title, QString data, QString time, QImage head):
    BaseButton(title, data, head),
    _time(time),
    _count(0)
{

}

MessageButton::~MessageButton()
{
    delete _timeLabel;
    delete _countLabel;
}

void MessageButton::refresh()
{
    _countLabel->show();
    _count++;
    if(_count < 99)
        _countLabel->setText(QString::number(_count, 10));
    else
        _countLabel->setText("99+");
    _dataLabel->setText(_data);
}
