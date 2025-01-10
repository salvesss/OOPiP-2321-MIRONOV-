#pragma once
#ifndef STACK_H
#define STACK_H

#include "List.h"
#include <initializer_list>

using namespace std;

template <typename T>
class Stack {
private:
    List<T> list;

public:
    Stack() = default;

    Stack(initializer_list<T> initList) {
        for (const auto& value : initList) {
            push(value);
        }
    }

    void push(const T& value) { list.push_back(value); }
    void pop() { list.pop_back(); }
    T& top() { return list.back(); }
    size_t size() const { return list.get_size(); }
    bool empty() const { return size() == 0; }

    Stack(const Stack& other) {
        Stack temp;
        Node<T>* node = other.list.head;
        while (node) {
            temp.push(node->value);
            node = node->next;
        }
        while (!temp.empty()) {
            push(temp.top());
            temp.pop();
        }
    }

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            list.clear();
            Stack temp;
            Node<T>* node = other.list.head;
            while (node) {
                temp.push(node->value);
                node = node->next;
            }
            while (!temp.empty()) {
                push(temp.top());
                temp.pop();
            }
        }
        return *this;
    }

    Stack(Stack&& other) noexcept : list(move(other.list)) {}

    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            list = move(other.list);
        }
        return *this;
    }
};

#endif // STACK_H