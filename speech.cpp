#include "speech.h"
#include "ui_speech.h"

Speech::Speech(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Speech)
{
    ui->setupUi(this);
}

Speech::~Speech()
{
    delete ui;
}

QString Speech::speechIdentify(QString fileName)
{
//    获取Access Token
    QString tokenUrl =QString(baiduTokenUrl).arg(client_id).arg(client_secret);
//    Http my_http;
    QMap<QString,QString>header;
    header.insert(QString("Content-Type"),QString("audio/pcm;rate=16000"));
    QByteArray requestData;//请求内容
    QByteArray replyData;//url返回内容

   qDebug()<<tokenUrl;
    bool result = Http::post_sync(tokenUrl,header,requestData,replyData);
    if(result) {
        QString key = "access_token";
        QString accessToken =getJsonValue(replyData,key);
        qDebug()<< "speech accessToken = " << accessToken;
        //    语音识别
        QString speechUrl = QString(baiduSpeechUrl).arg(QHostInfo::localHostName()).arg(accessToken);
        QFile file;
        file.setFileName(fileName);
        file.open(QIODevice::ReadOnly);
        requestData = file.readAll();
        file.close();


        replyData.clear();
//        再次发起请求
        result = Http::post_sync(speechUrl,header,requestData,replyData);
         if(result) {
             QString key = "result";
             QString retText =getJsonValue(replyData,key);
//             qDebug()<< "replyData = " <<replyData;
             return retText;
         }
         else{
             return NULL;
         }
    }
    else {
        return  "error";
    }
}
QString Speech::getJsonValue(QByteArray ba,QString key)
{
    QJsonParseError parseError;
    QJsonDocument jsondocument = QJsonDocument::fromJson(ba,&parseError);
    if(parseError.error ==QJsonParseError::NoError)
    {
        if(jsondocument.isObject())
        {
            QJsonObject jsonObject = jsondocument.object();
//return jsonObject.keys().last();

            if(jsonObject.contains(key)){
                QJsonValue jsonvalue = jsonObject.value(key);
                if(jsonvalue.isString())
                    return jsonvalue.toString();
                else if(jsonvalue.isArray()){
                    QJsonArray arr = jsonvalue.toArray();
                    QJsonValue val =arr.at(0);
                    return val.toString();
                }

            }

        }
    }
    return "";

}

void Speech::on_pushButton_video_clicked()
{
//    system("arecord -D record_codec -f S16_LE -d 3 1.wav");
//    ui->label->setStyleSheet("border-image: url(:/images出行助手/开始说话.png);");
}


void Speech::on_pushButton_video_pressed()
{
    RecorderStart("./1.pcm");
    ui->label->setStyleSheet("border-image: url(:/images出行助手/开始说话.png);");
//    ui->pushButton_video->setText("松开识别");
}

void Speech::on_pushButton_video_released()
{
    ui->label->setStyleSheet("border-image: url(:/images出行助手/松开识别.png);");
    RecorderEnd();
    QString text = speechIdentify("1.pcm");

    audioCtrl(text);
    ui->label_yuyin->setText(text);
}


void Speech::on_pushButton_clear_clicked()
{
    ui->label_yuyin->clear();
}

///**********************
// * 开始录音
//**********************/
void Speech::RecorderStart(QString fileName)
{
    QAudioDeviceInfo device = QAudioDeviceInfo::defaultInputDevice();
    if(device.isNull())
    {
        QMessageBox::warning(NULL,"QAudioDeviceInfo","录音设备不存在");
        return;
    }
//    设置通道数
    audioFormat.setChannelCount(1);
//    设置编码
    audioFormat.setCodec("audio/pcm");
//    设置采样频率
    audioFormat.setSampleRate(8000);
//    设置位深
    audioFormat.setSampleSize(16);
//    判断设备是否支持该格式
    if(!device.isFormatSupported(audioFormat)){ //当前使用设备是否支持
        qDebug() << "isFormatSupported don't support";
        audioFormat = device.nearestFormat(audioFormat); //转换为最接近格式
    }else{
        qDebug() << "isFormatSupported support";
    }
//    qDebug() << audioFormat.codec() << Qt::endl;
//    ui->label_yuyin->setText(QString::number(audioFormat.channelCount()));
//    qDebug() << audioFormat.sampleRate() << Qt::endl;
//    qDebug() << audioFormat.sampleSize() << Qt::endl;
//    qDebug() << audioFormat.sampleType() << Qt::endl;
//    qDebug() << audioFormat.channelCount() << Qt::endl;
//    创建录音对象
    my_audio = new QAudioInput(audioFormat,this);
    outFile = new QFile;
    outFile->setFileName(fileName); //语音原始文件
    outFile->open(QIODevice::WriteOnly|QIODevice::Truncate);
    my_audio->start(outFile);
}

///**********************
// * 结束录音并转换格式
//**********************/
void Speech::RecorderEnd()
{
//    结束录音
    my_audio->stop();

    outFile->close();
    delete outFile;
    outFile =nullptr;

    delete my_audio;
    my_audio = nullptr;

}


void Speech::audioCtrl(QString text)
{

    if(text == "开灯。")
    {
        system("echo 1 > /sys/class/leds/led1/brightness");
        system("echo 1 > /sys/class/leds/led2/brightness");
        system("echo 1 > /sys/class/leds/led3/brightness");

        ui->label_return->setText("灯已打开");
    }
    else if(text == "关灯。")
    {

        system("echo 0 > /sys/class/leds/led1/brightness");
        system("echo 0 > /sys/class/leds/led2/brightness");
        system("echo 0 > /sys/class/leds/led3/brightness");

        ui->label_return->setText("灯已关闭");
    }
    else if(text == "报警。")
    {
        int fd;
        struct input_event event;
        struct timeval time;
        fd = open("/dev/input/by-path/platform-beeper-event", O_RDWR);
        event.type = EV_SND;
        event.code = SND_TONE;
        event.value = 1000;
        time.tv_sec = 1;
        time.tv_usec = 0;
        event.time = time;
        write(fd, &event, sizeof(struct input_event));
        ui->label_return->setText("蜂鸣器已报警");
    }
    else if(text == "关闭。")
    {
        int fd;
        struct input_event event;
        struct timeval time;
        fd = open("/dev/input/by-path/platform-beeper-event", O_RDWR);
        event.type = EV_SND;
        event.code = SND_TONE;
        event.value = 0;
        time.tv_sec = 0;
        time.tv_usec = 0;
        event.time = time;
        write(fd, &event, sizeof(struct input_event));
        ui->label_return->setText("蜂鸣器报警已关闭");
    }
    else if(text == "关风扇。")
    {
        system("echo 0 > /sys/class/hwmon/hwmon1/pwm1");
        ui->label_return->setText("风扇已关闭");
    }
    else if(text == "开风扇。")
    {
        system("echo 255 > /sys/class/hwmon/hwmon1/pwm1");
        ui->label_return->setText("风扇已打开");
    }
    else if(text == "温度。")
    {
       QString tem = temCollect();
       ui->label_return->setText(QString("此时温度为:").append(tem).append("'C"));
    }
    else if(text == "湿度。")
    {
        QString hum = humCollect();
        ui->label_return->setText(QString("此时湿度为:").append(hum).append("%"));
    }

}

/*温度湿度*/
QString Speech::temCollect()
{
    int temp_raw = 0;
    int temp_offset = 0;
    float temp_scale = 0;
    float tem_float =0;
    QString tem;
    const char *device1 ="iio:device0";//温湿度
    /*read temp data*/
    read_sysfs_int(device1, "in_temp_raw", &temp_raw);
    read_sysfs_int(device1, "in_temp_offset", &temp_offset);
    read_sysfs_float(device1, "in_temp_scale", &temp_scale);
    tem_float =(temp_raw + temp_offset) * temp_scale / 1000;
    tem =QString::number(tem_float,'f', 2);
    return tem;
}
QString Speech::humCollect()
{
    int hum_raw = 0;
    int hum_offset = 0;
    float hum_scale = 0;
    float hum_float =0;
    QString hum;
    const char *device1 ="iio:device0";//温湿度
    read_sysfs_int(device1, "in_humidityrelative_raw", &hum_raw);
    read_sysfs_int(device1, "in_humidityrelative_offset", &hum_offset);
    read_sysfs_float(device1, "in_humidityrelative_scale", &hum_scale);
    hum_float = (hum_raw + hum_offset) * hum_scale / 1000;
    hum =QString::number(hum_float,'f', 2);
    return hum;
}

int Speech::read_sysfs_float(const char *device, const char *filename, float *val)
{
    int ret = 0;
    FILE *sysfsfp;
    char temp[128];
    memset(temp, '0', 128);
    ret = sprintf(temp, "/sys/bus/iio/devices/%s/%s", device, filename);
    if (ret < 0)
        goto error;
    sysfsfp = fopen(temp, "r");
    if (!sysfsfp)
    {
        ret = -errno;
        goto error;
    }
    errno = 0;
    if (fscanf(sysfsfp, "%f\n", val) != 1)
    {
        ret = errno ? -errno : -ENODATA;
        if (fclose(sysfsfp))
            perror("read_sysfs_float(): Failed to close dir");
        goto error;
    }
    if (fclose(sysfsfp))
        ret = -errno;
error:
    return ret;
}
int Speech::read_sysfs_int(const char *device, const char *filename, int *val)
{
    int ret = 0;
    FILE *sysfsfp;
    char temp[128];
    memset(temp, '0', 128);
    ret = sprintf(temp, "/sys/bus/iio/devices/%s/%s", device, filename);
    if (ret < 0)
        goto error;
    sysfsfp = fopen(temp, "r");
    if (!sysfsfp)
    {
        ret = -errno;
        goto error;
    }
    errno = 0;
    if (fscanf(sysfsfp, "%d\n", val) != 1)
    {
        ret = errno ? -errno : -ENODATA;
        if (fclose(sysfsfp))
            perror("read_sysfs_float(): Failed to close dir");
        goto error;
    }
    if (fclose(sysfsfp))
        ret = -errno;
error:
    return ret;
}


void Speech::on_back_ptn_clicked()
{
    this->close();
    this->deleteLater();
}
