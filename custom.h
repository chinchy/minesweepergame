#ifndef CUSTOM_H
#define CUSTOM_H

#include <QDialog>

namespace Ui {
class Custom;
}

class Custom : public QDialog
{
    Q_OBJECT

public:
    explicit Custom(QWidget *parent = nullptr);
    ~Custom();
    int GetWidth();
    int GetHeight();

private slots:

    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::Custom *ui;
    int w, h;
};

#endif // CUSTOM_H
