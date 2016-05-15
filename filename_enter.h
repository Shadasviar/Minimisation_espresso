/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 2 -*-  */
/*
 * filename_enter.h
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
