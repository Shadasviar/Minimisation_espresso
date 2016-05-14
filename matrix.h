#include <vector>
#include <string>
#include <QBitArray>
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
matrix make_bin_matrix_by_dec_vec(const vector<int> &vec, int max);

#endif //MATRIX

