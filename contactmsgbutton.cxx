#include "contactmsgbutton.h"

#include "chatform.h"

ContactMsgButton::ContactMsgButton(M_Message msg):
    MessageButton(msg._userName,msg._data,msg._time)
{
    _profile = new ContactProfile(msg._userName,msg._data,msg._ipAddress);
    //_profile->_name = msg._userName;
    //_profile->_data = msg._data;
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
    this->_count = 0;
    this->_countLabel->setText("");

    ChatForm *c = new ChatForm(this->_title,this->_data,this->_head, ProfileType::contact);
    for(int i = 0; i < currentChatVec.size(); ++i){
        if(*currentChatVec[i] == *c){
            currentChatVec[i]->show();
            currentChatVec[i]->raise();
            return;
        }
    }
    c->show();
    currentChatVec.push_back(c);

}

void ContactMsgButton::mouseReleaseEvent(QMouseEvent *e)
{

}
