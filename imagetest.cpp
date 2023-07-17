#include "imagetest.h"
#include "ui_imagetest.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QUrlQuery>
#include <QByteArray>
#include <QPainter>
#include <QCameraInfo>
#include <QComboBox>
#include <QRandomGenerator>

extern V4l2Api vapi;

ImageTest::ImageTest(QWidget *parent)
    : MyNetManager(parent)
    , ui(new Ui::ImageTest)
{
    ui->setupUi(this);
    this->resize(1060,700);

    cameraInfoList = QCameraInfo::availableCameras();
    for(const QCameraInfo &tmpCam:cameraInfoList){
        ui->comboBox->addItem(tmpCam.description());
    }
//    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),this,&ImageTest::pickCamera);

    connect(&vapi, &V4l2Api::sendImage, this, &ImageTest::showCamera);
    vapi.open();
    vapi.start();
    qDebug() << "ok";
    connect(ui->pushButton,&QPushButton::clicked,this, &ImageTest::beginGame);

    ui->game_label->setText("猜拳游戏");
    // 界面布局
//    QVBoxLayout *vboxl = new QVBoxLayout;
//    vboxl->addWidget(ui->game_label);
//    vboxl->addWidget(ui->label);
//    vboxl->addWidget(ui->pushButton);

//    QVBoxLayout *vboxr = new QVBoxLayout;
////    vboxr->addWidget(finder);
//    vboxr->addWidget(ui->comboBox);
//    vboxr->addWidget(ui->textBrowser);
//    vboxr->addWidget(ui->back_ptn);

//    QHBoxLayout *hbox = new QHBoxLayout(this);
//    hbox->addLayout(vboxl);
//    hbox->addLayout(vboxr);
//    this->setLayout(hbox);

    // 定时器 : 利用定时器不断刷新界面
//    timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, &ImageTest::takePicture);
//    timer->start(TIMER_REFRESH);

    /*    设置定时器不断刷新界面     */

    gameTimer = new QTimer(this);

    // 文本更新
    connect(this,&MyNetManager::faceInfoOK,this,[&](const QString& f, int yourhand){
        ui->textBrowser->setText(f);
        if(yourhand == -1){
            titleGameStr="你未出拳，请重试~";
            ui->game_label->setText(titleGameStr);
            ui->pushButton->setEnabled(true);
            return;
        }
        int ret = (yourhand-computerHand+3)%3;
        QString result = ret==0?"平局":(ret==1?"你输了！":"你赢了！");
        titleGameStr.clear();
        titleGameStr.append("电脑出拳:")
                .append(computerHand==0?"石头":(computerHand==1?"剪刀":"布"))
                .append(",你的出拳：")
                .append(yourhand==0?"石头":(yourhand==1?"剪刀":"布"))
                .append("。最后结果：")
                .append(result);
        ui->game_label->setText(titleGameStr);
        ui->pushButton->setEnabled(true);
    });
    connect(gameTimer,&QTimer::timeout, this, &ImageTest::Analy);
}
// 触发器控制
void ImageTest::showCamera(QImage img){
    this->SaveImg = img;
    ui->label->setPixmap(QPixmap::fromImage(img));
}

// 按键按下
void ImageTest::beginGame(){
    ui->pushButton->setEnabled(false);
    gameTimer->start(1000);
    cnt = 3;
    titleGameStr = "准备出拳 : " + QString::number(cnt);
    ui->game_label->setText(titleGameStr);
}

void ImageTest::Analy(){
    if(--cnt > 0){
        titleGameStr = "准备出拳 : "+ QString::number(cnt);
        ui->game_label->setText(titleGameStr);
    }else{
        computerHand = QRandomGenerator::global()->generate()%3;
        gameTimer->stop();
        titleGameStr.clear();
        titleGameStr.append("出拳！！！电脑出拳:")
                .append(computerHand==0?"石头":(computerHand==1?"剪刀":"布"))
                .append(",你的出拳：分析中...");
        ui->game_label->setText(titleGameStr);
        beginFaceDetect(this->SaveImg);
    }
}

ImageTest::~ImageTest()
{
    qDebug() << "~ImageTest";
    vapi.close();
    qDebug() << "vapi.close()";
    delete gameTimer;
    delete ui;
}

//void ImageTest::pickCamera(int idx){
//    // qDebug() <<idx << " : " << cameraInfoList.at(idx);
//    timer->stop();

//    camera->stop();
//    camera = new QCamera(cameraInfoList.at(idx));
//    camera->setViewfinder(finder);
//    camera->setCaptureMode(QCamera::CaptureStillImage);

//    // 触发器
//    connect(capture, &QCameraImageCapture::imageCaptured,\
//            this, &ImageTest::showCamera);
//    capture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
//    camera->start();
//    timer->start(TIMER_REFRESH);
//}

void ImageTest::on_back_ptn_clicked()
{
    this->close();
    this->deleteLater();
}
