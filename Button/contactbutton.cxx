#include "contactbutton.h"

ContactButton::ContactButton(ContactProfile contact):
    ProfileButton(contact._name,contact._data,contact._head),
    _contact(contact)
{
    _type = ProfileType::contact;
}

void ContactButton::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit newChat(BaseProfile(_contact._userName+"["+_contact._computerName+"]",
                             _contact._ipAddress, _contact._head),
                 ProfileType::contact);
}



void ContactButton::mouseReleaseEvent(QMouseEvent *e)
{

}
