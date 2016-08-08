#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>
#include <QVector>

class QLabel;
class QVBoxLayout;
class QTextBrowser;

namespace Ui {
class ChatForm;
}

class ChatForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatForm(QWidget *parent = 0);
    explicit ChatForm( QString title, QString context, QPixmap *head=NULL,QWidget *parent=0);
    ~ChatForm();
    void initForm();
private slots:
    void on_sendMsgButton_clicked();

private:
    Ui::ChatForm *ui;

    QString m_title;
    QString m_preview;
    QPixmap *m_head;

    QLabel *m_previewLabel;

    QWidget *m_parent;

    QString bid;
    QVBoxLayout *browserLayout;

    QVector<QTextBrowser *> msgVector;
};

#endif // CHATFORM_H
