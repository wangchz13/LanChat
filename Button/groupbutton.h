#ifndef GROUPBUTTON_H
#define GROUPBUTTON_H

#include "Button/profilebutton.h"
#include "Profile/groupprofile.h"

#include "global.h"

class GroupButton : public ProfileButton
{
    Q_OBJECT
public:
    GroupButton();
    GroupButton(GroupProfile group);

    void mouseDoubleClickEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void newChat(BaseProfile g, ProfileType t);

private:
    GroupProfile _group;
};

#endif // GROUPBUTTON_H
