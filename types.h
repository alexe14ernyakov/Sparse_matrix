#ifndef SPARSE_MATRIX_TYPES_H
#define SPARSE_MATRIX_TYPES_H

#include <iostream>
//#include <fstream>

struct Item
{
    int          value;
    struct Item* next;
    int          number;                       /// Номер элемента в строке
};
typedef struct Item Item;

struct Node
{
    int          line;
    struct Node* next;
    struct Item* head;
};
typedef struct Node Node;

struct Matrix
{
    int          m;                            /// Количество строк
    int          n;                            /// Количество столбцов
    struct Node* head;
};
typedef struct Matrix Matrix;

int get_num(int &a, const char* content);

Node* create_node(int line);
Item* create_line(int n, int line);

Matrix* create_matrix();
void fill_matrix(Matrix* matrix);

#endif
