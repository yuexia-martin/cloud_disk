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

#include "tools.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

//    void mousePressEvent(QMouseEvent *event);

    ~MainWindow();

private slots:
    void on_exit_btn_clicked();

    void on_exit_btn_2_clicked();


    void on_back_main_clicked();

    void on_pushButton_clicked();

    void on_exit_btn_3_clicked();

    void on_pushButton_4_clicked();

    void on_reg_btn_clicked();

    void on_login_btn_clicked();

private:
    Ui::MainWindow *ui;

    QString ip;

    QString port;

    //请求管理
    QNetworkAccessManager * net_manger;

    QString token;
};

#endif // MAINWINDOW_H
