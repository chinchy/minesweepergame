#include "custom.h"
#include "ui_custom.h"
#include "mainwindow.h"

Custom::Custom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Custom)
{
    ui->setupUi(this);
}

Custom::~Custom()
{
    delete ui;
}

int Custom::GetWidth(){
    return this->w;
}

int Custom::GetHeight(){
    return this->h;
}

void Custom::on_okButton_clicked()
{
    w = ui->widthEdit->text().toInt();
    h = ui->heightEdit->text().toInt();
    this->close();
}

void Custom::on_cancelButton_clicked()
{
    this->close();
}
