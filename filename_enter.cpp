/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 2 -*-  */
/*
 * filename_enter.cpp
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
