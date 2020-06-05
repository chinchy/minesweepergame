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
    game->NewGame();
    map = game->GetMap();

    setFixedSize(game->GetWidth()*20, game->GetHeight()*20+20);

    QWidget *widget = new QWidget();
    QGridLayout *layout = new QGridLayout;
    QPushButton *btn;

    setCentralWidget(widget);

    for (int h = 1; h <= game->GetHeight(); h++){
        for (int w = 1; w <= game->GetWidth(); w++) {
            btn = new QPushButton("", widget);
            btn->setObjectName(QString("%1_%2").arg(h-1).arg(w-1));
            btn->setGeometry(QRect(QPoint(h*20, (w-1)*20), QSize(20, 20)));
            connect(btn, SIGNAL (clicked()), this, SLOT (on_cell_clicked()));
            layout->addWidget(btn, h, w);
        }
    }
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    widget->setLayout(layout);
}


void MainWindow::OpenCells(QPushButton* btn, int h, int w){
    btn->setEnabled(false);

    if (h+1 < game->GetHeight() && h+1 >= 0){
        QPushButton* tmp_btn = this->findChild<QPushButton *>(QString("%1_%2").arg(h+1).arg(w));
        if (map.at(h+1).at(w) == 0){
            if (tmp_btn->isEnabled())
                OpenCells(tmp_btn, h+1, w);
        }
        else{
            tmp_btn->setText(QString("%1").arg(map.at(h+1).at(w)));
            tmp_btn->setEnabled(false);
        }
    }

    if (h-1 < game->GetHeight() && h-1 >= 0){
        QPushButton* tmp_btn = this->findChild<QPushButton *>(QString("%1_%2").arg(h-1).arg(w));
        if (map.at(h-1).at(w) == 0){
            if (tmp_btn->isEnabled())
                OpenCells(tmp_btn, h-1, w);
        }
        else{
            tmp_btn->setText(QString("%1").arg(map.at(h-1).at(w)));
            tmp_btn->setEnabled(false);
        }
    }

    if (w+1 < game->GetWidth() && w+1 >= 0){
        QPushButton* tmp_btn = this->findChild<QPushButton *>(QString("%1_%2").arg(h).arg(w+1));
        if (map.at(h).at(w+1) == 0){
            if (tmp_btn->isEnabled())
                OpenCells(tmp_btn, h, w+1);
        }
        else{
            tmp_btn->setText(QString("%1").arg(map.at(h).at(w+1)));
            tmp_btn->setEnabled(false);
        }
    }

    if (w-1 < game->GetWidth() && w-1 >= 0){
        QPushButton* tmp_btn = this->findChild<QPushButton *>(QString("%1_%2").arg(h).arg(w-1));
        if (map.at(h).at(w-1) == 0){
            if (tmp_btn->isEnabled())
                OpenCells(tmp_btn, h, w-1);
        }
        else{
            tmp_btn->setText(QString("%1").arg(map.at(h).at(w-1)));
            tmp_btn->setEnabled(false);
        }
    }
}


void MainWindow::on_cell_clicked(){
    QPushButton* btn = qobject_cast<QPushButton*>(sender());

    int h = btn->objectName().split("_")[0].toInt();
    int w = btn->objectName().split("_")[1].toInt();

    if (map.at(h).at(w) == -1){
        btn->setIcon(QIcon(":/icon/src/mine.ico"));
        btn->setIconSize(QSize(10, 10));
    }
    else if (map.at(h).at(w) == 0){
        OpenCells(btn, h, w);
    }
    else{
        btn->setText(QString("%1").arg(map.at(h).at(w)));
    }
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
