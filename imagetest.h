#ifndef IMAGETEST_H
#define IMAGETEST_H

#include <QWidget>
#include <QCamera>
#include <QTimer>
#include <QCameraImageCapture>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QSslConfiguration>
#include <QNetworkReply>
#include "mynetmanager.h"
#include "v4l2api.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ImageTest; }
QT_END_NAMESPACE

#define TIMER_REFRESH 50

class ImageTest : public MyNetManager
{
    Q_OBJECT
public slots:
    void showCamera(QImage img); // 触发器控制
//    void takePicture();     // 定时器控制
    void beginGame();
    void Analy();       // 按键控制
//    void pickCamera(int idx);
//    void imgReply(QNetworkReply *reply);
//    void beginFaceDetect();
public:
    ImageTest(QWidget *parent = nullptr);
    ~ImageTest();

private slots:
    void on_back_ptn_clicked();

private:
    Ui::ImageTest *ui;
    QList<QCameraInfo> cameraInfoList;
    QTimer *gameTimer;
    QImage SaveImg;
    QString titleGameStr;
    int cnt;
    int computerHand;
//    V4l2Api vapi;
//    QImage Saveimage;
};
#endif // IMAGETEST_H
