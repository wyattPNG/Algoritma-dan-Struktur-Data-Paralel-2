#include "double_linked_list.h"
#include <iostream>
#include <stdexcept>

void DoubleLinkedList::init() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

bool DoubleLinkedList::is_empty() {
    return size == 0;
}

void DoubleLinkedList::add_front(char val) {
    Node* newNode = new Node{static_cast<char>(val), nullptr, nullptr};
    
    if (is_empty()) {
        head = tail = newNode;
        head->next = head;
        head->prev = head;
    } else {
        newNode->next = head;
        newNode->prev = tail;
        head->prev = newNode;
        tail->next = newNode;
        head = newNode;
    }
    size++;
}

void DoubleLinkedList::add_back(char val) {
    Node* newNode = new Node{static_cast<char>(val), nullptr, nullptr};
    
    if (is_empty()) {
        head = tail = newNode;
        head->next = head;
        head->prev = head;
    } else {
        newNode->next = head;
        newNode->prev = tail;
        tail->next = newNode;
        head->prev = newNode;
        tail = newNode;
    }
    size++;
}

void DoubleLinkedList::add_idx(char val, int idx) {
    if (idx < 0 || idx > size) {
        throw std::out_of_range("Index out of bounds");
    }
    
    if (idx == 0) {
        add_front(val);
        return;
    }
    if (idx == size) {
        add_back(val);
        return;
    }

    Node* curr = head;
    for (int i = 0; i < idx; ++i) {
        curr = curr->next;
    }
    
    Node* newNode = new Node{static_cast<char>(val), curr, curr->prev};
    curr->prev->next = newNode;
    curr->prev = newNode;
    size++;
}

void DoubleLinkedList::delete_front() {
    if (is_empty()) {
        throw std::out_of_range("Index out of bounds");
    }

    Node* temp = head;
    if (size == 1) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = tail;
        tail->next = head;
    }
    delete temp;
    size--;
}

void DoubleLinkedList::delete_back() {
    if (is_empty()) {
        throw std::out_of_range("Index out of bounds");
    }

    Node* temp = tail;
    if (size == 1) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
    }
    delete temp;
    size--;
}

void DoubleLinkedList::delete_idx(int idx) {
    if (idx < 0 || idx >= size) {
        throw std::out_of_range("Index out of bounds");
    }

    if (idx == 0) {
        delete_front();
        return;
    }
    if (idx == size - 1) {
        delete_back();
        return;
    }

    Node* curr = head;
    for (int i = 0; i < idx; ++i) {
        curr = curr->next;
    }

    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    delete curr;
    size--;
}

void DoubleLinkedList::display() {
    if (is_empty()) {
        std::cout << "List is empty\n";
        return;
    }
    
    Node* curr = head;
    for (int i = 0; i < size; ++i) {
        std::cout << curr->data;
        if (i < size - 1) std::cout << " ";
        curr = curr->next;
    }
    std::cout << "\n";
}

char DoubleLinkedList::get(int idx) {
    if (idx < 0 || idx >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    
    Node* curr = head;
    for (int i = 0; i < idx; ++i) {
        curr = curr->next;
    }
    return curr->data;
}

void DoubleLinkedList::set(char val, int idx) {
    if (idx < 0 || idx >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    
    Node* curr = head;
    for (int i = 0; i < idx; ++i) {
        curr = curr->next;
    }
    curr->data = val;
}

void DoubleLinkedList::clear() {
    while (!is_empty()) {
        delete_front();
    }
}