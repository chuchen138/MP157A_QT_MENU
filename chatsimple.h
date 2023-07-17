#ifndef CHATSIMPLE_H
#define CHATSIMPLE_H

#include <QMainWindow>
#include <QThread>
#include <QPalette>
#include <QString>
#include "syszuxpinyin.h"
#include "my_lineedit.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"
#include "wechat.h"
//#include "worker.h"

//#define MAX(x,y) ((x)>(y)?(x):(y)))
#define SERVER_ADDR "8.140.34.20"
#define PORT 9999
const char myName[] = "ubuntu_sxg";
const char myPasswd[] = "123456";

QT_BEGIN_NAMESPACE
namespace Ui { class chatSimple; }
QT_END_NAMESPACE

class chatSimple : public QMainWindow
{
    Q_OBJECT

public:
    chatSimple(QWidget *parent = nullptr);
    ~chatSimple();

    void initLineEdit();
    int initSocket();
    void initMsg();
    void initThread();

private slots:
    void on_login_ptn_clicked();
    void on_logout_ptn_clicked();
    void on_flush_ptn_clicked();
    void on_send_ptn_clicked();

    void keyboardshow_sendInfo(QString data);
    void confirmString_sendInfo(QString gemfield);

    void on_back_ptn_clicked();

signals:
    void recvMsgWork(int fd,wechat_msg msg);

private:
    Ui::chatSimple *ui;
    My_lineEdit *myLineEdit_sendinfo;
    SyszuxPinyin *syszuxpinyin_sendInfo;
    QThread *childThread;
    bool is_login;
    int sock_client;
    wechat_msg sendMsg,recvMsg;
    char buff[512];
    QPalette patlette_green, patlette_blue ;
};

#endif // CHATSIMPLE_H
