#include "types.h"
using namespace std;

int main()
{
    Matrix* matrix = create_matrix();
    fill_matrix(matrix);
    return 0;
}

int get_num(int &a, const char* content)
{
    std::cout << "Enter " << content << ": " << std::endl;
    std::cin >> a;
    if(!std::cin.good()){
        std::cout << "Error! " << std::endl;
        return  0;
    }
    return 1;
}

Node* create_node(int line)
{
    Node* node = new Node;
    node->next = nullptr;
    node->head = nullptr;
    node->line = line;
    return node;
}

Item* create_line(int n, int line)
{
    Item* head = new Item;
    head->next = nullptr;
    head->number = 1;

    int value;
    get_num(value, "value");
    head->value = value;

    Item* ptr = head;
    for(int i = 1; i < n; i++){
        ptr = new Item;
        ptr->number = i+1;
        ptr->next = nullptr;
        get_num(value, "value");
        ptr->value = value;
        ptr = ptr->next;
    }
    return head;
}

Matrix* create_matrix()
{
    int m, n;
    get_num(m, "number of lines");
    get_num(n, "number of columns");
    Matrix* matrix;
    matrix = new Matrix;
    matrix->head = nullptr;
    matrix->m = m;
    matrix->n = n;
    return matrix;
}

void fill_matrix(Matrix* matrix)
{
    matrix->head = create_node(1);
    matrix->head->head = create_line(matrix->n, 1);
    Node* ptr = matrix->head;
    for(int i = 1; i < matrix->m; i++){
        ptr = new Node;
        ptr->next = nullptr;
        ptr->line = i+1;
        ptr->head = create_line(matrix->n, i);
        ptr = ptr->next;
    }
}
