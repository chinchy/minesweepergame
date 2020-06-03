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
    explicit Custom(int w, int h, QWidget *parent = nullptr);
    ~Custom();
    void SetWidth(int value);
    int GetWidth();
    void SetHeight(int value);
    int GetHeight();

private slots:

    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::Custom *ui;
    int width, height;
};

#endif // CUSTOM_H
