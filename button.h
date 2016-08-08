#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QPixmap>

class Button : public QPushButton
{
    Q_OBJECT

public:
    Button(QWidget *parent = 0);
    Button(QPixmap *head, QString title, QString *preview, QString time, QWidget *parent = NULL);
    ~Button();
    void mouseDoubleClickEvent(QMouseEvent *event);

public slots:
    void hideCount();
    void newMessageComing();
private:
    QPixmap *m_head;
    QString m_title;
    QString *m_preview;
    QString m_time;
    QPixmap *m_countPixmap;
    QWidget *m_parent;

    QLabel *m_counterLabel;
    quint16 m_msgNumber;
};

#endif
