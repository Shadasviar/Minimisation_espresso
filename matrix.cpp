/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 2 -*-  */
/*
 * matrix.cpp
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

#include "matrix.h"
#include "to_binary.h"
#include <string>

using namespace std;

matrix createMatrix(int numOfLines, int numOfColumns){
    vector<QBitArray> array(numOfLines, QBitArray(numOfColumns));
    matrix matr;
    matr.array=array;
    matr.numOfRows=numOfLines;
    matr.numOfColumns=numOfColumns;
    return matr;
}

void showMatrix(const matrix &array){
    for(int i=0;i<array.numOfRows;i++){
        for(int j=0;j<array.numOfColumns;j++){
            cout<<array.array[i][j]<<" | ";
        }
        cout<<endl;
    }
}


matrix make_bin_matrix_by_dec_vec(const set<int> &vec, int max){
    vector<int> bin = toBinary(max);
    matrix matr = createMatrix(vec.size(),bin.size());
    set<int>::iterator ite = vec.begin();
    int dif = 0, k = 0;
    while(ite != vec.end()){
        bin = toBinary(*ite++);
        dif = matr.numOfColumns-bin.size();
        int last = bin.size()-1;
        for(int i=0; i<matr.numOfColumns;i++){
            if(dif>0){
                matr.array[k][i] = 0;
                --dif;
            } else{
                matr.array[k][i] = bin[last--];
            }
        }
        ++k;
    }
    return matr;

}


string show_matrix_as_string(const matrix &array){
    string result;
    string res;
    for(int i=0; i < array.numOfRows; i++){
        for(int j=0;j<array.numOfColumns;j++){
            res.append(to_string(array.array[i][j]));
            res.append("|");
        }
				res.append("\n");
        result.append(res);
        res.clear();
    }
    return result;
}
