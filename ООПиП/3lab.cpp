#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

template <typename T>
class ShPtr {
private:
    T* ptr;
    size_t* ref_count;

    void release() {
        if (ref_count) {
            (*ref_count)--;
            if (*ref_count == 0) {
                delete ptr;
                delete ref_count;
            }
        }
    }

public:
    ShPtr() : ptr(nullptr), ref_count(nullptr) {}

    explicit ShPtr(T* p) : ptr(p), ref_count(new size_t(1)) {}

    ShPtr(const ShPtr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        if (ref_count) {
            (*ref_count)++;
        }
    }

    ShPtr& operator=(const ShPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            if (ref_count) {
                (*ref_count)++;
            }
        }
        return *this;
    }

    ~ShPtr() {
        release();
    }

    T* get() const {
        return ptr;
    }

    void reset(T* p = nullptr) {
        release();
        if (p) {
            ptr = p;
            ref_count = new size_t(1);
        }
        else {
            ptr = nullptr;
            ref_count = nullptr;
        }
    }

    void swap(ShPtr& other) {
        std::swap(ptr, other.ptr);
        std::swap(ref_count, other.ref_count);
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    size_t use_count() const {
        return ref_count ? *ref_count : 0;
    }
};

void menu() {
    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Работа с типом int\n";
        cout << "2. Работа с типом double\n";
        cout << "3. Работа с типом string\n";
        cout << "4. Выход\n";
        cout << "Введите номер операции: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            ShPtr<int> p1(new int(42));
            cout << "Значение: " << *p1 << ", Счетчик ссылок: " << p1.use_count() << endl;

            ShPtr<int> p2 = p1;
            cout << "После копирования: Счетчик ссылок: " << p1.use_count() << endl;

            p2.reset();
            cout << "После обнуления p2: Счетчик ссылок p1: " << p1.use_count() << endl;
            break;
        }
        case 2: {
            ShPtr<double> p1(new double(3.14));
            cout << "Значение: " << *p1 << ", Счетчик ссылок: " << p1.use_count() << endl;

            ShPtr<double> p2;
            p2.swap(p1);
            cout << "После обмена: Значение p2: " << *p2 << ", Счетчик ссылок p2: " << p2.use_count() << endl;
            break;
        }
        case 3: {
            ShPtr<string> p1(new string("Привет, мир!"));
            cout << "Значение: " << *p1 << ", Счетчик ссылок: " << p1.use_count() << endl;

            ShPtr<string> p2 = p1;
            cout << "После копирования: Счетчик ссылок: " << p1.use_count() << endl;

            p1.reset();
            cout << "После обнуления p1: Счетчик ссылок p2: " << p2.use_count() << endl;
            break;
        }
        case 4:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный ввод. Попробуйте снова." << endl;
        }
    } while (choice != 4);
}

int main() {
    setlocale(LC_ALL, "Russian");
    menu();
    return 0;
}