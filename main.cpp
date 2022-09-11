#include "types.h"

int main(){
    Matrix* matrix;
    try {
        matrix = create_matrix();
    }
    catch(const std::bad_alloc& ex){
        std::cout << "Alloc error!";
        clear_matrix(matrix);
        return 0;
    }
    fill_matrix(matrix);
    print_matrix(matrix);
    std::cout << std::endl;
    Matrix* new_matrix;
    try {
        new_matrix = copy_matrix(matrix);
    }
    catch(const std::bad_alloc& ex){
        std::cout << "Alloc error!";
        clear_matrix(new_matrix);
        return 0;
    }
    edit_matrix(new_matrix);
    delete_spaces(new_matrix);
    sort_list(new_matrix);
    print_matrix(new_matrix);
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
        if(i < 0 || i > matrix->m){
            std::cout << "Incorrect index...\n";
            continue;
        }

        std::cout << "Enter number of column: ";
        get_int(j);
        if(j == 0)
            return;
        if(j < 0 || j > matrix->n){
            std::cout << "Incorrect index...\n";
            continue;
        }
        if(find_cell(matrix->head, i, j)){
            std::cout << "Indexes repeat..." << std::endl;
            continue;
        }

        std::cout << "Enter value of cell: ";
        get_int(value);

        if (matrix->head == nullptr) {
            matrix->head = create_node(i);
            matrix->head->head = create_item(i, j, value);
            matrix->head->amount = 1;
        } else {
            Node *current_node = find_node(matrix->head, i);
            if (current_node != nullptr) {
                current_node->amount++;
                add_item(current_node->head, create_item(i, j, value));
            } else {
                add_node(matrix->head, create_node(i));
                Node* node = find_node(matrix->head, i);
                node->head = create_item(i, j, value);
                node->amount = 1;
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

Matrix* copy_matrix(Matrix* src){
    Matrix* new_matrix;
    new_matrix = new Matrix;
    new_matrix->head = list_copy(src->head);
    Node* ptr = new_matrix->head;
    Node* tmp = src->head;
    while(ptr != nullptr){
        ptr->head = list_copy(tmp->head);
        ptr = ptr->next;
        tmp = tmp->next;
    }
    new_matrix->n = src->n;
    new_matrix->m = src->m;
    return new_matrix;
}

void edit_matrix(Matrix* matrix){
    int d;
    Node* ptr = matrix->head;
    while(ptr != nullptr){
        d = edit_list(ptr);
        ptr->amount = ptr->amount - d;
        ptr = ptr->next;
    }
}

int edit_list(Node* node){
    int counter = 0;
    while (criterion_check(node->head)){
        Item* trash = node->head;
        node->head = node->head->next;
        delete trash;
        counter++;
    }
    Item* ptr = node->head;
    if(ptr == nullptr)
        return counter;
    while(ptr->next != nullptr){
        if(criterion_check(ptr->next)){
            delete_item(ptr);
            counter++;
        }
        else
            ptr = ptr->next;
    }
    return counter;
}

bool criterion_check(Item* item){
    if( item == nullptr)
        return false;

    int a = item->value;

    while(a / 10 != 0){
        if(a%10%2 == 1)
            return true;
        a = a / 10;
    }
    if (a % 2 == 1)
        return true;
    else
        return false;
}

void delete_item(Item* previous_item){
    Item* trash = previous_item->next;
    previous_item->next = previous_item->next->next;
    delete trash;
}

void delete_spaces(Matrix* matrix){
    if(matrix->head == nullptr)
        return;

    while(matrix->head->head == nullptr){
        Node* trash = matrix->head;
        matrix->head = matrix->head->next;
        delete trash;
    }

    Node* ptr = matrix->head;
    if(ptr == nullptr)
        return;
    while(ptr->next != nullptr){
        if(ptr->next->head == nullptr){
            Node* trash = ptr->next;
            ptr->next = ptr->next->next;
            delete trash;
        }
        else
            ptr = ptr->next;
    }
}

void sort_list(Matrix* matrix){
    if(matrix->head == nullptr)
        return;

    Node* new_head = find_max(matrix->head);
    Node* ptr = matrix->head;
    while(ptr->next != new_head)
        ptr = ptr->next;
}

Node* find_max(Node* head){
    Node* max = head;
    Node* ptr = head;
    while(ptr != nullptr){
        if(ptr->next->amount > max->amount)
            max = ptr->next;
        ptr = ptr->next;
    }
    return max;
}

void clear_matrix(Matrix* matrix){
    Node* ptr = matrix->head;
    while(ptr != nullptr){
        clear_list(ptr->head);
        ptr = ptr->next;
    }
    clear_list(matrix->head);
    delete matrix;
}