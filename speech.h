#ifndef SPEECH_H
#define SPEECH_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include "http.h"
#include <QHostInfo>
#include <linux/input.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <QAudioDeviceInfo>
#include <QMessageBox>
#include <QAudioInput>

//    获取Access Token
const QString baiduTokenUrl = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2&";
const QString client_id = "ve9EyozwZNQBjHaO5d98H1FS";
const QString client_secret = "3X1e3BEfsTP2N1mtBZ1dO5pOmzXi1zVl";
//    语音识别url
const QString baiduSpeechUrl = "https://vop.baidu.com/server_api?dev_pid=1537&cuid=%1&token=%2";

namespace Ui {
class Speech;
}

class Speech : public QWidget
{
    Q_OBJECT

public:
    explicit Speech(QWidget *parent = nullptr);
    ~Speech();
    QString speechIdentify(QString fileName);

private slots:
    void on_pushButton_video_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_video_released();
void RecorderStart(QString fileName);
void RecorderEnd();

    void on_back_ptn_clicked();

    void on_pushButton_video_pressed();

private:
    QFile *outFile;//录音时的变量
    QAudioInput *my_audio;//录音时的变量
    QAudioFormat audioFormat;//录音时的变量
    QString getJsonValue(QByteArray ba,QString key);
    void audioCtrl(QString text);
    QString temCollect();
    QString humCollect();
    int read_sysfs_float(const char *device, const char *filename, float *val);
    int read_sysfs_int(const char *device, const char *filename, int *val);
private:
    Ui::Speech *ui;
};

#endif // SPEECH_H
