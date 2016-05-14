#include "filename_enter.h"
#include "ui_filename_enter.h"
#include "espresso.h"

Filename_enter::Filename_enter(QWidget *parent, std::string *in_str) :
    QDialog(parent),
    ui(new Ui::Filename_enter)
{
    ui->setupUi(this);
    str = *in_str;
}

Filename_enter::~Filename_enter()
{
    delete ui;
}

void Filename_enter::on_pushButton_clicked()
{
    const char *filename = ui->lineEdit->text().toStdString().c_str();
    write_to_file(str, filename);
    this->close();
}
