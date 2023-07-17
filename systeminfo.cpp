#include "ui_systeminfo.h"
#include "sys/statfs.h"
#include "systeminfo.h"

static QStringList func(QString str, QChar ch){
    QList<QString> strlist;
    QString tmp = "";
    for(QChar c : str){
        if(c == ch){
            if(tmp != "") strlist.push_back(tmp);
            tmp = "";
        }else{
            tmp += c;
        }
    }
    QStringList lst(strlist);
    return lst;
}

SystemInfo::SystemInfo(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::SystemInfo)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(pushbuttonSlot()));
}

SystemInfo::~SystemInfo()
{
    delete ui;
}
void SystemInfo::pushbuttonSlot()
{
    InitTimer();
}
void SystemInfo::InitTimer()
{
    monitor_timer__.setSingleShot(false);
    monitor_timer__.start(m_timer_interval__);
    connect(&monitor_timer__, &QTimer::timeout, this, &SystemInfo::timeoutSlot);
}

void SystemInfo::timeoutSlot()
{
//  cat /proc/stat
    get_cpu_usage__ ();
//  iostat -k -d
    get_disk_speed__();
//  cat /proc/net/dev
    get_net_usage__ ();
//  ifconfig eth0|grep 'inet addr'|awk -F '[ :]' '{print $13}' > ipAddr.txt
    get_ipAddr();
//  uname -a > uname.txt
    get_kernelNumber();
}
//获取网络传输速度
bool SystemInfo::get_net_usage__()
{
    QProcess process;
    process.start("cat /proc/net/dev"); //读取文件/proc/net/dev获取网络收发包数量，再除取样时间得到网络速度
    process.waitForFinished();
    process.readLine();
    process.readLine();

    while(!process.atEnd())
    {
        QString str = process.readLine();
        str.replace("\n","");
//        qDebug() << "net1" <<str;
        str.replace(QRegExp("( ){1,}")," ");
//        qDebug() << "net2" <<str;
//        auto lst = str.split(" ");
        QStringList lst = func(str, ' ');
//        qDebug() << "net_end" <<str;
//        qDebug() << "net[1] = " << lst[0];
        if(lst.size() > 12 && lst[0] == "eth0:")
        {
            double recv = 0;
            double send = 0;
            if(lst.size() > 1)
                recv = lst[1].toDouble();
            if(lst.size() > 12)
                send = lst[9].toDouble();
            double recvrate= (recv - m_recv_bytes__) / (m_timer_interval__ / 1000.0);
            double sendrate =(send - m_send_bytes__) / (m_timer_interval__ / 1000.0);
            ui->label_netRecvrate->setText(QString::number(recvrate).append("byte/s"));
            ui->label_netSendrate->setText(QString::number(sendrate).append("byte/s"));
            m_recv_bytes__ = recv;
            m_send_bytes__ = send;
        }
    }
    return true;
}
//获取CPU利用率
bool SystemInfo::get_cpu_usage__()
{
    QProcess process;
    process.start("cat /proc/stat");
    process.waitForFinished();
    QString str = process.readLine();
    str.replace("\n","");
    str.replace(QRegExp("( ){1,}")," ");
//    qDebug() << "cpu" ;
    qDebug() << str;
//    QStringList lst = str.split(" ",Qt::SkipEmptyParts,Qt::CaseSensitive);
    QStringList lst = func(str, ' ');
//    qDebug() << "cpu" ;
    if(lst.size() > 3)
    {
        double use = lst[0].toDouble() + lst[2].toDouble() + lst[3].toDouble();
        double total = 0;
        for(int i = 1;i < lst.size();++i)
            total += lst[i].toDouble();
        if(total - m_cpu_total__ > 0)
        {
            QString cpuRate = QString::number((use - m_cpu_use__) / (total - m_cpu_total__) * 100.0,'f',2).append("%");
            ui->label_cpu->setText(cpuRate);
            m_cpu_total__ = total;
            m_cpu_use__ = use;
            return true;
        }
    }
    return false;
}
//获取读取硬盘速度
bool SystemInfo::get_disk_speed__()
{
    QProcess process;
    process.start("iostat -k -d");
    process.waitForFinished();
    process.readLine();
    process.readLine();
    process.readLine();
    QString str = process.readLine();
    str.replace("\n","");
    str.replace(QRegExp("( ){1,}")," ");
//    auto lst = str.split(" ");
    qDebug() << str;
    QStringList lst = func(str,' ');
    if(lst.size() > 5)
    {
        QString diskread = QString::number((lst[4].toDouble() - m_disk_read__ )/(m_timer_interval__ / 1000.0)).append("kb/s");
        QString diskwrite = QString::number((lst[5].toDouble() - m_disk_write__) / (m_timer_interval__ / 1000.0)).append("kb/s");
        ui->label_diskReadrate->setText(diskread);
        ui->label_diskWriterate->setText(diskwrite);
        m_disk_read__ = lst[4].toDouble();
        m_disk_write__ = lst[5].toDouble();
        return true;
    }
    return false;
}
//获取ip地址
void SystemInfo::get_ipAddr()
{
    char buf[32] = {0};
    system("ifconfig eth0|grep 'inet addr'|awk -F '[ :]' '{print $13}' > ipAddr.txt");
    FILE* fp0 = fopen("ipAddr.txt", "r+");//读写方式打开
    memset(buf, 0, sizeof(buf));
    fgets(buf, sizeof(buf), fp0);
    QString str = buf;
    ui->label_ipAddr->setText(str);
    fclose(fp0);
    system("rm ipAddr.txt");
}
//获取内核版本
void SystemInfo::get_kernelNumber()
{
    char buf[32] = {0};
    system("uname -a > uname.txt");
    FILE* fp0 = fopen("uname.txt", "r+");//读写方式打开
    memset(buf, 0, sizeof(buf));
    fgets(buf, sizeof(buf), fp0);
    QString str = buf;
//    auto lst = str.split("#");
    QStringList lst = func(str,'#');
    ui->label_kernel->setText(lst[0]);
}


void SystemInfo::on_back_ptn_clicked()
{
    this->close();
    this->deleteLater();
}
