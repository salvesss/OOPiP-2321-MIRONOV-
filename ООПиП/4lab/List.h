#pragma once
#ifndef LIST_H
#define LIST_H

#include "Node.h"
#include <stdexcept>

using namespace std;

template <typename T>
class List {
private:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    size_t size = 0;

public:
    List() = default;

    ~List() { clear(); }

    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++size;
    }

    void pop_back() {
        if (!tail) throw out_of_range("List is empty");
        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        --size;
    }

    T& back() {
        if (!tail) throw out_of_range("List is empty");
        return tail->value;
    }

    size_t get_size() const { return size; }

    void clear() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = nullptr;
        size = 0;
    }
};

#endif // LIST_H