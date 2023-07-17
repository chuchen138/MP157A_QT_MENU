#include "mywifi.h"
#include "ui_mywifi.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <QTextStream>
#include <QFile>
#include <QRadioButton>
#include <QDebug>

QString wifiName;
static int j = 0;
MyWifi::MyWifi(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWifi)
{
    ui->setupUi(this);
    Get_Wifi_Name();
}

MyWifi::~MyWifi()
{
    delete ui;
}


void MyWifi::on_connectBTN_clicked()
{
//    添加网络
    system("wpa_supplicant -D nl80211 -i wlan0 -c /etc/wpa_supplicant.conf -B");
    system("wpa_cli -i wlan0 add_network > i.ini");
    if(ui->Wlan1->isChecked())
        {
            ui->Wlan1->setStyleSheet("color:rgb(114, 159, 207);");
            ui->Wlan2->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan3->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan4->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan5->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan6->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan7->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan8->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan9->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan10->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan11->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan12->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan13->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan14->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan15->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan16->setStyleSheet("color:rgb(0, 0, 0);");
            wifiName = ui->Wlan1->text();
            WifiDlg.show();
        }else if(ui->Wlan2->isChecked())
        {
            ui->Wlan1->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan2->setStyleSheet("color:rgb(114, 159, 207);");
            ui->Wlan3->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan4->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan5->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan6->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan7->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan8->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan9->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan10->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan11->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan12->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan13->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan14->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan15->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan16->setStyleSheet("color:rgb(0, 0, 0);");
            wifiName = ui->Wlan2->text();
            WifiDlg.show();
        }else if(ui->Wlan3->isChecked())
        {
            ui->Wlan1->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan2->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan3->setStyleSheet("color:rgb(114, 159, 207);");
            ui->Wlan4->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan5->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan6->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan7->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan8->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan9->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan10->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan11->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan12->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan13->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan14->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan15->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan16->setStyleSheet("color:rgb(0, 0, 0);");
            wifiName = ui->Wlan3->text();
            WifiDlg.show();
        }else if(ui->Wlan4->isChecked())
        {
            ui->Wlan1->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan2->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan4->setStyleSheet("color:rgb(114, 159, 207);");
            ui->Wlan3->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan5->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan6->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan7->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan8->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan9->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan10->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan11->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan12->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan13->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan14->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan15->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan16->setStyleSheet("color:rgb(0, 0, 0);");
            wifiName = ui->Wlan4->text();
            WifiDlg.show();
        }else if(ui->Wlan5->isChecked())
        {
            ui->Wlan1->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan2->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan5->setStyleSheet("color:rgb(114, 159, 207);");
            ui->Wlan3->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan4->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan6->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan7->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan8->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan9->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan10->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan11->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan12->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan13->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan14->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan15->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan16->setStyleSheet("color:rgb(0, 0, 0);");
            wifiName = ui->Wlan5->text();
            WifiDlg.show();
        }else if(ui->Wlan6->isChecked())
        {
            ui->Wlan1->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan2->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan6->setStyleSheet("color:rgb(114, 159, 207);");
            ui->Wlan3->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan4->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan5->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan7->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan8->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan9->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan10->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan11->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan12->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan13->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan14->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan15->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan16->setStyleSheet("color:rgb(0, 0, 0);");
            wifiName = ui->Wlan6->text();
            WifiDlg.show();
        }else if(ui->Wlan7->isChecked())
        {
            ui->Wlan1->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan2->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan7->setStyleSheet("color:rgb(114, 159, 207);");
            ui->Wlan3->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan4->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan5->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan6->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan8->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan9->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan10->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan11->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan12->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan13->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan14->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan15->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan16->setStyleSheet("color:rgb(0, 0, 0);");
            wifiName = ui->Wlan7->text();
            WifiDlg.show();
        }else if(ui->Wlan8->isChecked())
        {
            ui->Wlan1->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan2->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan8->setStyleSheet("color:rgb(114, 159, 207);");
            ui->Wlan3->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan4->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan5->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan6->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan7->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan9->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan10->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan11->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan12->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan13->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan14->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan15->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan16->setStyleSheet("color:rgb(0, 0, 0);");
            wifiName = ui->Wlan8->text();
            WifiDlg.show();
        }else if(ui->Wlan9->isChecked())
        {
            ui->Wlan1->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan2->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan9->setStyleSheet("color:rgb(114, 159, 207);");
            ui->Wlan3->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan4->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan5->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan6->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan7->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan8->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan10->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan11->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan12->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan13->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan14->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan15->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan16->setStyleSheet("color:rgb(0, 0, 0);");
            wifiName = ui->Wlan9->text();
            WifiDlg.show();
        }else if(ui->Wlan10->isChecked())
        {
            ui->Wlan1->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan2->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan10->setStyleSheet("color:rgb(114, 159, 207);");
            ui->Wlan3->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan4->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan5->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan6->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan8->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan9->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan7->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan11->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan12->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan13->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan14->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan15->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan16->setStyleSheet("color:rgb(0, 0, 0);");
            wifiName = ui->Wlan10->text();
            WifiDlg.show();
        }else if(ui->Wlan11->isChecked())
        {
            ui->Wlan1->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan2->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan11->setStyleSheet("color:rgb(114, 159, 207);");
            ui->Wlan3->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan4->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan5->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan6->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan8->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan9->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan10->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan7->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan12->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan13->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan14->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan15->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan16->setStyleSheet("color:rgb(0, 0, 0);");
            wifiName = ui->Wlan11->text();
            WifiDlg.show();
        }else if(ui->Wlan12->isChecked())
        {
            ui->Wlan1->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan2->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan12->setStyleSheet("color:rgb(114, 159, 207);");
            ui->Wlan3->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan4->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan5->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan6->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan8->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan9->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan10->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan11->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan7->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan13->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan14->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan15->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan16->setStyleSheet("color:rgb(0, 0, 0);");
            wifiName = ui->Wlan12->text();
            WifiDlg.show();
        }else if(ui->Wlan13->isChecked())
        {
            ui->Wlan1->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan2->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan13->setStyleSheet("color:rgb(114, 159, 207);");
            ui->Wlan3->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan4->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan5->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan6->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan8->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan9->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan10->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan11->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan12->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan7->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan14->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan15->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan16->setStyleSheet("color:rgb(0, 0, 0);");
            wifiName = ui->Wlan13->text();
            WifiDlg.show();
        }else if(ui->Wlan14->isChecked())
        {
            ui->Wlan1->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan2->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan14->setStyleSheet("color:rgb(114, 159, 207);");
            ui->Wlan3->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan4->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan5->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan6->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan8->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan9->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan10->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan11->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan12->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan13->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan7->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan15->setStyleSheet("color:rgb(0, 0, 0);");
            ui->Wlan16->setStyleSheet("color:rgb(0, 0, 0);");
            wifiName = ui->Wlan14->text();
            WifiDlg.show();
        }else if(ui->Wlan15->isChecked())
        {
        ui->Wlan1->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan2->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan15->setStyleSheet("color:rgb(114, 159, 207);");
        ui->Wlan3->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan4->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan5->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan6->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan8->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan9->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan10->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan11->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan12->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan13->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan14->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan7->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan16->setStyleSheet("color:rgb(0, 0, 0);");
            wifiName = ui->Wlan15->text();
            WifiDlg.show();
        }else if(ui->Wlan16->isChecked())
        {
        ui->Wlan1->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan2->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan16->setStyleSheet("color:rgb(114, 159, 207);");
        ui->Wlan3->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan4->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan5->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan6->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan8->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan9->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan10->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan11->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan12->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan13->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan14->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan15->setStyleSheet("color:rgb(0, 0, 0);");
        ui->Wlan7->setStyleSheet("color:rgb(0, 0, 0);");
            wifiName = ui->Wlan16->text();
            WifiDlg.show();
        }else
        {
            QMessageBox::warning(this,"Warnning","请选择要连接的网络",QMessageBox::Yes);
        }
}
void MyWifi::Get_Wifi_Name()
{
    system("wpa_supplicant -D nl80211 -i wlan0 -c /etc/wpa_supplicant.conf -B");
    system("wpa_cli -i wlan0 scan");
    system("wpa_cli -i wlan0 scan_results > ./wifilist");
    system("cat wifilist |awk -F'\t' '{print $5}'> wifiname.txt");
//    usleep(50000);
    QString fileName = "./wifiname.txt";
    QFile file(fileName);
    j = 0;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"Warnning","can't open",QMessageBox::Yes);
    }
    QTextStream in(&file);
    QString str;
    while (j<=16)
    {
         j++;
        str = in.readLine();
        qDebug()<<str;
        if(str.isEmpty())
        {
            str = "无法连接";
        }
        switch (j-1)
        {
        case 1:ui->Wlan1->setVisible(true);
            ui->Wlan1->setText(str);
            break;
        case 2:ui->Wlan2->setVisible(true);
            ui->Wlan2->setText(str);
            break;
        case 3:ui->Wlan3->setVisible(true);
            ui->Wlan3->setText(str);
            break;
        case 4:ui->Wlan4->setVisible(true);
            ui->Wlan4->setText(str);
            break;
        case 5:ui->Wlan5->setVisible(true);
            ui->Wlan5->setText(str);
            break;
        case 6:ui->Wlan6->setVisible(true);
            ui->Wlan6->setText(str);
            break;
        case 7:ui->Wlan7->setVisible(true);
            ui->Wlan7->setText(str);
            break;
        case 8:ui->Wlan8->setVisible(true);
            ui->Wlan8->setText(str);
            break;
        case 9:ui->Wlan9->setVisible(true);
            ui->Wlan9->setText(str);
            break;
        case 10:ui->Wlan10->setVisible(true);
            ui->Wlan10->setText(str);
            break;
        case 11:ui->Wlan11->setVisible(true);
            ui->Wlan11->setText(str);
            break;
        case 12:ui->Wlan12->setVisible(true);
            ui->Wlan12->setText(str);
            break;
        case 13:ui->Wlan13->setVisible(true);
            ui->Wlan13->setText(str);
            break;
        case 14:ui->Wlan14->setVisible(true);
            ui->Wlan14->setText(str);
            break;
        case 15:ui->Wlan15->setVisible(true);
            ui->Wlan15->setText(str);
            break;
        case 16:ui->Wlan16->setVisible(true);
            ui->Wlan16->setText(str);
            break;
        default:break;
        }
    }
    file.close();
}

void MyWifi::on_connectBTN_2_clicked()
{
    Get_Wifi_Name();
     QMessageBox::information(this,tr("Connect information"), tr("成功!"));
}


void MyWifi::on_back_ptn_clicked()
{
    this->close();
    this->deleteLater();
}
