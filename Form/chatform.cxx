#include "Form/chatform.h"
#include "ui_chatform.h"

#include "Network/messagesender.h"
#include "Network/filesender.h"
#include "Button/filewidget.h"

#include "protocol.h"
#include "global.h"

#include <QTextBrowser>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QScrollBar>
#include <QPixmap>
#include <QSizePolicy>


#include <QFileDialog>

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
    ui->sideStackedWidget->hide();
//    QPalette back;
//    back.setBrush(QPalette::Background, QBrush(QPixmap(":/source/main.png")));
//    this->setPalette(back);

    _fileLayout = new QVBoxLayout;
    _fileLayout->addStretch();
    ui->scrollAreaWidgetContents->setLayout(_fileLayout);
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

void ChatForm::fileRequest(M_File request)
{
    int ret = QMessageBox::question(this, "接收文件",
                            tr("是否接收来自 %1 的文件 %2 ?")
                            .arg(request._sender._fullName)
                            .arg(request._fileName),
                            QMessageBox::Yes | QMessageBox::No,
                            QMessageBox::Yes);
    if(ret == QMessageBox::Yes){
        qDebug() << "选择接收文件" << endl;
        QString savePath = QFileDialog::getSaveFileName(0, tr("保存文件"), request._fileName);
        if(!savePath.isEmpty()){
            MessageSender receive(M_File(myProfile, request._fileName), MessageType::receiveFile);
            receive.send(QHostAddress(request._sender._ipAddress));

            FileReceiver *receiver = new FileReceiver(QHostAddress(request._sender._ipAddress), savePath);
            receiver->receive();
        }else
            ret = QMessageBox::No;
    }
    if(ret != QMessageBox::Yes){
        MessageSender refuse(M_File(myProfile, request._fileName), MessageType::refuseFile);
        refuse.send(QHostAddress(request._sender._ipAddress));
    }
    qDebug() << ret;
}

void ChatForm::fileRefused(M_File refuse)
{
    QMessageBox::critical(this, "发送文件", tr("%1 拒绝接受文件！").arg(refuse._sender._fullName),
                          QMessageBox::Yes,QMessageBox::Yes);
    emit fileCancel();
}

void ChatForm::fileReceive(M_File receive)
{
    emit fileSend();
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
    ui->msgBrowser->append(myProfile._fullName + " " + message._time);
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

void ChatForm::on_sendFileBtn_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this);
    if(filePath.isEmpty()) return;

    QSize size = this->size();
    int w = ui->sideStackedWidget->width();
    if(ui->sideStackedWidget->isHidden()){
        resize(size.width()+w, size.height());
        ui->sideStackedWidget->show();
        ui->sideStackedWidget->setCurrentWidget(ui->filePage);
    }
    QString fileName = filePath.right(filePath.size() - filePath.lastIndexOf('/')-1);
    FileWidget *fileWidget = new FileWidget(fileName, FileWidgetType::sender);
    _fileLayout->insertWidget(0,fileWidget);
    connect(this, SIGNAL(fileCancel()), fileWidget, SLOT(deleteLater()));

    FileSender *fileSender = new FileSender(filePath, QHostAddress(_data));
    fileSender->initServer();
    fileSender->ready();
    connect(this, SIGNAL(fileCancel()), fileSender, SLOT(cancel()));
    connect(this, SIGNAL(fileSend()), fileSender, SLOT(send()));
}
