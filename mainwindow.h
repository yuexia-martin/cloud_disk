#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QMessageBox>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonArray>
#include <QJsonParseError>
#include <QObject>
#include <QFileDialog>
#include <QCryptographicHash>
#include <QFile>
#include <QPixmap>

#include <future>
#include <thread>
#include <vector>
#include <algorithm>
#include <cassert>

#include <QFileDialog>
#include <QMenu>
#include <QWidget>
#include <QtWin>
#include <QIcon>
#include <QFileIconProvider>
#include <QTemporaryFile>

#include <windows.h>
#include <iostream>

//#include <QWe

#include "config.h"
#include "tools.h"
#include "main_disk.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);


    ~MainWindow();

    void set_config(Config *temp_config);


private:





private slots:
    void on_exit_btn_clicked();

    void on_exit_btn_2_clicked();


    void on_back_main_clicked();

    void on_pushButton_clicked();

    void on_exit_btn_3_clicked();

    void on_pushButton_4_clicked();

    void on_reg_btn_clicked();

    void on_login_btn_clicked();

    void window_change();

private:
    Ui::MainWindow *ui;


    QString host;
    QString ip;
    QString port;

    Config *config;


    //请求管理
    QNetworkAccessManager * net_manger;

    QString token;
};

#endif // MAINWINDOW_H
