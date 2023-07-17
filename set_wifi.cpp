#include "set_wifi.h"
#include "ui_set_wifi.h"
#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>
Set_Wifi::Set_Wifi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Set_Wifi)
{ 
    ui->setupUi(this);
    password_edit = new My_lineEdit(this);
    password_edit->setObjectName("password");
    password_edit->setGeometry(QRect(100, 100, 150, 50));
    syszuxpinyin =new SyszuxPinyin();
    connect(password_edit,SIGNAL(send_show(QString)),this,SLOT(keyboardshow(QString)));
    connect(syszuxpinyin,SIGNAL(sendPinyin(QString)),this,SLOT(confirmString(QString)));
}

Set_Wifi::~Set_Wifi()
{
    delete ui;
}
void Set_Wifi::keyboardshow(QString data)
{

    syszuxpinyin->lineEdit_window->setText(data);
    syszuxpinyin->resize(800,330);
    syszuxpinyin->move(100,280);
    syszuxpinyin->show();

}
void  Set_Wifi::confirmString(QString gemfield)
{
   password_edit->setText(gemfield);
}
void Set_Wifi::on_pushButton_clicked()
{
    char set_ssid[64];
    char set_password[64];
    char select_wlan[64];

    if (password_edit->text().isEmpty())
    {
        QMessageBox::warning(this,tr("Connect information"), tr("密码不能为空"));
    }
    else
    {

        int i =get_i();
        sprintf(set_ssid,"wpa_cli -i wlan0 set_network %d ssid '\"%s\"'",i,wifiName.toLatin1().data());
        sprintf(set_password, "wpa_cli -i wlan0 set_network %d psk '\"%s\"' > TorF.ini",i,password_edit->text().toLatin1().data());
        sprintf(select_wlan, "wpa_cli -i wlan0 select_network %d ",i);
        system(set_ssid);
        system(set_password);
        system("wpa_cli -i wlan0 list_network");
        system(select_wlan);
        system("wpa_supplicant -B -c wifi.conf -i wlan0");
        qDebug()<< get_TorF().data()->toUpper();
        if(get_TorF().data()->toUpper()=="F")
        {
            QMessageBox::warning(this,tr("Connect information"), tr("密码错误"));
            return ;
        }
        system("udhcpc -i wlan0 -B");
        char echo_1[64];
        char echo_2[64];
        sprintf(echo_1,"echo \"nameserver 114.114.114.114\" > /etc/resolv.conf");
        system(echo_1);
        sprintf(echo_2,"echo \"nameserver 8.8.8.8\" > /etc/resolv.conf");
        system(echo_2);
        close();
        QMessageBox::information(this,tr("Connect information"), tr("连接成功"));
    }

}
//读取i的值
int Set_Wifi::get_i()
{
    char buf[32] = {0};
    FILE* fp0 = fopen("i.ini", "r+");//读写方式打开
    memset(buf, 0, sizeof(buf));
    fgets(buf, sizeof(buf), fp0);
    QString str = buf;
    return str.toInt();
}
//验证是否登陆成功
QString Set_Wifi::get_TorF()
{
    char buf[32] = {0};
    FILE* fp = fopen("TorF.ini", "r+");//读写方式打开
    memset(buf, 0, sizeof(buf));
    fgets(buf, sizeof(buf), fp);
    QString str = buf;
    return str;
}
void Set_Wifi::on_pushButton_2_clicked()
{
    close();
}

