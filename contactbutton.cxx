#include "contactbutton.h"

ContactButton::ContactButton()
{

}

ContactButton::ContactButton(Contact contact):
    ProfileButton(contact._name,contact._data,contact._head)
{
    _type = ProfileType::contact;
}

void ContactButton::mouseDoubleClickEvent(QMouseEvent *e)
{
    ChatForm *c = new ChatForm(this->_title,this->_data,this->_head, this->_type);
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

void ContactButton::mouseReleaseEvent(QMouseEvent *e)
{

}
