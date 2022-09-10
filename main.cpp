#include <iostream>
#include "types.h"

int main(){                               /// обработка исключений (память)
    int a;
    get_int(a);
    std::cout << a << std::endl;

    Matrix* matrix = create_matrix();
    fill_matrix(matrix);
    print_matrix(matrix);
    return 0;
}

int get_int(int &a){
    std::cin >> a;
    if(!std::cin.good())
        return 0;
    return 1;
}

Matrix* create_matrix(){
    int m, n;
    std::cout << "Enter number of lines: ";
    get_int(m);
    std::cout << "Enter number of columns: ";
    get_int(n);
    Matrix* matrix;
    matrix = new Matrix;
    matrix->head = nullptr;
    matrix->m = m;
    matrix->n = n;
    return matrix;
}

Node* create_node(int i){
    Node* node;
    node = new Node;
    node->line = i;
    node->next = nullptr;
    node->head = nullptr;
    node->amount = 0;
    return node;
}

Item* create_item(int i, int j, int value){
    Item* item;
    item = new Item;
    item->i = i;
    item->j = j;
    item->value = value;
    item->next = nullptr;
    return item;
}

void fill_matrix(Matrix* matrix){
    int i, j, value;

    while(true) {
        std::cout << "Enter number of line: ";
        get_int(i);
        if(i == 0)
            return;

        std::cout << "Enter number of column: ";
        get_int(j);
        if(find_cell(matrix->head, i, j))
            continue;

        std::cout << "Enter value of cell: ";
        get_int(value);

        if (matrix->head == nullptr) {
            matrix->head = create_node(i);
            matrix->head->head = create_item(i, j, value);
        } else {
            Node *current_node = find_node(matrix->head, i);
            if (current_node != nullptr) {
                current_node->amount++;
                add_item(current_node->head, create_item(i, j, value));
            } else {
                add_node(matrix->head, create_node(i));
                Node* node = find_node(matrix->head, i);
                node->head = create_item(i, j, value);
            }
        }
    }
}

bool find_cell(Node* head, int i, int j){
    Node* node = find_node(head, i);
    if(node == nullptr)
        return false;
    else{
        Item* item = find_item(node->head, i, j);
        if(item != nullptr)
            return true;
    }
    return false;
}

Node* find_node(Node* head, int i){
    if(head == nullptr)
        return nullptr;
    Node* ptr = head;
    while(ptr != nullptr){
        if(ptr->line == i)
            return ptr;
        ptr = ptr->next;
    }
    return nullptr;
}

Item* find_item(Item* head, int i, int j){
    if(head == nullptr)
        return nullptr;
    Item* ptr = head;
    while(ptr != nullptr){
        if(ptr->i == i && ptr->j == j)
            return ptr;
        ptr = ptr->next;
    }
    return nullptr;
}

void add_item(Item* head, Item* item){
    Item* ptr = head;
    while(ptr->next != nullptr)
        ptr = ptr->next;
    ptr->next = item;
}

void add_node(Node* head, Node* node){
    Node* ptr = head;
    while(ptr->next != nullptr)
        ptr = ptr->next;
    ptr->next = node;
}

void print_matrix(Matrix* matrix){
    Node* ptr = matrix->head;
    while(ptr != nullptr){
        std::cout << "Line " << ptr->line << ":\t";
        print_line(ptr->head);
        ptr = ptr->next;
        std::cout << std::endl;
    }
}

void print_line(Item* head){
    Item* ptr = head;
    while(ptr != nullptr){
        std::cout << "[" << ptr->j << "]: " << ptr->value << "\t";
        ptr = ptr->next;
    }
}
