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

     void set_config(Config *temp_config);


private:

    /*
     * 判断文件是否能够进行秒传
       返回1 秒传成功  返回0 无法秒传
    */

    void check_file_md5(QString filename,QString file_md5_string);

    void upload_file(QString filename);

    void flush_table(QByteArray result);


private slots:
    void on_toolButton_clicked();

    void on_upload_btn_clicked();



    void on_change_user_clicked();



    void on_my_files_clicked();

private:
    Ui::main_disk *ui;

    //请求管理
    QNetworkAccessManager * net_manger;

    Config *config;

};

#endif // MAIN_DISK_H
