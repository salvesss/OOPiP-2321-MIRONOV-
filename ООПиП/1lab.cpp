#include <iostream>
#include <initializer_list>
#include <string>

using namespace std;

namespace containers {

    template <typename T>
    class NameClass {
    private:
        struct Node {
            T value;
            Node* next;

        private:
            Node(const T& val, Node* nxt = nullptr) : value(val), next(nxt) {}
            friend class NameClass;
        };

        Node* head;
        size_t size;

    public:
        NameClass() : head(nullptr), size(0) {}

        NameClass(initializer_list<T> init_list) : head(nullptr), size(0) {
            for (const auto& item : init_list) {
                add(item, size);
            }
        }

        NameClass(const NameClass& other) : head(nullptr), size(0) {
            Node* current = other.head;
            while (current) {
                add(current->value, size);
                current = current->next;
            }
        }

        NameClass& operator=(const NameClass& other) {
            if (this != &other) {
                clear();
                Node* current = other.head;
                while (current) {
                    add(current->value, size);
                    current = current->next;
                }
            }
            return *this;
        }

        NameClass(NameClass&& other) noexcept : head(other.head), size(other.size) {
            other.head = nullptr;
            other.size = 0;
        }

        NameClass& operator=(NameClass&& other) noexcept {
            if (this != &other) {
                clear();
                head = other.head;
                size = other.size;
                other.head = nullptr;
                other.size = 0;
            }
            return *this;
        }

        ~NameClass() { clear(); }

        T& operator[](size_t index) {
            Node* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            return current->value;
        }

        const T& operator[](size_t index) const {
            Node* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            return current->value;
        }

        void add(const T& value, size_t position) {
            if (position > size) throw out_of_range("Position out of range");

            if (position == 0) {
                head = new Node(value, head);
            }
            else {
                Node* current = head;
                for (size_t i = 0; i < position - 1; ++i) {
                    current = current->next;
                }
                current->next = new Node(value, current->next);
            }
            ++size;
        }

        void remove(size_t position) {
            if (position >= size) throw out_of_range("Position out of range");

            Node* to_delete;
            if (position == 0) {
                to_delete = head;
                head = head->next;
            }
            else {
                Node* current = head;
                for (size_t i = 0; i < position - 1; ++i) {
                    current = current->next;
                }
                to_delete = current->next;
                current->next = to_delete->next;
            }
            delete to_delete;
            --size;
        }

        void clear() {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            size = 0;
        }

        size_t getSize() const { return size; }
    };

    template <typename T>
    class Queue {
    private:
        NameClass<T> list;

    public:
        void enqueue(const T& value) {
            list.add(value, list.getSize());
        }

        void dequeue() {
            if (list.getSize() == 0) throw underflow_error("Queue is empty");
            list.remove(0);
        }

        T& front() {
            if (list.getSize() == 0) throw underflow_error("Queue is empty");
            return list[0];
        }

        const T& front() const {
            if (list.getSize() == 0) throw underflow_error("Queue is empty");
            return list[0];
        }

        size_t getSize() const { return list.getSize(); }

        bool isEmpty() const { return list.getSize() == 0; }
    };
}

int main() {
    using namespace containers;

    NameClass<int> intVector = { 1, 2, 3, 4, 5 };
    intVector.add(10, 2);
    intVector.remove(4);
    for (size_t i = 0; i < intVector.getSize(); ++i) {
        cout << intVector[i] << " ";
    }
    cout << endl;

    Queue<string> stringQueue;
    stringQueue.enqueue("Hello");
    stringQueue.enqueue("World");
    cout << stringQueue.front() << endl;
    stringQueue.dequeue();
    cout << stringQueue.front() << endl;

    return 0;
}
