#include "wechat.h"


WorkerMsg::WorkerMsg(QObject *parent)
    : QObject{parent}
{

}
void WorkerMsg::doWork(int fd,wechat_msg msg){
    qDebug() << "I'm doing work";
    int ret = recv(fd,&msg,sizeof(msg),0);
    if(ret <= 0){
        msg.type = -2;
    }
    qDebug() << "work over";
    qDebug() << "type = " << msg.type;
    emit resultReady(msg);
}
