#ifndef OBJECTDETECT_H
#define OBJECTDETECT_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include "v4l2api.h"
#include "iamgeprocess.h"
#include "http.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
//#include <QZXing>
QT_BEGIN_NAMESPACE
namespace Ui { class ObjectDetect; }
QT_END_NAMESPACE

class ObjectDetect : public QMainWindow
{
    Q_OBJECT

public:
    ObjectDetect(QWidget *parent = nullptr);
    ~ObjectDetect();
private slots:
    void on_openBt_clicked();
    void on_closeBt_clicked();
    void recvImage(QImage image);
    void on_saveBt_clicked();
    void on_recognitionBt_clicked();
    void on_comboBox_activated(int index);
    void on_pushButton_ewm_clicked();

    void on_back_ptn_clicked();

private:
    Ui::ObjectDetect *ui;
//    V4l2Api vapi;
    QImage Saveimage;
    bool cameraTorF = false;
    bool picTorF = false;
    bool Keypadding = false;
    QString accessToken;
    QString imgUrl;
    void detecKey();
};
#endif // MAINWINDOW_H
