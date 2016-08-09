#include "chatform.h"
#include "ui_chatform.h"

#include "sendmessage.h"
#include "protocol.h"

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
}

ChatForm::~ChatForm()
{
    qDebug() << "be destory\n";
    delete ui;
}

void ChatForm::initForm()
{

}

void ChatForm::on_sendMsgButton_clicked()
{
    QString msg = ui->msgTextEdit->toHtml();
    if(msg.isEmpty())
        return;
    M_Message message(userName+"["+computerName+"]", msg, ipAddress, QDateTime::currentDateTime().toString(), this->_type);
    MessageSender messageSender(message);
    messageSender.send();

    ui->msgTextEdit->clear();
    ui->msgTextEdit->setFocus();
}
