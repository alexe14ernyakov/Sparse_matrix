#ifndef SPARSE_MATRIX_TYPES_H
#define SPARSE_MATRIX_TYPES_H

#include <iostream>
//#include <fstream>

template <class T>
int get_num(T &a)
{
    std::cin >> a;
    if(!std::cin.good())
        return -1;
    return 1;
}

#endif
