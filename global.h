#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QPixmap>
#include <QImage>
#include <QVector>

class ChatForm;
class ContactProfile;

extern int currentOnline;
extern QString myUserName;
extern QString myComputerName;
extern QString myIpAddress;

extern QImage defaultHead;
extern QImage contactHead;
extern QImage groupHead;

extern QPixmap *head;

extern ContactProfile myProfile;
#endif // GLOBAL_H
