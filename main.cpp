#include "mainwindow.h"
#include <QApplication>





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Config *config=new Config;

    w.set_config(config);



    w.show();

    return a.exec();
}
