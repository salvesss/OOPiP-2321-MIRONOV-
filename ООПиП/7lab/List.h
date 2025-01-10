#ifndef LIST_H
#define LIST_H

#include <memory>
#include "CustomException.h"

template <typename T>
class List {
private:

public:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node* prev;

        Node(const T& value, Node* prevNode = nullptr)
            : data(value), next(nullptr), prev(prevNode) {}
    };

    std::unique_ptr<Node> head;
    Node* tail;
    size_t listSize;

    List() : head(nullptr), tail(nullptr), listSize(0) {}

    void push_back(const T& value) {
        if (!head) {
            head = std::make_unique<Node>(value);
            tail = head.get();
        }
        else {
            tail->next = std::make_unique<Node>(value, tail);
            tail = tail->next.get();
        }
        ++listSize;
    }

    void pop_back() {
        if (!tail) throw CustomException("Список пуст");
        if (tail == head.get()) {
            head.reset();
            tail = nullptr;
        }
        else {
            tail = tail->prev;
            tail->next.reset();
        }
        --listSize;
    }

    const T& back() const {
        if (!tail) throw CustomException("Список пуст");
        return tail->data;
    }

    bool empty() const { return listSize == 0; }
    size_t size() const { return listSize; }

    Node* getHead() const { return head.get(); }
    Node* getTail() const { return tail; }
};

#endif 