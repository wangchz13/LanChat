#include "chatform.h"
#include "ui_chatform.h"

#include "sendmessage.h"
#include "protocol.h"

#include <QTextBrowser>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QScrollBar>
#include <QDebug>
ChatForm::ChatForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatForm)
{
    ui->setupUi(this);
}

ChatForm::ChatForm(QString title, QString context, QPixmap *head,QWidget *parent):
    m_title(title),m_preview(context),m_head(head),
    QWidget(parent),
    ui(new Ui::ChatForm)
{
    ui->setupUi(this);
    if(m_head)
        ui->headLabel->setPixmap(*m_head);
    ui->titleLabel->setText(m_title);
    ui->previewLabel->setText(m_preview);
    bid = m_title;

    browserLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    browserLayout->addStretch();
}

ChatForm::~ChatForm()
{
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
    M_Message message(m_title, msg, DataProcess::creatKey());
    MessageSender messageSender(message);
    messageSender.send();

    ui->msgTextEdit->clear();
    ui->msgTextEdit->setFocus();
}
