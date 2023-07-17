#include "mynetmanager.h"
#include "mynetmanager.h"
#include <QUrl>
#include <QUrlQuery>
#include <QByteArray>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QBuffer>
#include <QJsonArray>
#include "worker.h"
using namespace std;

MyNetManager::MyNetManager(QWidget *parent)
    : QWidget(parent)
{
    // 网络操作
    m_pManager = new QNetworkAccessManager();
    imgManager = new QNetworkAccessManager();

//    qDebug() << m_pManager->supportedSchemes();

    // 拼接url https://aip.baidubce.com/oauth/2.0/token
//    QUrl url("https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials\
//&client_id=wgGoKIOmMhr1O180GDRY7PEy&client_secret=I1ye3N6HvwpzPi55xBhv57AaEsyFaucF");
    QUrl url("https://aip.baidubce.com/oauth/2.0/token");
    QUrlQuery query;
    query.addQueryItem("grant_type","client_credentials");
    query.addQueryItem("client_id","wgGoKIOmMhr1O180GDRY7PEy");
    query.addQueryItem("client_secret","I1ye3N6HvwpzPi55xBhv57AaEsyFaucF");
    url.setQuery(query);

//    qDebug() << url;
//    // 是否支持ssl
//    if(QSslSocket::supportsSsl()){
//        qDebug() << "支持 ssl";
//    }else{
//        qDebug() << "不支持 ssl";
//    }

    sslConfig = QSslConfiguration::defaultConfiguration();
    sslConfig.setPeerVerifyMode(QSslSocket::QueryPeer);
    sslConfig.setProtocol(QSsl::TlsV1_2);

    // 组装请求
    QNetworkRequest req;
    req.setUrl(url);
    req.setSslConfiguration(sslConfig);

    // 发送get请求
    connect(m_pManager, &QNetworkAccessManager::finished,this, &MyNetManager::tokenReply);
    // token 24.ec08bad34b11a9b4157b069d13987a7a.2592000.1672936397.282335-28880511
    m_pManager->get(req);
    connect(imgManager, &QNetworkAccessManager::finished,this, &MyNetManager::imgReply);

}

void MyNetManager::tokenReply(QNetworkReply *reply){
    if(reply->error() != QNetworkReply::NoError){
        qDebug() << "error : "<< reply->errorString();
        return;
    }
    // 正常应答
    const QByteArray reply_data = reply->readAll();
    // json解析
    QJsonParseError jsonErr;
    QJsonDocument doc = QJsonDocument::fromJson(reply_data, &jsonErr);

    // 解析成功
    if(jsonErr.error == QJsonParseError::NoError){
        QJsonObject obj =  doc.object();
        // qDebug() << "all return " <<obj;
        if(obj.contains("access_token")){
            accessToken = obj.take("access_token").toString();
        }
        qDebug() << "access_token : " << accessToken;
    }else{
        qDebug() << "json error " << jsonErr.errorString();
    }
    reply->deleteLater();
}

void MyNetManager::beginFaceDetect(QImage img){
    childThread = new QThread(this);
    Worker *worker = new Worker;
    qDebug() << "beginFaceDetect";
    worker->moveToThread(childThread);
    qDebug() << "moveToThread";
    connect(this, &MyNetManager::beginFaceDetectwork,worker, &Worker::doWork);
    connect(worker, &Worker::resultReady,this, [&](QNetworkRequest req,QByteArray postData, QThread *overThread){
        qDebug() << "resultReady over";
        imgManager->post(req, postData);
        qDebug() << "resultReady over";
        overThread->exit();
        qDebug() << "overThread is stop";
//        overThread->wait();
        qDebug() << "overThread is stop";
    });
    qDebug() << "connect";
    connect(childThread, &QThread::finished, worker,&QObject::deleteLater);
    childThread->start();
    qDebug() << "childThread is atart";
    emit beginFaceDetectwork(img, accessToken,sslConfig,childThread);
    qDebug() << "childThread is start";
}


void MyNetManager::imgReply(QNetworkReply *reply){
    if(reply->error() != QNetworkReply::NoError){
        qDebug() << reply->errorString();
        return;
    }
    const QByteArray replyData = reply->readAll();
    qDebug() << "imgReply face information replyData : "<<replyData;
    faceInfo.clear();
    QJsonParseError jsonErr;
    int yourhand = -1;
    QJsonDocument doc = QJsonDocument::fromJson(replyData, &jsonErr);
    if (jsonErr.error==QJsonParseError::NoError ){
        //取出最外层的j son
        QJsonObject obj=doc.object();

        if (obj.contains("result_num")){
            int result_num =obj.take("result_num").toInt() ;
            //取出人脸列表
            if(obj.contains("result")){
                QJsonArray resultList = obj.take("result").toArray();
                // 取出第一-张人脸信息
                for(int i = 0; i < result_num; i++){
                    QJsonObject handobj = resultList.at(i).toObject();
                    if(handobj.contains("classname")){
                        QString handClass = handobj.take("classname").toString();
                        faceInfo.append(QString::number(i+1)).append('.').append(handClass).append("\r\n");

                        if(handClass == "Fist"){
                            yourhand = 0;
                            break;
                        }else if(handClass == "Two"){
                            yourhand = 1;
                            break;
                        }else if(handClass == "Five"){
                            yourhand = 2;
                            break;
                        }
                    }
                }
//                qDebug() << "handInfo = " << faceInfo;
                emit faceInfoOK(faceInfo, yourhand);
            }else{
                qDebug() << "no posture";
            }
        }else{
            qDebug() << "no back result";
        }
    }else{
        qDebug() << "JSON ERROR " << jsonErr.errorString();
    }

    reply->deleteLater();
}


MyNetManager::~MyNetManager()
{

}
