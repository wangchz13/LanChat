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
#include <QColorDialog>

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

    ui->msgTextEdit->installEventFilter(this);
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
    ui->msgBrowser->setFontPointSize(9);
    ui->msgBrowser->setFontUnderline(false);
    ui->msgTextEdit->setFontItalic(false);
    ui->msgBrowser->append(msg._sender._userName +"[" + msg._sender._computerName + "]" + " " +msg._time);
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
        QString savePath = QFileDialog::getSaveFileName(0, tr("保存文件"), request._fileName);
        if(!savePath.isEmpty()){
            int w = ui->sideStackedWidget->width();
            if(ui->sideStackedWidget->isHidden()){
                resize(size().width()+w, size().height());
                ui->sideStackedWidget->show();
                ui->sideStackedWidget->setCurrentWidget(ui->filePage);
            }
            FileWidget *fileWidget = new FileWidget(request._fileName, FileWidgetType::receiver);
            _fileLayout->insertWidget(_fileLayout->count()-1, fileWidget);
            connect(fileWidget, SIGNAL(destroyed(QObject*)), this, SLOT(hideSideWidget(QObject*)));
            FileReceiver *receiver = new FileReceiver(QHostAddress(request._sender._ipAddress), savePath);
            receiver->receive();

            connect(receiver, SIGNAL(updateProgress(qint64,qint64,float)), fileWidget, SLOT(updateProgressSlot(qint64,qint64,float)));
            connect(receiver, SIGNAL(succeed(QString)), fileWidget, SLOT(succeedSlot(QString)));
            connect(receiver, SIGNAL(succeed(QString)), this, SLOT(fileReceivedSucceed(QString)));
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

bool ChatForm::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *e = static_cast<QKeyEvent*>(event);
        if(e->key() == Qt::Key_Return){
            if(e->modifiers() & Qt::ControlModifier)
                return false;
            on_sendMsgButton_clicked();
            return true;
        }
    }
    return false;
}

void ChatForm::hideSideWidget(QObject* widget)
{
    qDebug() << "hide";
    _fileLayout->removeWidget(dynamic_cast<QWidget*>(widget));
    if(_fileLayout->isEmpty()){
        int w = ui->sideStackedWidget->width();
        ui->sideStackedWidget->hide();
        resize(size().width()-w, size().height());
    }
}

void ChatForm::fileReceivedSucceed(QString fileName)
{
    ui->msgBrowser->setTextColor(Qt::gray);
    ui->msgBrowser->append(tr("\n    接收文件 %1 成功\n").arg(fileName));
}

void ChatForm::fileSendSucceed(QString fileName)
{
    ui->msgBrowser->setTextColor(Qt::gray);
    ui->msgBrowser->append(tr("\n    发送文件 %1 成功\n").arg(fileName));
}

void ChatForm::on_sendMsgButton_clicked()
{
    QString msg = ui->msgTextEdit->toPlainText();
    if(msg.isEmpty())
        return;
    msg = ui->msgTextEdit->toHtml();
    M_Message message(myProfile, msg, QDateTime::currentDateTime().time().toString(),
                      this->_type);
    MessageSender messageSender(message);
    //先给自己发一份
    ui->msgBrowser->setTextColor(Qt::darkGreen);
    ui->msgBrowser->setFontPointSize(9);
    ui->msgBrowser->setFontUnderline(false);
    ui->msgTextEdit->setFontItalic(false);
    ui->msgBrowser->append(myProfile._fullName + " " + message._time);

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
    _fileLayout->insertWidget(_fileLayout->count()-1, fileWidget);
    connect(fileWidget, SIGNAL(destroyed(QObject*)), this, SLOT(hideSideWidget(QObject*)));
    connect(this, SIGNAL(fileCancel()), fileWidget, SLOT(deleteLater()));



    FileSender *fileSender = new FileSender(filePath, QHostAddress(_data));
    fileSender->ready();
    connect(fileSender, SIGNAL(updateProgress(qint64,qint64,float)), fileWidget, SLOT(updateProgressSlot(qint64, qint64,float)));
    connect(fileSender, SIGNAL(succeed(QString)), fileWidget, SLOT(succeedSlot(QString)));
    connect(fileSender, SIGNAL(succeed(QString)), this, SLOT(fileSendSucceed(QString)));
    connect(this, SIGNAL(fileCancel()), fileSender, SLOT(cancel()));
}

void ChatForm::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->msgTextEdit->setFont(f);
    ui->msgTextEdit->setFocus();
}

void ChatForm::on_sizeComboBox_currentIndexChanged(const QString &arg1)
{
    ui->msgTextEdit->setFontPointSize(arg1.toDouble());
    ui->msgTextEdit->setFocus();
}

void ChatForm::on_boldToolBtn_toggled(bool checked)
{
    if(checked)
        ui->msgTextEdit->setFontWeight(QFont::Bold);
    else
        ui->msgTextEdit->setFontWeight(QFont::Normal);
    ui->msgTextEdit->setFocus();
}

void ChatForm::on_italicToolBtn_toggled(bool checked)
{
    ui->msgTextEdit->setFontItalic(checked);
    ui->msgTextEdit->setFocus();
}

void ChatForm::on_underlineToolBtn_toggled(bool checked)
{
    ui->msgTextEdit->setFontUnderline(checked);
    ui->msgTextEdit->setFocus();
}

void ChatForm::on_colorToolBtn_clicked()
{
    QColor color = QColorDialog::getColor(color, this);
    if (color.isValid()) {
        ui->msgTextEdit->setTextColor(color);
        ui->msgTextEdit->setFocus();
    }
}
