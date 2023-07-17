#include "objectdetect.h"
#include "ui_objectdetect.h"
#include <QFile>
#include <QPainter>
#include <QRect>
#include <QFont>
const QString baiduTokenUrl = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2&";
QString client_id = "uXKGo3B1CaqGNjh0VGCOplKN";
QString secret_id = "10aoTo3nGi4PVOGiVFG0hKmlcvpGdkfB";
const QString baiduImageUrl = "https://aip.baidubce.com/rest/2.0/image-classify/%1/%2?access_token=%3";

extern V4l2Api vapi;
ObjectDetect::ObjectDetect(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ObjectDetect)
{
    ui->setupUi(this);
    /**判断是否填充过秘钥**/
    Keypadding = true;
//    detecKey();
    on_comboBox_activated(0);
}

ObjectDetect::~ObjectDetect()
{
    delete ui;
}


void ObjectDetect::on_openBt_clicked()
{
    if(cameraTorF) return;
    cameraTorF = true;
    if(picTorF == false){
        vapi.open();
        vapi.start();
    }
    picTorF = false;
    connect(&vapi, &V4l2Api::sendImage, this, &ObjectDetect::recvImage);
    qDebug() << "connect sucessus!";
    qDebug() << " vapi.start();";
}

void ObjectDetect::on_closeBt_clicked()
{
    ui->label->clear();
    cameraTorF = false;
    disconnect(&vapi, &V4l2Api::sendImage, this, &ObjectDetect::recvImage);
    qDebug() << "disconnect";
    vapi.close();
    qDebug() << " vapi.close();";
}
void ObjectDetect::recvImage(QImage image)
{
    Saveimage = image;
    QPixmap mmp = QPixmap::fromImage(image);
    ui->label->setPixmap(mmp);
}

void ObjectDetect::on_saveBt_clicked()
{
    if(cameraTorF == false)
    {
         QMessageBox::warning(this, "警告", "请先采集图像");
         return ;
    }
    picTorF = true;
    disconnect(&vapi, &V4l2Api::sendImage, this, &ObjectDetect::recvImage);
    cameraTorF = false;

    Saveimage.save("./pic.jpg","JPG",100);
    ui->label->setPixmap(QPixmap::fromImage(Saveimage));
}

void ObjectDetect::on_recognitionBt_clicked()
{
//    qDebug()<<baiduImageUrl;
    ui->textEdit->clear();
    ui->label_3->clear();
    ui->label_4->clear();
    if(Keypadding ==false)
    {
        QMessageBox::warning(this, "警告", "请先填充秘钥");
        return ;
    }
    if(picTorF == false)
    {
         QMessageBox::warning(this, "警告", "请先拍照保存图片");
         return ;
    }
    picTorF = false;
    QByteArray img = IamgeProcess::imageBaseTo64ToUrlEncode("pic.jpg");    //image=xxxxxxx
    QByteArray imgData = "image=" + img;               //body
    //获取access_token
    QByteArray replyData;                 //保存回复信息

    QString url = QString(baiduTokenUrl).arg(client_id).arg(secret_id);

    QMap<QString, QString> header;        //封装头部信息
    header.insert(QString("Content-Type"), QString("application/x-www-form-urlencoded"));
    bool result = Http::post_sync(imgUrl, header, imgData, replyData);
    if (result)
    {
        QJsonObject obj = QJsonDocument::fromJson(replyData).object();
        QJsonValue val = obj.value("result");
        qDebug()<< obj;
        if(ui->comboBox->currentIndex() == 1){
            QJsonObject first = val.toObject();
            int mleft = first.value("left").toInt();
            int mtop = first.value("top").toInt();
            int mwidth = first.value("width").toInt();
            int mheight = first.value("height").toInt();
            QString str = "left : " + QString::number(mleft) +"\ntop : " + QString::number(mtop)+\
                    "\nwidth : "+QString::number(mwidth) + "\nheight : " + QString::number(mheight);
            ui->textEdit->setText(str);
            ui->label_3->clear();
            ui->label_4->clear();
            QRect rect(mleft,mtop,mwidth,mheight);
            QPainter p(&Saveimage);
            p.setPen(Qt::red);
            p.drawRect(rect);
            QFont font = p.font();
            font.setPixelSize(60);
            p.setFont(font);
            ui->label->setPixmap(QPixmap::fromImage(Saveimage));

            return;
        }
        if (val.isArray())
        {
            if(ui->comboBox->currentIndex() == 2){
                QJsonArray first = val.toArray();
                qsizetype Jsonarr_size = first.size() >= 3 ? 3:first.size();
                qDebug() << "Jsonarr_size = " << first.size();
                qDebug() << "Jsonarr_size = " << Jsonarr_size;
                for(qsizetype i = 0; i < Jsonarr_size; ++i){
                    QJsonValue second = first.at(i);
                    qDebug() << "i:"<<i << ",second JsonValue = " << second;
                    QJsonValue third = second.toObject().value("location");

                    qDebug() << "i:"<<i << ",third JsonValue = " << third;
                    int mleft = third.toObject().value("left").toInt();
                    int mtop = third.toObject().value("top").toInt();
                    int mwidth = third.toObject().value("width").toInt();
                    int mheight = third.toObject().value("height").toInt();
                    QString str = QString::number(i+1)+" : " + second.toObject().value("name").toString();
                    ui->textEdit->append(str);
                    QRect rect(mleft,mtop,mwidth,mheight);
                    QPainter p(&Saveimage);
//                    QPainter p;
                    if(i==0)p.setPen(Qt::red);
                    else if(i==1)p.setPen(Qt::blue);
                    else if(i==2)p.setPen(Qt::green);
                    p.drawRect(rect);
//                    p.drawImage(rect,Saveimage);
                    QFont font = p.font();
                    font.setPixelSize(60);
                    p.setFont(font);
                }
                ui->label_3->clear();
                ui->label_4->clear();
                ui->label->setPixmap(QPixmap::fromImage(Saveimage));
                return;
            }
            for(int i=0;i<3;i++)
            {
                QJsonValue first = val.toArray().at(i);
                if (first.isObject())
                {
                    if(ui->comboBox->currentIndex() > 2){
                        QString name = first.toObject().value("name").toString();
                        QString score = first.toObject().value("score").toString();
                        ui->textEdit->append(QString(QString::number(i+1)).append(". 名称: ").append(name).append("\n置信度: ").append(score));
                    }else if(ui->comboBox->currentIndex() == 0){
                        QString name = first.toObject().value("keyword").toString();
                        QString root = first.toObject().value("root").toString();
                        QString score = first.toObject().value("score").toString();
                        double sscore = first.toObject().value("score").toDouble();
                        qDebug() << "score : " <<score << ",sscore = " << sscore;
                        ui->textEdit->append(QString(QString::number(i+1)).append(". 名称: ")\
                                      .append(name).append("\n主体: ").append(root)
                                             .append("\n置信度: ").append(QString::number(sscore)));
                    }
                }
            }
//            显示最终结果
            ui->label_3->setText("经图像分析最可能为");
            if(ui->comboBox->currentIndex() > 2)
            ui->label_4->setText(val.toArray().at(0).toObject().value("name").toString());
            else if(ui->comboBox->currentIndex() == 0)
                ui->label_4->setText(val.toArray().at(0).toObject().value("keyword").toString());
        }
        else{
            ui->textEdit->append("识别不到，请重新拍照识别");
        }
    }
    else{
        ui->textEdit->append("识别不到，请重新拍照识别");
    }
}

void ObjectDetect::on_comboBox_activated(int index)
{
    Q_UNUSED(index)

    QByteArray img = IamgeProcess::imageBaseTo64ToUrlEncode("pic.jpg");    //image=xxxxxxx
    QByteArray imgData = "image=" + img;               //body
    //获取access_token
    QByteArray replyData;                 //保存回复信息

    QString url = QString(baiduTokenUrl).arg(client_id).arg(secret_id);

    QMap<QString, QString> header;        //封装头部信息
    header.insert(QString("Content-Type"), QString("application/x-www-form-urlencoded"));

    bool result = Http::post_sync(url, header, imgData, replyData);
    if (result)
    {
        QJsonObject obj = QJsonDocument::fromJson(replyData).object();
        accessToken = obj.value("access_token").toString();
    }

    switch (ui->comboBox->currentIndex())
    {
    case 0:
        imgUrl = baiduImageUrl.arg("v2").arg("advanced_general").arg(accessToken);
        break;
    case 1:
        imgUrl = baiduImageUrl.arg("v1").arg("object_detect").arg(accessToken);
        break;
    case 2:
        imgUrl = baiduImageUrl.arg("v1").arg("multi_object_detect").arg(accessToken);
        break;
    case 3:
        imgUrl = baiduImageUrl.arg("v1").arg("animal").arg(accessToken);
        break;
    case 4:
        imgUrl = baiduImageUrl.arg("v2").arg("logo").arg(accessToken);
        break;
    case 5:
        imgUrl = baiduImageUrl.arg("v1").arg("classify/ingredient").arg(accessToken);
        break;
    case 6:
        imgUrl = baiduImageUrl.arg("v1").arg("plant").arg(accessToken);
        break;
    case 7:
        imgUrl = baiduImageUrl.arg("v2").arg("dish").arg(accessToken);
        break;
    case 8:
        imgUrl = baiduImageUrl.arg("v1").arg("redwine").arg(accessToken);
        break;
    case 9:
        imgUrl = baiduImageUrl.arg("v1").arg("currency").arg(accessToken);
        break;
    }
}

void ObjectDetect::on_pushButton_ewm_clicked()
{
    if(picTorF == false)
    {
         QMessageBox::warning(this, "警告", "请先拍照保存图片");
         return ;
    }
//     QZXing zxing;
//     QString imagePth ="./pic.jpg";
//     QImage image(imagePth);
//     QByteArray byte = zxing.decodeImage(image).toUtf8();//该方法返回QString串，标识图片二维码的内容
//     QJsonObject obj = QJsonDocument::fromJson(byte).object();
//     client_id = obj.value("client_id").toString();
//     secret_id = obj.value("secret_id").toString();
//     qDebug()<< "client_id:"<<client_id;
//     qDebug()<< "secret_id:"<<secret_id;
//     if(client_id =="")
//     {
//         QMessageBox::warning(this, "警告", "请重新填充秘钥");
//         on_openBt_clicked();
//         return ;
//     }
//     else
//     {
//         QMessageBox::information(this, "提示", "填充秘钥成功");
//         ui->pushButton_ewm->setText("填充完成");
//         ui->pushButton_ewm->setEnabled(false);
//         Keypadding = true;
//         picTorF = false;
//         on_comboBox_activated(0);
//         on_openBt_clicked();
//     }
//     /**将秘钥保存到本地****/
//     system("touch client_id.txt");
//     system("touch secret_id.txt");
//     QFile client_idFile("./client_id.txt");
//     client_idFile.open(QIODevice::ReadWrite);
//     client_idFile.write(client_id.toUtf8());
//     client_idFile.close();
//     QFile secret_idFile("./secret_id.txt");
//     secret_idFile.open(QIODevice::ReadWrite);
//     secret_idFile.write(secret_id.toUtf8());
//     secret_idFile.close();
}
void ObjectDetect::detecKey()
{
    /**判断是否填充过秘钥**/
    QFile client_idFile("./client_id.txt");
    if(client_idFile.exists()){
        client_idFile.open(QIODevice::ReadWrite);
        QByteArray cli_id = client_idFile.readAll();
        qDebug()<<cli_id;
        client_id = cli_id;
        Keypadding = true;
        client_idFile.close();
    }else{
        Keypadding = false;
    }

    QFile secret_idFile("./secret_id.txt");
    if(secret_idFile.exists()){
        secret_idFile.open(QIODevice::ReadWrite);
        QByteArray sec_id = secret_idFile.readAll();
        qDebug()<<sec_id;
        secret_id = sec_id;
        ui->pushButton_ewm->setEnabled(false);
        ui->pushButton_ewm->setText("填充完成");
        Keypadding = true ;
        secret_idFile.close();
    }else{
        Keypadding = false;
    }
}

void ObjectDetect::on_back_ptn_clicked()
{
    if(cameraTorF) on_closeBt_clicked();
    this->close();
    this->deleteLater();
}
