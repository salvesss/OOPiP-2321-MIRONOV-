#ifndef STACK_H
#define STACK_H

#include "List.h"
#include "IteratorInterface.h"
#include "CustomException.h"
#include <memory>

template <typename T>
class Stack {
private:
    List<T> list;

public:
    Stack() = default;

    Stack(std::initializer_list<T> initList) {
        for (const auto& item : initList) {
            push(item);
        }
    }

    void push(const T& value) {
        list.push_back(value);
    }

    void pop() {
        if (list.empty()) throw CustomException("Стек пуст");
        list.pop_back();
    }

    const T& top() const {
        if (list.empty()) throw CustomException("Стек пуст");
        return list.back();
    }

    bool empty() const { return list.empty(); }
    size_t size() const { return list.size(); }

    class ForwardIterator : public IteratorInterface<T> {
    private:
        typename List<T>::Node* current;

    public:
        explicit ForwardIterator(const List<T>& lst) : current(lst.getHead()) {}

        bool hasNext() const override {
            return current != nullptr;
        }

        T next() override {
            if (!current) throw CustomException("Итерация за пределами стека");
            T value = current->data;
            current = current->next.get();
            return value;
        }
    };

    class ReverseIterator : public IteratorInterface<T> {
    private:
        typename List<T>::Node* current;

    public:
        explicit ReverseIterator(const List<T>& lst) : current(lst.getTail()) {}

        bool hasNext() const override {
            return current != nullptr;
        }

        T next() override {
            if (!current) throw CustomException("Итерация за пределами стека");
            T value = current->data;
            current = current->prev;
            return value;
        }
    };

    ForwardIterator getForwardIterator() const {
        return ForwardIterator(list);
    }

    ReverseIterator getReverseIterator() const {
        return ReverseIterator(list);
    }
};

#endif