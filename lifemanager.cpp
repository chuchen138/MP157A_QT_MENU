#include "lifemanager.h"
#include "ui_lifemanager.h"

lifemanager::lifemanager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lifemanager)
{
    ui->setupUi(this);
}

lifemanager::~lifemanager()
{
    delete ui;
}

void lifemanager::on_pushButton_beijing_clicked()
{
    LifeWidget *beijinglifeWidget = new LifeWidget(BEIJING);
    beijinglifeWidget->show();
}

void lifemanager::on_pushButton_shanghai_clicked()
{
    LifeWidget *shanghailifeWidget = new LifeWidget(SHANGHAI);
    shanghailifeWidget->show();
}

void lifemanager::on_pushButton_tianjin_clicked()
{
    LifeWidget *tianjinlifeWidget = new LifeWidget(TIANJIN);
    tianjinlifeWidget->show();
}

void lifemanager::on_pushButton_chongqing_clicked()
{
    LifeWidget *chongqinglifeWidget = new LifeWidget(CHONGQING);
    chongqinglifeWidget->show();
}

void lifemanager::on_pushButton_jinan_clicked()
{
    LifeWidget *jinanlifeWidget = new LifeWidget(JINAN);
    jinanlifeWidget->show();
}

void lifemanager::on_pushButton_nanjing_clicked()
{
    LifeWidget *nanjinglifeWidget = new LifeWidget(NANJING);
    nanjinglifeWidget->show();
}

void lifemanager::on_pushButton_wuhan_clicked()
{
    LifeWidget *wuhanlifeWidget = new LifeWidget(WUHAN);
    wuhanlifeWidget->show();
}

void lifemanager::on_pushButton_hangzhou_clicked()
{
    LifeWidget *hangzhoulifeWidget = new LifeWidget(HANGZHOU);
    hangzhoulifeWidget->show();
}

void lifemanager::on_pushButton_guangzhou_clicked()
{
    LifeWidget *guangzhoulifeWidget = new LifeWidget(GUANGZHOU);
    guangzhoulifeWidget->show();
}

void lifemanager::on_pushButton_zhengzhou_clicked()
{
    LifeWidget *zhengzhoulifeWidget = new LifeWidget(ZHENGZHOU);
    zhengzhoulifeWidget->show();
}

void lifemanager::on_pushButton_shenyang_clicked()
{
    LifeWidget *shenyanglifeWidget = new LifeWidget(SHENYANG);
    shenyanglifeWidget->show();
}

void lifemanager::on_pushButton_taiyuan_clicked()
{
    LifeWidget *taiyuanlifeWidget = new LifeWidget(TAIYUAN);
    taiyuanlifeWidget->show();
}


void lifemanager::on_back_ptn_clicked()
{
    this->close();
    this->deleteLater();
}
