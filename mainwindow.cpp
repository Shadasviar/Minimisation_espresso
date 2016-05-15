/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 2 -*-  */
/*
 * mainwindow.cpp
 * Copyright (C) Uladzislau Harbuz 2016 
 * 
 * Minimisation is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Minimisation is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "espresso.h"
#include <QVector>
#include <QString>
#include <vector>
#include "filename_enter.h"
#include <ctime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exit_button_clicked()
{
    this->close();
}

void MainWindow::on_make_button_clicked()
{

    char choose[2];

    bool something_is_checked = checked_options(choose);

    if(something_is_checked){

        ui->textBrowser->clear();

        QString ones = ui->ones_line_edit->text()+',',
                zeros = ui->zeros_line_edit->text()+',';

        vector<int> ones_vec = get_vector_from_string(ones);
        vector<int> zeros_vec = get_vector_from_string(zeros);

        clock_t start, stop;
        start = clock();

        string res = get_finally_functions_as_str(ones_vec, zeros_vec, choose);
        ui->textBrowser->setText(QString::fromStdString(res));

        if(ui->check_write_to_file->isChecked()){
            Filename_enter *filename = new Filename_enter(0, &res);
            filename->show();
        }
        res.clear();

        stop = clock();
        ui->time_label->setText(QString::number((double)(stop-start)/CLOCKS_PER_SEC));
    }


}

vector<int> MainWindow::get_vector_from_string(QString in_str){
    QString number;
    int num = 0;

    vector<int> result;
    for(QString::iterator ite= in_str.begin(); ite!= in_str.end(); ++ite){
        if(*ite != ','){
            number.append(*ite);
            continue;
        }else{
            num=number.toInt();
            number.clear();
            result.push_back(num);
        }
    }
    return result;
}


bool MainWindow::checked_options(char choose[2]){

    bool something_is_checked = false;
    if(ui->ones_radio_ones->isChecked()){
        choose[0] = 'F';
        something_is_checked = true;
    }
    else if(ui->ones_radio_dont_care->isChecked()){
        choose[0] = 'D';
        something_is_checked = true;
    }
    else if(ui->ones_radio_zeros->isChecked()){
        choose[0] = 'Z';
        something_is_checked = true;
    }
    else something_is_checked = false;

    if(ui->zeros_radio_zeros->isChecked()){
        choose[1] = 'R';
        something_is_checked = something_is_checked && true;
    }
    else if(ui->zeros_radio_dont_care->isChecked()){
        choose[1] = 'D';
        something_is_checked = something_is_checked && true;
    }
    else if(ui->zeros_radio_ones->isChecked()){
        choose[1] = 'Z';
        something_is_checked = something_is_checked && true;
    }
    else something_is_checked = false;

    return something_is_checked;
}
