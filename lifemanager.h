#ifndef LIFEMANAGER_H
#define LIFEMANAGER_H

#include <QWidget>
#include "lifewidget.h"

#define BEIJING    "101010100"
#define SHANGHAI   "101020100"
#define TIANJIN    "101030100"
#define CHONGQING  "101040100"
#define JINAN      "101120101"
#define NANJING    "101190101"
#define WUHAN      "101200101"
#define HANGZHOU   "101210101"
#define GUANGZHOU  "101280101"
#define ZHENGZHOU  "101210101"
#define SHENYANG   "101070101"
#define TAIYUAN    "101100101"

namespace Ui {
class lifemanager;
}

class lifemanager : public QWidget
{
    Q_OBJECT

public:
    explicit lifemanager(QWidget *parent = nullptr);
    ~lifemanager();

private slots:
    void on_pushButton_beijing_clicked();

    void on_pushButton_shanghai_clicked();

    void on_pushButton_tianjin_clicked();

    void on_pushButton_chongqing_clicked();

    void on_pushButton_jinan_clicked();

    void on_pushButton_nanjing_clicked();

    void on_pushButton_wuhan_clicked();

    void on_pushButton_hangzhou_clicked();

    void on_pushButton_guangzhou_clicked();

    void on_pushButton_zhengzhou_clicked();

    void on_pushButton_shenyang_clicked();

    void on_pushButton_taiyuan_clicked();

    void on_back_ptn_clicked();

private:
    Ui::lifemanager *ui;
};

#endif // LIFEMANAGER_H
