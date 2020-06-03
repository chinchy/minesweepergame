#include "custom.h"
#include "ui_custom.h"
#include "mainwindow.h"

#include <QMessageBox>

Custom::Custom(int w, int h, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Custom)
{
    this->width = w;
    this->height = h;
    ui->setupUi(this);
    setWindowFlags( Qt::WindowTitleHint );
}

Custom::~Custom()
{
    delete ui;
}

int Custom::GetWidth(){
    return this->width;
}

int Custom::GetHeight(){
    return this->height;
}

void Custom::on_okButton_clicked()
{
    int w, h;
    w = ui->widthEdit->text().toInt();
    h = ui->heightEdit->text().toInt();
    if ((9 <= w && w <= 32) || (9 <= h && h <= 32)){
        width = ui->widthEdit->text().toInt();
        height = ui->heightEdit->text().toInt();
        this->close();
    }
    else{
        QMessageBox validateMsg;
        validateMsg.setText("Размер поля не может быть меньше 9 и больше 32");
        validateMsg.setWindowTitle("Неверные значения");
        validateMsg.setIcon(QMessageBox::Critical);
        validateMsg.exec();
    }
}

void Custom::on_cancelButton_clicked()
{
    this->close();
}
