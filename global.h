#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QPixmap>
#include <QImage>
#include <QVector>

#include "chatform.h"
class ChatForm;

extern int currentOnline;
extern QString userName;
extern QString computerName;
extern QString ipAddress;

extern QImage defaultHead;
extern QImage contactHead;
extern QImage groupHead;

extern QPixmap *head;

extern QVector<ChatForm*> currentChatVec;
#endif // GLOBAL_H
