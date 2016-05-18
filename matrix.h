/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 2 -*-  */
/*
 * matrix.h
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

#include <vector>
#include <string>
#include <QBitArray>
#include <set>
#ifndef MATRIX
#define MATRIX
#define OUT
#define IN

using namespace std;

struct matrix{
    vector<QBitArray> array;
    int numOfRows=0;
    int numOfColumns=0;
};

matrix createMatrix(int numOfLines, int numOfColumns);
void showMatrix(const matrix &array);
string show_matrix_as_string(const matrix &array);
matrix make_bin_matrix_by_dec_vec(const set<int> &vec, int max);

#endif //MATRIX

