#include "groupbutton.h"

GroupButton::GroupButton()
{

}

GroupButton::GroupButton(GroupProfile group):
    ProfileButton(group._name, group._data, group._head),
    _group(group)
{
    _type = ProfileType::contact;
}

void GroupButton::mouseDoubleClickEvent(QMouseEvent *e)
{

}

void GroupButton::mouseReleaseEvent(QMouseEvent *e)
{

}
