#include "chatsimple.h"
#include "ui_chatsimple.h"
#include <QMessageBox>
#include <QDebug>
#include <QMetaType>
#include "string.h"
#include <QPalette>

chatSimple::chatSimple(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::chatSimple)
{
    ui->setupUi(this);
    qRegisterMetaType<wechat_msg> ("wechat_msg");
    initLineEdit();
    is_login = false;
    initMsg();
    initThread();
    patlette_green.setColor(QPalette::Text, Qt::green);
    patlette_blue.setColor(QPalette::Text, Qt::blue);
    ui->textEdit->setPalette(patlette_blue);
}

chatSimple::~chatSimple()
{
    delete ui;
    childThread->exit();
//    childThread->wait();
    delete  childThread;
    delete myLineEdit_sendinfo;
    delete syszuxpinyin_sendInfo;
}
void chatSimple::keyboardshow_sendInfo(QString data)
{
    syszuxpinyin_sendInfo->lineEdit_window->setText(data);
    syszuxpinyin_sendInfo->resize(800,348);
    syszuxpinyin_sendInfo->move(100,0);
    syszuxpinyin_sendInfo->show();
}
void chatSimple::confirmString_sendInfo(QString gemfield)
{
    myLineEdit_sendinfo->setText(gemfield);
}
void chatSimple::initLineEdit()
{
    myLineEdit_sendinfo = new My_lineEdit(this);
    myLineEdit_sendinfo->setObjectName("lineEdit_sendInfo");
    myLineEdit_sendinfo->setGeometry(QRect(50, 500, 930, 80));
//    myLineEdit_sendinfo->setStyleSheet("QLineEdit{background-color:transparent}"
//                                        "QLineEdit{border-width:0;border-style:outset}");
    myLineEdit_sendinfo->setText("I'm sxg.");
    syszuxpinyin_sendInfo =new SyszuxPinyin();
    connect(myLineEdit_sendinfo,SIGNAL(send_show(QString)),this,SLOT(keyboardshow_sendInfo(QString)));
    connect(syszuxpinyin_sendInfo,SIGNAL(sendPinyin(QString)),this,SLOT(confirmString_sendInfo(QString)));
}

void chatSimple::on_login_ptn_clicked()
{
    if(is_login) return;
    ui->login_ptn->setEnabled(false);
    int conret = initSocket();
    if(conret < 0){
        perror("couldn't connect");
        return;
    }
    sendMsg.type = WECHAT_SIGNIN;
    childThread->start();
    send(sock_client,&sendMsg,sizeof(sendMsg),0);
//    recv(sock_client,&recvMsg,sizeof(recvMsg),0);
    emit recvMsgWork(sock_client,recvMsg);
//    if(recvMsg.type & WECHAT_ACK){
//        QMessageBox msgBox;
//        msgBox.setText("login successly.");
//        msgBox.exec();
//        is_login = true;
//    }else{
//        QMessageBox msgBox;
//        msgBox.setText("login failed.");
//        msgBox.exec();
//    }
}

void chatSimple::on_logout_ptn_clicked()
{
    if(!is_login) return;
    sendMsg.type = WECHAT_FIN;
    send(sock_client,&sendMsg,sizeof(sendMsg),0);
    ::close(sock_client);
    QMessageBox msgBox;
    msgBox.setText("logout successly.");
    msgBox.exec();
    is_login = false;
}

void chatSimple::on_flush_ptn_clicked()
{
    ui->textEdit->clear();
    ui->textEdit_sys->clear();
    if(!is_login){
        QMessageBox msgBox;
        msgBox.setText("please login first.");
        msgBox.exec();
        return;
    }
}

void chatSimple::on_send_ptn_clicked()
{
    if(!is_login){
        QMessageBox msgBox;
        msgBox.setText("please login first.");
        msgBox.exec();
        return;
    }
    memset(sendMsg.msg,0,sizeof(sendMsg.msg));
    QString str = myLineEdit_sendinfo->text();
//    char *chptr = str.toUtf8().data();
//    size_t cpy_len = (int)sizeof(chptr)>str.size() ? (int)sizeof(chptr):str.size();
//    qDebug() << "chptr.count() = "<<sizeof(chptr) ;
//    memcpy(&sendMsg.msg,str.toUtf8().data(),cpy_len);
    strcpy(sendMsg.msg, str.toUtf8().data());
    ui->textEdit->setAlignment(Qt::AlignRight);


    ui->textEdit->setTextColor(Qt::green);
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText(str);
    ui->textEdit->insertPlainText("\n");
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->setAlignment(Qt::AlignLeft);
    ui->textEdit->setTextColor(Qt::blue);
//    ui->textEdit->insertPlainText(sendMsg.msg);
    sendMsg.type = WECHAT_WALL;
    if(sendMsg.msg[0] == '@'){
        sendMsg.type = WECHAT_MSG;\
        strncpy(sendMsg.to, sendMsg.msg+1,strchr(sendMsg.msg,' ')-sendMsg.msg-1);
    }
    send(sock_client,&sendMsg,sizeof(sendMsg),0);
}

int chatSimple::initSocket(){
    sock_client = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    server_addr.sin_port = htons(PORT);
    int conret = ::connect(sock_client,(struct sockaddr *)&server_addr,sizeof(server_addr));
    if(conret < 0) return -1;
    return conret;
}

void chatSimple::initMsg(){
    memset(&sendMsg,0,sizeof(sendMsg));
    memset(&recvMsg,0,sizeof(recvMsg));
    sendMsg.type = WECHAT_SIGNIN;
    sendMsg.sex = 1;
    memcpy(sendMsg.name,myName,sizeof(myName));
    memcpy(sendMsg.passwd,myPasswd,sizeof(myPasswd));

    recvMsg.sex = 1;
    memcpy(recvMsg.name,myName,sizeof(myName));
    memcpy(recvMsg.passwd,myPasswd,sizeof(myPasswd));
}

void chatSimple::initThread(){
    childThread = new QThread(this);
    WorkerMsg *worker = new WorkerMsg;
    worker->moveToThread(childThread);
//    connect(lineEdit_serialName,SIGNAL(send_show(QString)),this,SLOT(keyboardshow_serialName(QString)));
    connect(this,&chatSimple::recvMsgWork,worker, &WorkerMsg::doWork);
//    connect(this,SIGNAL(recvMsgWork(int,wechat_msg)),worker, SLOT(doWork(int,wechat_msg)));
    connect(worker, &WorkerMsg::resultReady,this, [&](wechat_msg msg){
        if(msg.type == -1){

        }else if(msg.type < 0){
                QMessageBox msgBox;
                msgBox.setText("服务器已断开连接");
                msgBox.exec();
//                childThread->exit();
//                childThread->wait();
                is_login = false;
                ui->login_ptn->setEnabled(true);
            }else if((msg.type & WECHAT_ACK) && is_login == false){
//                ui->textEdit->moveCursor(QTextCursor::End);
//                ui->textEdit->insertPlainText(QString("已成功连接上服务器\n"));
//                ui->textEdit->moveCursor(QTextCursor::End);
                QMessageBox msgBox;
                msgBox.setText("login successly.");
                msgBox.exec();
                is_login = true;
                ui->login_ptn->setEnabled(true);
            }else if(msg.type & WECHAT_ACK){
            }else if(msg.type & WECHAT_WALL){
                QString str(msg.msg);
                ui->textEdit->moveCursor(QTextCursor::End);
                ui->textEdit->insertPlainText(str);
                ui->textEdit->insertPlainText("\n");
                ui->textEdit->moveCursor(QTextCursor::End);
            }else if(msg.type & WECHAT_SYS){
                QString str(msg.msg);
                ui->textEdit_sys->moveCursor(QTextCursor::End);
                ui->textEdit_sys->insertPlainText(str);
                ui->textEdit_sys->moveCursor(QTextCursor::End);
            }else if(msg.type & WECHAT_MSG){
                QString str(msg.name);
                str.append(" : ");
                str.append(msg.msg);
                ui->textEdit->moveCursor(QTextCursor::End);
                ui->textEdit->insertPlainText(str);
                ui->textEdit->insertPlainText("\n");
                ui->textEdit->moveCursor(QTextCursor::End);
            }
        if(msg.type >= -1){
            memset(recvMsg.msg,0,sizeof(recvMsg.msg));
            emit recvMsgWork(sock_client,recvMsg);
        }
    });
    connect(childThread, &QThread::finished, worker,&QObject::deleteLater);


}

void chatSimple::on_back_ptn_clicked()
{
    if(!is_login) {
        this->close();
        this->deleteLater();
        return;
    }
    sendMsg.type = WECHAT_FIN;
    send(sock_client,&sendMsg,sizeof(sendMsg),0);
    ::close(sock_client);
    is_login = false;
    this->close();
this->deleteLater();
}
