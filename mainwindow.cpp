#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "custom.h"

#include "game.h"

#include <QMessageBox>
#include <QPushButton>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new Game();

    setWindowFlags( Qt::WindowTitleHint | Qt::WindowCloseButtonHint );

    this->RenderField();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RenderField(){
    setFixedSize(game->GetWidth()*20, game->GetHeight()*20+20);

    QWidget *widget = new QWidget();
    QGridLayout *layout = new QGridLayout;
    QPushButton *tmp_btn;

    setCentralWidget(widget);

    for (int h = 1; h <= game->GetHeight(); h++){
        for (int w = 1; w <= game->GetWidth(); w++) {
            tmp_btn = new QPushButton(QString("btn_%1_%2").arg(h).arg(w), widget);
            tmp_btn->setText(QString("%1%2").arg(h).arg(w));
            tmp_btn->setGeometry(QRect(QPoint(h*20, (w-1)*20), QSize(20, 20)));
            layout->addWidget(tmp_btn, h, w);
        }
    }
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    widget->setLayout(layout);
}


void MainWindow::on_newgame_item_triggered()
{
    this->RenderField();
}

void MainWindow::on_easy_item_triggered()
{
    game->SetWidth(9);
    game->SetHeight(9);
    this->RenderField();
}

void MainWindow::on_medium_item_triggered()
{
    game->SetWidth(16);
    game->SetHeight(16);
    this->RenderField();
}

void MainWindow::on_hard_item_triggered()
{
    game->SetWidth(32);
    game->SetHeight(16);
    this->RenderField();
}

void MainWindow::on_custom_item_triggered()
{
    Custom *customWindow = new Custom(game->GetWidth(), game->GetHeight());
    customWindow->setModal(false);
    customWindow->setFixedSize(220, 150);
    customWindow->exec();

    game->SetWidth(customWindow->GetWidth());
    game->SetHeight(customWindow->GetHeight());
    this->RenderField();
}

void MainWindow::on_exit_item_triggered()
{
    MainWindow::close();
}
