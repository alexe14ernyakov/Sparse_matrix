#ifndef LAB1_TYPES_H
#define LAB1_TYPES_H
#include <iostream>
#include <cstring>

struct Item{
    int          value;
    int          i;
    int          j;
    struct Item* next;
};
typedef struct Item Item;

struct Node{
    int          line;
    int          amount;
    Item*        head;
    struct Node* next;
};
typedef struct Node Node;

struct Matrix{
    int   m;
    int   n;
    Node* head;
};
typedef struct Matrix Matrix;


int get_int(int &a);

Matrix* create_matrix();
Node* create_node(int i);
Item* create_item(int i, int j, int value);

void fill_matrix(Matrix* matrix);

bool find_cell(Node* node, int i, int j);
Node* find_node(Node* head, int i);
Item* find_item(Item* head, int i, int j);

void add_item(Item* head, Item* item);
void add_node(Node* head, Node* node);

void print_matrix(Matrix* matrix);
void print_line(Item* head);

template <typename T>
T* list_copy(T* head){
    if(head == nullptr)
        return nullptr;
    T* ptr = head;
    T* tmp;
        tmp = new T;

    std::memcpy(tmp, ptr, sizeof(T));
    T* new_head = tmp;
    ptr = ptr->next;
    while(ptr != nullptr){
        tmp->next = new T;
        std::memcpy(tmp->next, ptr, sizeof(T));
        tmp = tmp->next;
        ptr = ptr->next;
    }
    return new_head;
}

Matrix* copy_matrix(Matrix* src);

void edit_matrix(Matrix* matrix);
int edit_list(Node* node);
bool criterion_check(Item* item);

void delete_item(Item* previous_item);
void delete_spaces(Matrix* matrix);

void sort_list(Matrix* matrix);
Node* find_max(Node* head);

void clear_matrix(Matrix* matrix);

template <typename T>
void clear_list(T* head){
    while(head != nullptr){
        T* trash = head;
        head = head->next;
        delete trash;
    }
}

#endif