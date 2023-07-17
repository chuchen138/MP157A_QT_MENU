#ifndef MYWIFI_H
#define MYWIFI_H

#include <QMainWindow>
#include "set_wifi.h"
#include <QDebug>
namespace Ui {
class MyWifi;
}

class MyWifi : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyWifi(QMainWindow *parent =  nullptr);
    ~MyWifi();
     Set_Wifi WifiDlg;
     void Get_Wifi_Name();
private slots:
    void on_connectBTN_clicked();

    void on_connectBTN_2_clicked();

    void on_back_ptn_clicked();

private:
    Ui::MyWifi *ui;
};

#endif // MAINWINDOW_H
/**
     * @brief system <getWifiName>
     *
    system("wpa_supplicant -D nl80211 -i wlan0 -c /etc/wpa_supplicant.conf -B");
    system("wpa_cli -i wlan0 scan");
    system("wpa_cli -i wlan0 scan_results > ./wifilist");
    system("cat wifilist |awk -F'\t' '{print $5}'> wifiname.txt");

    // 添加网络
    system("wpa_supplicant -D nl80211 -i wlan0 -c /etc/wpa_supplicant.conf -B");
    system("wpa_cli -i wlan0 add_network > i.ini");
     */
