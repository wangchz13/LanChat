#include "messagebutton.h"

//MessageButton::MessageButton(QString title, QString data, QString time, QImage head):
//    BaseButton(title, data, head),
//    _time(time),
//    _count(0)
//{
//    //调用者应该有一句MessageButton.profile = new contact...

//    _timeLabel = new QLabel(_time);
//    _timeLabel->setObjectName("timeLabel");
//    _countLabel = new QLabel;
//    _countLabel->setObjectName("countLabel");

//    _titleHLayout->addStretch();
//    _titleHLayout->addWidget(_timeLabel);

//    _dataHLayout->addStretch();
//    _dataHLayout->addWidget(_countLabel);
//}

MessageButton::MessageButton(M_Message message):
    BaseButton(message._sender._userName+"["+ message._sender._computerName +"]",
               message._data),
    _time(message._time)
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

MessageButton::MessageButton(QString title, QString data, QString time):
    BaseButton(title, data),
    _time(time)
{

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
