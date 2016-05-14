#ifndef FILENAME_ENTER_H
#define FILENAME_ENTER_H

#include <QDialog>
#include <vector>
#include <string>

namespace Ui {
class Filename_enter;
}

using std::vector;

class Filename_enter : public QDialog
{
    Q_OBJECT

public:
    explicit Filename_enter(QWidget *parent = 0, std::string *in_str = nullptr);
    ~Filename_enter();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Filename_enter *ui;
    std::string str;
};

#endif // FILENAME_ENTER_H
