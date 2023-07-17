#include "worker.h"

Worker::Worker(QObject *parent)
    : QObject{parent}
{

}


void Worker::doWork(QImage img,QString accessToken,QSslConfiguration sslConfig,QThread* overThread){
    QByteArray ba;
    qDebug() << "dowork over";
    QBuffer buff(&ba);
    qDebug() << "dowork over";
    img.save(&buff, "jpg");
    QByteArray postData("image=");
    postData.append(ba.toBase64().toPercentEncoding());
    qDebug() << "dowork over";
    QUrl url("https://aip.baidubce.com/rest/2.0/image-classify/v1/gesture");
    QUrlQuery query;
    query.addQueryItem("access_token", accessToken);
    url.setQuery(query);
    qDebug() << "dowork over";
    // 组装请求
    QNetworkRequest req;

    req.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
    req.setUrl(url);
    req.setSslConfiguration(sslConfig);
    qDebug() << "dowork over";
    emit resultReady(req, postData,overThread);
    qDebug() << "dowork really over";
}



