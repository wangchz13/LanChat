/*******************************************
**
** 类名：ChatForm
** 父类：QWidget
** 作用：聊天界面，包括
**
** ****************************************/
#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>
#include <QVector>
#include <QImage>

#include "global.h"
#include "protocol.h"
#include "Network/filereceiver.h"
#include "facetableview.h"

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
    ChatForm(QString title, QString context, QImage head, ProfileType type, QWidget *parent=0);
    ~ChatForm();
    void initForm();

    bool operator ==(const ChatForm &rhs){
        return this->_title == rhs._title && this->_type == rhs._type;
    }

    void newMessageComing(M_Message msg);

    void fileRequest(M_File request);
    void fileRefused(M_File refuse);
    void fileReceive(M_File receive);

protected:
    bool eventFilter(QObject *watched, QEvent *event);
signals:
    void fileCancel();  //对方拒绝接受
    void fileSend();

public slots:
    void hideSideWidget(QObject *widget);
    void fileReceivedSucceed(QString fileName);
    void fileSendSucceed(QString fileName);

    void insertEmoji(QString emoji);
private slots:
    void on_sendMsgButton_clicked();

    void on_sendFileBtn_clicked();

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_sizeComboBox_currentIndexChanged(const QString &arg1);

    void on_boldToolBtn_toggled(bool checked);

    void on_italicToolBtn_toggled(bool checked);

    void on_underlineToolBtn_toggled(bool checked);

    void on_colorToolBtn_clicked();

    void on_faceToolBtn_toggled(bool checked);

private:
    Ui::ChatForm *ui;
    QVBoxLayout *_fileLayout;
    FaceTableView *_face;

public:
    QString _title;
    QString _data;
    QImage _head;

    ProfileType _type;
};

#endif // CHATFORM_H
