#include "groupbutton.h"

GroupButton::GroupButton()
{

}

GroupButton::GroupButton(GroupProfile group):
    ProfileButton(group._name, group._data, group._head),
    _group(group)
{
    _type = ProfileType::group;
}

void GroupButton::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit newChat(BaseProfile(_group._name, _group._data, _group._head), ProfileType::group);
}

void GroupButton::mouseReleaseEvent(QMouseEvent *e)
{

}
