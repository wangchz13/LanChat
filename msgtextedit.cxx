#include "msgtextedit.h"

#include <QFile>
#include <QKeyEvent>
#include <QRegExp>
#include <QClipboard>
#include <QApplication>
#include <QDebug>
#include <QDir>

MsgTextEdit::MsgTextEdit(QWidget *p)
    :QTextEdit(p)
{
//    _board = QApplication::clipboard();
}

void MsgTextEdit::addAnimation(const QUrl &url, const QString &fileName)
{
    QFile *file = new QFile(fileName);
    file->open(QIODevice::ReadOnly);
    if(_urls.contains(url)) return;
    _urls.append(url);
    QMovie *movie = new QMovie;
    movie->setFileName(fileName);
    movie->setCacheMode(QMovie::CacheNone);

    _movies.append(movie);
    _gifHash.insert(movie, url);

    connect(movie, SIGNAL(frameChanged(int)), this, SLOT(animate(int)));
    movie->setSpeed(80);
    movie->start();
    file->close();
    delete file;
}

bool MsgTextEdit::eventFilter(QObject *target, QEvent *event)
{
    if(event->type() != QEvent::KeyPress)
        return false;
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if(keyEvent->matches(QKeySequence::Paste)){
        QString test;
        QUrl url = findLocalImage(test);
        QString fileName = url.toString().right(url.toString().size() - url.toString().lastIndexOf('/')-1);
        QString format = url.toString().right(3).toUpper();
        if(!url.isEmpty()){
            QFile::copy(url.toString(), tr("./cache/%1").arg(fileName));
            if(_board->image().isNull()){
                //发送文件
            }else{

                if(format == "GIF"){

                }else{
                    QDir dir;
                    dir.setPath(dir.currentPath().append("//cache"));
                    if(!dir.exists()) dir.mkpath(dir.path());
                    _board->image().save(tr("./cache/%1").arg(fileName), 0, 100);
                    textCursor().insertImage(QImage(tr("./cache/%1").arg(fileName)));
                }
            }
        }

        return true;
    }
    return false;
}

QUrl MsgTextEdit::findLocalImage(QString str)
{

    return QUrl();
}

void MsgTextEdit::animate(int)
{
    if(QMovie *movie = qobject_cast<QMovie *>(sender())){
        document()->addResource(QTextDocument::ImageResource,_gifHash.value(movie),movie->currentPixmap());
        setLineWrapColumnOrWidth(lineWrapColumnOrWidth());
    }
}
