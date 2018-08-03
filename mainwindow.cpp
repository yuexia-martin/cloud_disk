#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{



    ui->setupUi(this);

    //去除边框
    this->setWindowFlags(Qt::FramelessWindowHint);

    //启动时显示主界面
    this->ui->stackedWidget->setCurrentIndex(0);

    //获取服务器ip
    this->ip=ui->host_ip->text();

    //获取服务器端口
    this->port=ui->host_port->text();

    //初始化请求管理器

    this->net_manger=new QNetworkAccessManager;



}



MainWindow::~MainWindow()
{
    delete ui;
}


//退出按钮被点击
void MainWindow::on_exit_btn_clicked()
{
    exit(0);
}

//最小化按钮被点击
void MainWindow::on_exit_btn_2_clicked()
{


}

//从注册返回主界面
void MainWindow::on_back_main_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

//从主界面调到注册
void MainWindow::on_pushButton_clicked()
{
     this->ui->stackedWidget->setCurrentIndex(1);
}



void MainWindow::on_exit_btn_3_clicked()
{
     this->ui->stackedWidget->setCurrentIndex(2);
}

//从服务器设置界面转到主界面
void MainWindow::on_pushButton_4_clicked()
{
     this->ui->stackedWidget->setCurrentIndex(0);
}


//注册按钮被点击
void MainWindow::on_reg_btn_clicked()
{

    //验证正则表达式

    //验证用户名
    QString pattern="[A-Za-z0-9_\-\u4e00-\u9fa5]+";
    QRegExp rx(pattern);

    bool match = rx.exactMatch(ui->username->text());

    if(!match){

            QMessageBox::warning(this,"用户名填写格式不正确","用户名填写格式不正确,请输入字母数字或下划线");
            return;
    }





    //验证密码

   if(ui->password->text().isEmpty()  || ui->password_enter->text().isEmpty()){

       QMessageBox::warning(this,"密码必须填写","密码不能为空");
       return;
   }


   if(ui->password->text()!=ui->password_enter->text()){

             QMessageBox::warning(this,"密码不一致","两次输入的密码不一致,请重新重新输入密码");
             return;
   }

    //验证手机

   pattern="0?(13|14|15|16|17|18|19)[0-9]{9}";
   QRegExp rx_phone(pattern);
   match = rx_phone.exactMatch(ui->phone->text());

   //写了手机号码就判断
    if(!ui->phone->text().isEmpty() && !match){

        QMessageBox::warning(this,"手机号码填写不正确","手机号码填写不正确,请重新填写");
        return;

    }

    //验证邮箱
    pattern="^[a-zA-Z0-9_.-]+@[a-zA-Z0-9-]+(\.[a-zA-Z0-9-]+)*\.[a-zA-Z0-9]{2,6}$";
    QRegExp rx_email(pattern);
    match = rx_email.exactMatch(ui->email->text());


    //写了邮箱才判断 不写邮箱就不判断
     if(!ui->email->text().isEmpty() && !match){

         QMessageBox::warning(this,"邮箱填写不正确","邮箱填写不正确,请重新填写");
         return;

     }



     QNetworkRequest request(QUrl(QString("%1%2%3").arg("http://").arg(ui->host_ip->text()).arg("/reg")));

      //设置数据传输方式(post)
      request.setRawHeader("Content-Type","application/json");
      request.setRawHeader("cookie","afsbfuewihfksdjnfbkdf");

        //定义json对象
        QJsonObject json;

        json.insert("username",ui->username->text());
        json.insert("nickname",ui->nickname->text());
        json.insert("password",ui->password->text());
        json.insert("phone",ui->phone->text());
        json.insert("email",ui->email->text());


        //定义json操作类 从json中进行初始化
        QJsonDocument document;

        document.setObject(json);

        QByteArray data_json=document.toJson();



//        qDebug()<<data_json;




    //请求
    QNetworkReply * rep=this->net_manger->post(request,data_json);


//    绑定请求结束事件
    connect(rep,&QNetworkReply::finished,[=](){

        if(rep->error()!=QNetworkReply::NoError){
            qDebug()<<"请求出错"<<": http://"<<this->ip<<endl;

            rep->deleteLater();

            return ;
        }

        QByteArray byte_arr=rep->readAll();

        //判断字符串转化为QJsonDocument  是否出现了错误
       QJsonParseError jsonError;//Qt5新类
       QJsonDocument json = QJsonDocument::fromJson(byte_arr, &jsonError);//Qt5新类
       if (jsonError.error == QJsonParseError::NoError)
       {


           qDebug()<<"返回格式正确"<<endl;

            QJsonObject rootObj = json.object();



            qint8 status=rootObj.value("status").toInt();

            QString msg=rootObj.value("msg").toString();

            if(1==status)
            {

                QMessageBox::about(this,"成功",msg);
                this->ui->stackedWidget->setCurrentIndex(0);

            }else{
                QMessageBox::about(this,"失败",msg);
                qDebug()<<status<<endl;
            }


       }else{

           qDebug()<<"返回json格式错误"<<endl;

       }






    });


}

//登录功能
void MainWindow::on_login_btn_clicked()
{
      QNetworkRequest request(QUrl(QString("%1%2%3").arg("http://").arg(ui->host_ip->text()).arg("/login")));

       //设置数据传输方式(post)
       request.setRawHeader("Content-Type","application/json");
       request.setRawHeader("cookie","afsbfuewihfksdjnfbkdf");

         //定义json对象
         QJsonObject json;

         json.insert("username",ui->login_user->text());
         json.insert("password",ui->login_pass->text());



         //定义json操作类 从json中进行初始化
         QJsonDocument document;

         document.setObject(json);

         QByteArray data_json=document.toJson();

         //请求
         QNetworkReply * rep=this->net_manger->post(request,data_json);

         //    绑定请求结束事件
             connect(rep,&QNetworkReply::finished,[=](){

                 if(rep->error()!=QNetworkReply::NoError){
                     qDebug()<<"请求出错"<<": http://"<<this->ip<<endl;

                     rep->deleteLater();

                     return ;
                 }

                 QByteArray byte_arr=rep->readAll();

                 //判断字符串转化为QJsonDocument  是否出现了错误
                QJsonParseError jsonError;//Qt5新类
                QJsonDocument json = QJsonDocument::fromJson(byte_arr, &jsonError);//Qt5新类
                if (jsonError.error == QJsonParseError::NoError)
                {


                    qDebug()<<"返回格式正确"<<endl;

                     QJsonObject rootObj = json.object();



                     qint8 status=rootObj.value("status").toInt();

                     QString msg=rootObj.value("msg").toString();

                     this->token=rootObj.value("token").toString();

                     if(1 == status)
                     {

                        qDebug()<<"登录成功"<<endl;

                        qDebug()<<"token:"<<this->token<<endl;

                        this->window_change();

                     }else{
                         QMessageBox::about(this,"失败",msg);
                         qDebug()<<status<<endl;
                     }


                }else{

                    QString result_str=byte_arr;

                    qDebug()<<"返回json格式错误 返回:"<<result_str<<endl;

                }

             });

}

void MainWindow::window_change()
{

      main_disk  * disk_window = new main_disk;


      disk_window->show();

      this->hide();

}




