#ifndef LAB1_TYPES_H
#define LAB1_TYPES_H

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

#endif