#include "disk_main.h"
#include "ui_disk_main.h"

disk_main::disk_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::disk_main)
{
    ui->setupUi(this);
}

disk_main::~disk_main()
{
    delete ui;
}
