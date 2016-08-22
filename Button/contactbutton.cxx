#include "contactbutton.h"

ContactButton::ContactButton(ContactProfile contact):
    ProfileButton(contact._name,contact._data,contact._head),
    _contact(contact)
{
    _type = ProfileType::contact;
}

void ContactButton::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit newChat(BaseProfile(_contact._name, _contact._data, _contact._head));
}



void ContactButton::mouseReleaseEvent(QMouseEvent *e)
{

}
