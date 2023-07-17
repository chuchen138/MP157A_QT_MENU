#ifndef WECHAT_H
#define WECHAT_H

#include <QObject>
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"
#include <QDebug>
//#include "wechat.h"



struct wechat_user{
    char name[20];
    char passwd[20];
    int sex;
    int fd;
    int is_online;
};

#define SUB_MAXEVENTS 100
#define MAX_USERS 100
#define MAX_BYTE 512
#define WECHAT_SIGNUP 0x01
#define WECHAT_SIGNIN 0x02
#define WECHAT_SIGOUT 0x04
#define WECHAT_ACK 0x08
#define WECHAT_NAK 0x10
#define WECHAT_WALL 0X20
#define WECHAT_MSG 0x40
#define WECHAT_SYS 0x80
#define WECHAT_FIN 0x04

struct wechat_msg{
    int type;
    int sex;
    char name[20];
    char passwd[20];
    char msg[MAX_BYTE];
    char to[20];
};

class WorkerMsg:public QObject
{
    Q_OBJECT
public:
    explicit WorkerMsg(QObject *parent = nullptr);
    void doWork(int fd,wechat_msg msg);

signals:
    void resultReady(wechat_msg msg);
};

#endif // WECHAT_H
