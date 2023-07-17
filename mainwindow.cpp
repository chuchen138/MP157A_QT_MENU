#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chat = nullptr;
    life = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_chatSimple_ptn_clicked()
{
    chat = new chatSimple;
    chat->show();
}

void MainWindow::on_weather_ptn_clicked()
{
    life = new lifemanager;
    life->show();
}

void MainWindow::on_systemInfo_ptn_clicked()
{
    sysinfo = new SystemInfo;
    sysinfo->show();
}

void MainWindow::on_wifi_ptn_clicked()
{
    mywifi = new MyWifi;
    mywifi->show();

}

void MainWindow::on_music_ptn_clicked()
{
    music = new MusicPlayer;
    music->show();
}

void MainWindow::on_speechRec_ptn_clicked()
{
    speech = new Speech;
    speech->show();
}

void MainWindow::on_objectDetect_ptn_clicked()
{
    objdet = new ObjectDetect;
    objdet->show();
}

void MainWindow::on_faceDetect_ptn_clicked()
{
    scissor = new ImageTest;
    scissor->show();
}
