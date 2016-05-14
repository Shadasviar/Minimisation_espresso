#ifndef TO_BINARY
#define TO_BINARY

#include <iostream>
#include <vector>

using namespace std;

vector<int> toBinary(int deci){
    vector<int> vec;
    do{
        vec.push_back(deci%2);
        deci /= 2;
    }
    while (deci >0);
    return vec;
}

#endif // TO_BINARY

