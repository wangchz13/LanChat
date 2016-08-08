/********************************
**
** 类名：ProfileButton
** 父类：BaseButton
** 作用：额，直觉告诉我该加一个中间件(好与MessageButton对称)，虽然现在看起来没啥用，但愿以后会起作用吧:)
**
** ******************************/
#ifndef PROFILEBUTTON_H
#define PROFILEBUTTON_H
#include "basebutton.h"

class ProfileButton : public BaseButton
{
public:
    ProfileButton();
    ProfileButton(QString title, QString data="", QImage head = defaultHead);

    void mouseDoubleClickEvent(QMouseEvent *e){}
    void mouseReleaseEvent(QMouseEvent *e){}
};

#endif // PROFILEBUTTON_H
