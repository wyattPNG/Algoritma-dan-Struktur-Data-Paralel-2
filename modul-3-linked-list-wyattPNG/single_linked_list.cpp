#include "single_linked_list.h"
#include <iostream>
#include <stdexcept>

void SingleLinkedList::init() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

bool SingleLinkedList::is_empty() {
    return size == 0;
}

void SingleLinkedList::add_front(int val) {
    Node* newNode = new Node{val, nullptr};
    if (is_empty()) {
        head = tail = newNode;
        tail->next = head;
    } else {
        newNode->next = head;
        head = newNode;
        tail->next = head;
    }
    size++;
}

void SingleLinkedList::add_back(int val) {
    Node* newNode = new Node{val, nullptr};
    if (is_empty()) {
        head = tail = newNode;
        tail->next = head;
    } else {
        tail->next = newNode;
        tail = newNode;
        tail->next = head;
    }
    size++;
}

void SingleLinkedList::add_idx(int val, int idx) {
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

    Node* newNode = new Node{val, nullptr};
    Node* curr = head;
    
    for (int i = 0; i < idx - 1; ++i) {
        curr = curr->next;
    }
    
    newNode->next = curr->next;
    curr->next = newNode;
    size++;
}

void SingleLinkedList::delete_front() {
    if (is_empty()) {
        throw std::out_of_range("List is empty");
    }

    Node* temp = head;
    if (size == 1) {
        head = tail = nullptr;
    } else {
        head = head->next;
        tail->next = head;
    }
    delete temp;
    size--;
}

void SingleLinkedList::delete_back() {
    if (is_empty()) {
        throw std::out_of_range("List is empty");
    }
    
    if (size == 1) {
        delete_front();
        return;
    }

    Node* curr = head;
    while (curr->next != tail) {
        curr = curr->next;
    }

    Node* temp = tail;
    tail = curr;
    tail->next = head;
    delete temp;
    size--;
}

void SingleLinkedList::delete_idx(int idx) {
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
    for (int i = 0; i < idx - 1; ++i) {
        curr = curr->next;
    }

    Node* temp = curr->next;
    curr->next = temp->next;
    delete temp;
    size--;
}

void SingleLinkedList::display() {
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

int SingleLinkedList::get(int idx) {
    if (idx < 0 || idx >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    
    Node* curr = head;
    for (int i = 0; i < idx; ++i) {
        curr = curr->next;
    }
    return curr->data;
}

void SingleLinkedList::set(int val, int idx) {
    if (idx < 0 || idx >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    
    Node* curr = head;
    for (int i = 0; i < idx; ++i) {
        curr = curr->next;
    }
    curr->data = val;
}

void SingleLinkedList::clear() {
    while (!is_empty()) {
        delete_front();
    }
}