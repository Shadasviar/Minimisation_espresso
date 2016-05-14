#include "matrix.h"
#include "to_binary.h"
#include <string>
//#include <algorithm>

using namespace std;

matrix createMatrix(int numOfLines, int numOfColumns){
    vector<QBitArray> array(numOfLines, QBitArray(numOfColumns));
    matrix matr;
    matr.array=array;
    matr.numOfRows=numOfLines;
    matr.numOfColumns=numOfColumns;
    return matr;
}

/*
void delete_matrix(matrix &mat){
    for(int i=0;i<mat.numOfRows;i++){
            delete [] mat.array[i];
    }
    delete [] mat.array;
    mat.array = nullptr;
}


void delete_vector_of_matrix(vector<matrix> &vector_of_matr){
    vector<matrix>::iterator ite;
    for(ite=vector_of_matr.begin();ite != vector_of_matr.end(); ++ite){
        delete_matrix(*ite);
    }
}
*/

void showMatrix(const matrix &array){
    for(int i=0;i<array.numOfRows;i++){
        for(int j=0;j<array.numOfColumns;j++){
            cout<<array.array[i][j]<<" | ";
        }
        cout<<endl;
    }
}


matrix make_bin_matrix_by_dec_vec(const vector<int> &vec, int max){
    //int max = *max_element(vec.begin(),vec.end());
    vector<int> bin = toBinary(max);
    matrix matr = createMatrix(vec.size(),bin.size());
    //int dif =0;
    for(int k=0, dif = 0; k<matr.numOfRows;k++){
        bin = toBinary(vec[k]);
        dif = matr.numOfColumns-bin.size();
        int last = bin.size()-1;
        for(int i=0; i<matr.numOfColumns;i++){
            if(dif>0){
                matr.array[k][i] =0;
                dif--;
            } else{
                matr.array[k][i] = bin[last];
                last--;
            }
        }
    }
    return matr;

}

/*
matrix copy_matrix(const matrix &mat){
    matrix copied = createMatrix(mat.numOfRows, mat.numOfColumns);
    for(int i = 0; i < copied.numOfRows; i++){
        for(int j = 0; j < copied.numOfColumns; j++){
            copied.array[i][j] = mat.array[i][j];
        }
    }
    return copied;
}
*/

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
