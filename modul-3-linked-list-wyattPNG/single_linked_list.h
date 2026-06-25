#ifndef SINGLE_LINKED_LIST
#define SINGLE_LINKED_LIST

struct Node {
    int data;
    Node * next;
};

struct SingleLinkedList {
    Node *head = nullptr, *tail = nullptr;
    int size = 0;
    
    void init();
    bool is_empty();
    
    void add_front(int val);
    void add_back(int val);
    void add_idx(int val, int idx);

    void delete_front();
    void delete_back();
    void delete_idx(int idx);

    void display();
    int get(int idx);
    void set(int val, int idx);

    void clear();
};

#endif