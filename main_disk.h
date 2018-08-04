#ifndef MAIN_DISK_H
#define MAIN_DISK_H

#include <QMainWindow>
#include "mainwindow.h"


namespace Ui {
class main_disk;
}

class main_disk : public QMainWindow
{
    Q_OBJECT

public:
    explicit main_disk(QWidget *parent = 0);
    ~main_disk();


private:

    /*
     * 判断文件是否能够进行秒传
       返回1 秒传成功  返回0 无法秒传
    */

    int check_file_md5(QString filename,QString file_md5_string);


private slots:
    void on_toolButton_clicked();

    void on_upload_btn_clicked();



private:
    Ui::main_disk *ui;

    //请求管理
    QNetworkAccessManager * net_manger;

};

#endif // MAIN_DISK_H
