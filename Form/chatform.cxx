#include "Form/chatform.h"
#include "ui_chatform.h"

#include "Network/messagesender.h"
#include "protocol.h"
#include "global.h"

#include <QTextBrowser>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QScrollBar>
#include <QPixmap>
#include <QDebug>
ChatForm::ChatForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatForm)
{
    ui->setupUi(this);
}

ChatForm::ChatForm(QString title, QString data, QImage head, ProfileType type, QWidget *parent):
    QWidget(parent),
    ui(new Ui::ChatForm),
    _title(title),_data(data),_head(head),_type(type)
{
    ui->setupUi(this);
    ui->headLabel->setPixmap(QPixmap::fromImage(_head));
    ui->titleLabel->setText(_title);
    ui->previewLabel->setText(_data);

    ui->closeButton->setObjectName("closeButton");
    ui->sendMsgButton->setObjectName("sendMsgButton");
}

ChatForm::~ChatForm()
{
    delete ui;
}

void ChatForm::initForm()
{

}

void ChatForm::newMessageComing(M_Message msg)
{
    qDebug() << "show message!";
    ui->msgBrowser->setTextColor(Qt::blue);
    ui->msgBrowser->append(msg._sender._userName +"[" + msg._sender._computerName + "]" + " " +msg._time);
    ui->msgBrowser->setTextColor(Qt::black);
    ui->msgBrowser->append(msg._data);

}

void ChatForm::on_sendMsgButton_clicked()
{
    QString msg = ui->msgTextEdit->toPlainText();
    if(msg.isEmpty())
        return;
    M_Message message(myProfile, msg, QDateTime::currentDateTime().time().toString(),
                      this->_type);
    MessageSender messageSender(message);
    //先给自己发一份
    ui->msgBrowser->setTextColor(Qt::darkGreen);
    ui->msgBrowser->append(myUserName+"[" + myComputerName + "]" + " " + message._time);
    ui->msgBrowser->setTextColor(Qt::black);
    ui->msgBrowser->append(message._data);
    if(this->_type == ProfileType::contact){
        messageSender.send(QHostAddress(this->_data));
    }

    else
        messageSender.send();

    ui->msgTextEdit->clear();
    ui->msgTextEdit->setFocus();
}
