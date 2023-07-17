#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QWidget>
#include <QProcess>
#include <QDebug>
#include <QTimer>
#include <QString>
#include <QStringList>
#include <QList>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <Qt>
#include <QChar>
#include <QMainWindow>
//QT_BEGIN_NAMESPACE
namespace Ui { class SystemInfo; }
//QT_END_NAMESPACE

class SystemInfo : public QMainWindow
{
    Q_OBJECT

public:
    SystemInfo(QMainWindow *parent = nullptr);
    ~SystemInfo();
    void timeoutSlot();
    bool get_cpu_usage__ ();
    bool get_disk_speed__();
    bool get_net_usage__ ();
    void get_ipAddr();
    void get_kernelNumber();
private slots:
    void pushbuttonSlot();
    void on_back_ptn_clicked();

private:
    Ui::SystemInfo *ui;
    int m_timer_interval__ = 5000;
    QTimer monitor_timer__;
    double m_recv_bytes__ = 0;
    double m_send_bytes__ = 0;
    double m_cpu_total__ = 0;
    double m_cpu_use__ = 0;
    double m_disk_read__ = 0;
    double m_disk_write__ = 0;
    void InitTimer();
};


#endif // SYSTEMINFO_H
