#include "contactbutton.h"

ContactButton::ContactButton()
{

}

ContactButton::ContactButton(Contact contact):
    ProfileButton(contact._name,contact._data,contact._head)
{

}

void ContactButton::mouseDoubleClickEvent(QMouseEvent *e)
{

}

void ContactButton::mouseReleaseEvent(QMouseEvent *e)
{

}
