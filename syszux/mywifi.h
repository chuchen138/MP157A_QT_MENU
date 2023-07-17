#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "set_wifi.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     Set_Wifi WifiDlg;
     void Get_Wifi_Name();
private slots:
    void on_connectBTN_clicked();

    void on_connectBTN_2_clicked();

private:
    Ui::MainWindow *ui;
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
