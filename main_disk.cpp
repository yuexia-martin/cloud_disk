#include "main_disk.h"
#include "ui_main_disk.h"
#include "mainwindow.h"



main_disk::main_disk(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::main_disk)
{
    ui->setupUi(this);

    //初始化请求管理器
    this->net_manger=new QNetworkAccessManager;



    //设置QListWidget的显示模式
    ui->listWidget->setViewMode(QListView::IconMode);
    //设置QListWidget中单元项的图片大小
    ui->listWidget->setIconSize(QSize(100,100));

    //设置QListWidget中单元项的间距
    ui->listWidget->setSpacing(10);

    //设置自适应
    ui->listWidget->setResizeMode(QListWidget::Adjust);

    //设置不能移动
    ui->listWidget->setMovement(QListWidget::Static);


    //去除边框
    this->setWindowFlags(Qt::FramelessWindowHint);
}

main_disk::~main_disk()
{
    delete ui;
}

void main_disk::on_toolButton_clicked()
{
    exit(0);
}


//文件上传按钮被点击
void main_disk::on_upload_btn_clicked()
{

    int ret =0;

    QString filename = QFileDialog::getOpenFileName(this,"选择您要上传的文件",QDir::currentPath(),"All files(*.*)");

    //循环 多选

    if(!filename.isNull()){

        //用户选择了文件,进行计算md5
        QByteArray file_md5 = getFileMd5(filename);

        QString file_md5_string=file_md5.toHex();

        qDebug()<<"filename:"<<filename<<endl<<"file md5:"<<file_md5_string<<endl;

        //发送http请求,判断文件是否可以秒传

        this->check_file_md5(filename,file_md5_string);




    }

}


void  main_disk::check_file_md5(QString filename,QString file_md5_string)
{

    int ret=0;


    QNetworkRequest request(QUrl(QString("%1%2%3").arg("http://").arg("192.168.58.133").arg("/md5")));

     //设置数据传输方式(post)
     request.setRawHeader("Content-Type","application/json");

     request.setRawHeader("token",this->config->token);


//      qDebug()<<"check_md5"<<this->config->token<<endl;

       //定义json对象
       QJsonObject json;

       QFileInfo fi=QFileInfo(filename);

       qDebug()<<"file name:"<<fi.fileName()<<endl;

       json.insert("filename", fi.fileName());
       json.insert("md5",file_md5_string);



       //定义json操作类 从json中进行初始化
       QJsonDocument document;

       document.setObject(json);

       QByteArray data_json=document.toJson();

       //请求
       QNetworkReply * rep=this->net_manger->post(request,data_json);



       //    绑定请求结束事件
           connect(rep,&QNetworkReply::finished,[=](){

               qDebug()<<"111"<<endl;

               if(rep->error()!=QNetworkReply::NoError){

                    qDebug()<<"秒传对比md5请求错误"<<endl;

//                    rep->deleteLater();

                    return;
               }

               qDebug()<<"222"<<endl;

               QByteArray byte_arr=rep->readAll();

               qDebug()<<"777"<<endl;

               //判断字符串转化为QJsonDocument  是否出现了错误
              QJsonParseError jsonError;//Qt5新类

              qDebug()<<"888"<<endl;

              QJsonDocument json = QJsonDocument::fromJson(byte_arr, &jsonError);//Qt5新类

              qDebug()<<"333"<<endl;

              if (jsonError.error == QJsonParseError::NoError)
              {
                qDebug()<<"444"<<endl;

                  qDebug()<<"返回格式正确"<<endl;

                   QJsonObject rootObj = json.object();



                   qint8 status=rootObj.value("status").toInt();

                   QString msg=rootObj.value("msg").toString();


                   if(1 == status)
                   {

                      qDebug()<<"秒传成功"<<endl;

                      QMessageBox::information(this,"秒传成功","秒传成功");



                   }else if(2 == status){

                        QMessageBox::information(this,"文件已存在","该文件已存在,不能上传重复文件");

                   }
                   else{

                       qDebug()<<"该文件无法进行秒传 status:"<<status<<endl;

                       //调用文件上传方法 进行文件上传
                       this->upload_file(filename);
                   }


              }else{

                  qDebug()<<"555"<<endl;

                  QString result_str=byte_arr;

                  qDebug()<<"返回json格式错误 返回:"<<result_str<<endl;

              }

              rep->deleteLater();

           });



}

void main_disk::set_config(Config *temp_config){

   this->config=temp_config;

}


//切换用户按钮
void main_disk::on_change_user_clicked()
{

    MainWindow *mainwindow=new MainWindow;

    mainwindow->show();

    this->close();


}


//文件上传
void main_disk::upload_file(QString filename){

    qDebug()<<"进入文件上传函数"<<endl;

    do{

        QNetworkRequest request(QUrl(QString("%1%2%3").arg("http://").arg("192.168.58.133").arg("/upload")));

         //设置数据传输方式(post)
         request.setRawHeader("Content-Type","multipart/form-data;boundary=---------------------------18410170095896");
         request.setRawHeader("token",this->config->token);

         //打开要上传的文件
         QFile file(filename);

         QFileInfo fi(filename);

         if(!file.open(QIODevice::ReadOnly) || file.size()==0)
         {
             file.close();
             break;
         }


          QByteArray post_data;

          post_data.append(QString("-----------------------------18410170095896\r\nContent-Disposition: form-data; name=\"file\"; filename=\"%1\"\r\nContent-Type: text/plain\r\n\r\n").arg(fi.fileName()));

          //把文件读到要发送的包里面去
          post_data.append(file.readAll());



          post_data.append("\r\n-----------------------------18410170095896--\r\n");

           //请求
           QNetworkReply * rep=this->net_manger->post(request,post_data);

           file.close();



           //    绑定请求结束事件
               connect(rep,&QNetworkReply::finished,[=](){

                   if(rep->error()!=QNetworkReply::NoError){

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


                       if(1 == status)
                       {

                          qDebug()<<"上传成功"<<endl;
                          QMessageBox::information(this,"文件上传成功","文件上传成功");

                       }else{

                           qDebug()<<"上传失败"<<endl;

                       }


                  }else{



                      qDebug()<<"返回json格式错误"<<endl;

                  }

                  rep->deleteLater();


               });

    }while(0);

}


//刷新文件列表
void main_disk::on_my_files_clicked()
{
    //定义要访问的url地址
    QNetworkRequest request(QUrl(QString("%1%2").arg(this->config->url).arg("/myfiles")));
    //鉴权
    request.setRawHeader("token",this->config->token);

    QByteArray post_data;

    post_data.append("{\"action\": \"get_list\"}\n");

    QNetworkReply * rep=this->net_manger->post(request,post_data);

      connect(rep,&QNetworkReply::finished,[=](){

           //判断是否请求错误
          if(rep->error()!=QNetworkReply::NoError){

              qDebug()<<"发送请求错误"<<endl;
              rep->deleteLater();

              return ;
          }

           QByteArray byte_arr=rep->readAll();

           QString result=byte_arr;

          //判断json解析是否正确
          QJsonParseError jsonError;//Qt5新类
          QJsonDocument json = QJsonDocument::fromJson(byte_arr, &jsonError);//Qt5新类
          if (jsonError.error == QJsonParseError::NoError)
          {

              qDebug().noquote()<<result;

              //刷新文件列表
              this->flush_table(byte_arr);



          }else
          {
               qDebug()<<"JSON解析错误"<<endl;
               rep->deleteLater();
          }



      });



    qDebug()<<"获取完成"<<endl;
}

 void main_disk::flush_table(QByteArray result){


            //定义QListWidgetItem对象
             QListWidgetItem *imageItem = new QListWidgetItem;
             //为单元项设置属性
             imageItem->setIcon(QIcon(":/ico/fileIcon/bmp.png"));
             imageItem->setText(tr("Browse"));
             //重新设置单元项图片的宽度和高度
             imageItem->setSizeHint(QSize(100,120));
             //将单元项添加到QListWidget中
             ui->listWidget->addItem(imageItem);

 }




