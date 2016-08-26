#ifndef MSGTEXTEDIT_H
#define MSGTEXTEDIT_H
#include <QTextEdit>
#include <QWidget>
#include <QMovie>
#include <QHash>
#include <QUrl>
#include <QString>
#include <QClipboard>

class MsgTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    MsgTextEdit(QWidget *p=0);
    void addAnimation(const QUrl &url, const QString &fileName);
    bool eventFilter(QObject *target, QEvent *event);

    QUrl findLocalImage(QString str);
    QUrl findHttpImage(QString str);

private slots:
    void animate(int);
private:
    QClipboard *_board;

    QList<QUrl> _urls;
    QList<QImage *> _images;
    QHash<QImage *, QUrl> _imgHash;
    QList<QMovie *> _movies;
    QHash<QMovie *, QUrl> _gifHash;
};

#endif // MSGTEXTEDIT_H
