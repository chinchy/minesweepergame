#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "custom.h"

#include "game.h"
#include "qrightclickbutton.h"

#include <QMessageBox>
#include <QPushButton>
#include <QGridLayout>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new Game();

    setWindowFlags( Qt::WindowTitleHint | Qt::WindowCloseButtonHint );

    this->RenderField();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::WinGame(){
    if (isTimer){
        timer->stop();
        isTimer = false;
    }
    QString sec = "";
    switch(time % 10) {
      case 1:
        sec = "секунда";
        break;
      case 2:
        sec = "секунды";
        break;
      case 3:
        sec = "секунды";
        break;
      case 4:
        sec = "секунды";
        break;
      default:
        sec = "секунд";
    }
    QMessageBox *msg = new QMessageBox(QMessageBox::NoIcon, "Победа!", QString("Поздравляем!!! Вы справились %1 %2!").arg(time).arg(sec), QMessageBox::Apply);
    msg->setWindowIcon(QIcon(":/icon/src/mine.ico"));
    msg->exec();
}


void MainWindow::LoseGame(){
    if (isTimer){
        timer->stop();
        isTimer = false;
    }

    for (int h = 0; h < game->GetHeight(); h++){
        for (int w = 0; w < game->GetWidth(); w++) {
            QRightClickButton* btn = this->findChild<QRightClickButton *>(QString("%1_%2").arg(h).arg(w));
            btn->setEnabled(false);
            if (map.at(h).at(w) == -1){
                btn->setIcon(QIcon(":/icon/src/mine.ico"));
                btn->setIconSize(QSize(10, 10));
            }
            else{
                btn->setIcon(QIcon());
            }
        }
    }
}


void MainWindow::RenderField(){
    game->NewGame();
    map = game->GetMap();

    setFixedSize(game->GetWidth()*20, game->GetHeight()*20+20);

    QWidget *widget = new QWidget();
    QGridLayout *layout = new QGridLayout;
    QRightClickButton *btn;

    setCentralWidget(widget);

    for (int h = 1; h <= game->GetHeight(); h++){
        for (int w = 1; w <= game->GetWidth(); w++) {
            btn = new QRightClickButton("", widget);

            QIcon icon = QIcon();
            icon.addPixmap(QPixmap(":/icon/src/empty.png"), QIcon::Normal, QIcon::Off);
            icon.addPixmap(QPixmap(":/icon/src/flag.png"), QIcon::Normal, QIcon::On);
            btn->setIcon(icon);
            btn->setIconSize(QSize(10, 10));
            btn->setCheckable(true);
            btn->setStyleSheet("width: 20px;"
                               "height: 20px;"
                               "background-color: rgb(192, 192, 192);"
                               "border-width: 2px;"
                               "border-style: outset;"
                               "border-top-color: rgb(255, 255, 255);"
                               "border-left-color: rgb(255, 255, 255);"
                               "border-bottom-color: rgb(128, 128, 128);"
                               "border-right-color: rgb(128, 128, 128);");
            btn->setObjectName(QString("%1_%2").arg(h-1).arg(w-1));
            btn->setGeometry(QRect(QPoint(h*20, (w-1)*20), QSize(20, 20)));
            connect(btn, SIGNAL (leftClicked()), this, SLOT (on_cell_clicked()));
            connect(btn, SIGNAL (rightClicked()), this, SLOT (on_cell_add_flag()));
            layout->addWidget(btn, h, w);
        }
    }
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    widget->setLayout(layout);

    time = 0;
    if (isTimer){
        timer->stop();
        isTimer = false;
    }
    ui->statusBar->showMessage(QString("Всего мин: %1  Время: %2").arg(game->GetMineCount()).arg(time));
}


void MainWindow::OpenCells(QPushButton* btn, int h, int w){
    if (btn->isEnabled() and map.at(h).at(w) == 0){
        btn->setEnabled(false);
        btn->setChecked(false);
        btn->setCheckable(false);
        btn->setIcon(QIcon());
        btn->setStyleSheet("background-color: rgb(150, 150, 150);"
                           "border-width: 1px;"
                           "border-color: rgb(50, 50, 50);");
        if (game->CellCounterInc() == 1)
            WinGame();
    }

    for (int i=-1; i<2; i++){
        for (int j=-1; j<2; j++){
            if ((h+i < game->GetHeight() && h+i >= 0) && (w+j < game->GetWidth() && w+j >= 0)){
                QRightClickButton* tmp_btn = this->findChild<QRightClickButton *>(QString("%1_%2").arg(h+i).arg(w+j));
                if (map.at(h+i).at(w+j) == 0){
                    if (tmp_btn->isEnabled())
                        OpenCells(tmp_btn, h+i, w+j);
                }
                else{
                    if (tmp_btn->isEnabled()){
                        QString color;

                        switch(map.at(h+i).at(w+j)) {
                          case 1:
                            color = "color: blue;";
                            break;
                          case 2:
                            color = "color: green;";
                            break;
                          case 3:
                            color = "color: red;";
                            break;
                          default:
                            color = "color: yellow;";
                        }

                        tmp_btn->setText(QString("%1").arg(map.at(h+i).at(w+j)));
                        tmp_btn->setEnabled(false);
                        tmp_btn->setChecked(false);
                        tmp_btn->setCheckable(false);
                        tmp_btn->setIcon(QIcon());
                        tmp_btn->setStyleSheet(color +
                                               "font-weight: bold;"
                                               "background-color: rgb(150, 150, 150);"
                                               "border-width: 1px;"
                                               "border-color: rgb(50, 50, 50);");

                        if (game->CellCounterInc() == 1)
                            WinGame();
                    }
                }
            }
        }
    }
}


void MainWindow::updateTime()
{
    time++;
    ui->statusBar->showMessage(QString("Всего мин: %1  Время: %2").arg(game->GetMineCount()).arg(time));
}


void MainWindow::on_cell_clicked(){
    if (!isTimer){
        isTimer = true;
        timer->start(1000);
    }

    QRightClickButton* btn = qobject_cast<QRightClickButton*>(sender());

    int h = btn->objectName().split("_")[0].toInt();
    int w = btn->objectName().split("_")[1].toInt();

    if (map.at(h).at(w) == -1){
        btn->setIcon(QIcon(":/icon/src/mine.ico"));
        btn->setIconSize(QSize(10, 10));
        btn->setStyleSheet("background-color: red");
        LoseGame();
    }
    else if (map.at(h).at(w) == 0){
        OpenCells(btn, h, w);
    }
    else{
        QString color;
        switch(map.at(h).at(w)) {
          case 1:
            color = "color: blue;";
            break;
          case 2:
            color = "color: green;";
            break;
          case 3:
            color = "color: red;";
            break;
          default:
            color = "color: yellow;";
        }

        btn->setText(QString("%1").arg(map.at(h).at(w)));
        btn->setEnabled(false);
        btn->setChecked(false);
        btn->setCheckable(false);
        btn->setIcon(QIcon());
        btn->setStyleSheet(color +
                               "font-weight: bold;"
                               "background-color: rgb(150, 150, 150);"
                               "border-width: 1px;"
                               "border-color: rgb(50, 50, 50);");

        if (game->CellCounterInc() == 1)
            WinGame();
    }
}


void MainWindow::on_cell_add_flag(){
    QRightClickButton* btn = qobject_cast<QRightClickButton*>(sender());

    int h = btn->objectName().split("_")[0].toInt();
    int w = btn->objectName().split("_")[1].toInt();

    if (btn->isChecked()){
        btn->setChecked(false);
        connect(btn, SIGNAL (leftClicked()), this, SLOT (on_cell_clicked()));

        if (map.at(h).at(w) == -1)
            game->MineCounterDec();
    }
    else{
        btn->setChecked(true);
        disconnect(btn, SIGNAL (leftClicked()), this, SLOT (on_cell_clicked()));

        if (map.at(h).at(w) == -1)
            if (game->MineCounterInc() == 1)
                WinGame();
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

void MainWindow::on_rules_item_triggered()
{
    QMessageBox *msg = new QMessageBox(QMessageBox::NoIcon,
                                       "Сапер: правила и общие сведения",
                                       "• Число в ячейке показывает, сколько мин скрыто вокруг данной ячейки. Это число поможет понять вам, где находятся безопасные ячейки, а где находятся бомбы.\n"
                                       "• Если рядом с открытой ячейкой есть пустая ячейка, то она откроется автоматически.\n"
                                       "• Если вы открыли ячейку с миной, то игра проиграна.\n"
                                       "• Что бы пометить ячейку, в которой находится бомба, нажмите её правой кнопкой мыши.\n"
                                       "• Если в ячейке указано число, оно показывает, сколько мин скрыто в восьми ячейках вокруг данной. Это число помогает понять, где находятся безопасные ячейки.\n"
                                       "• Игра продолжается до тех пор, пока вы не откроете все не заминированные ячейки.",
                                       QMessageBox::Ok);
    msg->setWindowIcon(QIcon(":/icon/src/mine.ico"));
    msg->exec();
}

void MainWindow::on_about_item_triggered()
{
    QMessageBox *msg = new QMessageBox(QMessageBox::NoIcon,
                                       "Об игре \"Сапёр\"",
                                       "Игра \"Сапёр\"\n\nСоздана в рамках курсовой работы\nстудентом 2 курса СПбПУ Петровым Ильёй\n\n© 2020 Petrov Ilya. Все права защищены",
                                       QMessageBox::Ok);
    msg->setWindowIcon(QIcon(":/icon/src/mine.ico"));
    msg->exec();
}
