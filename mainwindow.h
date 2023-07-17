#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chatsimple.h"
#include "lifemanager.h"
#include "systeminfo.h"
#include "mywifi.h"
#include "musicplayer.h"
#include "speech.h"
#include "objectdetect.h"
#include "imagetest.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_chatSimple_ptn_clicked();

    void on_weather_ptn_clicked();

    void on_systemInfo_ptn_clicked();

    void on_wifi_ptn_clicked();

    void on_music_ptn_clicked();

    void on_speechRec_ptn_clicked();

    void on_objectDetect_ptn_clicked();

    void on_faceDetect_ptn_clicked();

private:
    Ui::MainWindow *ui;
    chatSimple *chat;
    lifemanager *life;
    SystemInfo *sysinfo;
    MyWifi *mywifi;
    MusicPlayer *music;
    Speech *speech;
    ObjectDetect *objdet;
    ImageTest *scissor;
};
#endif // MAINWINDOW_H
