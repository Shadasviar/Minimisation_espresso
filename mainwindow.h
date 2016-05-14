#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_exit_button_clicked();

    void on_make_button_clicked();


private:
    Ui::MainWindow *ui;
    std::vector<int> get_vector_from_string(QString in_str);
    bool checked_options(char choose[2]);
};

#endif // MAINWINDOW_H
