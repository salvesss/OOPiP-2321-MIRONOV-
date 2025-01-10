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
        cout << "\n����:\n";
        cout << "1. ������ � ����� int\n";
        cout << "2. ������ � ����� double\n";
        cout << "3. ������ � ����� string\n";
        cout << "4. �����\n";
        cout << "������� ����� ��������: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            ShPtr<int> p1(new int(42));
            cout << "��������: " << *p1 << ", ������� ������: " << p1.use_count() << endl;

            ShPtr<int> p2 = p1;
            cout << "����� �����������: ������� ������: " << p1.use_count() << endl;

            p2.reset();
            cout << "����� ��������� p2: ������� ������ p1: " << p1.use_count() << endl;
            break;
        }
        case 2: {
            ShPtr<double> p1(new double(3.14));
            cout << "��������: " << *p1 << ", ������� ������: " << p1.use_count() << endl;

            ShPtr<double> p2;
            p2.swap(p1);
            cout << "����� ������: �������� p2: " << *p2 << ", ������� ������ p2: " << p2.use_count() << endl;
            break;
        }
        case 3: {
            ShPtr<string> p1(new string("������, ���!"));
            cout << "��������: " << *p1 << ", ������� ������: " << p1.use_count() << endl;

            ShPtr<string> p2 = p1;
            cout << "����� �����������: ������� ������: " << p1.use_count() << endl;

            p1.reset();
            cout << "����� ��������� p1: ������� ������ p2: " << p2.use_count() << endl;
            break;
        }
        case 4:
            cout << "����� �� ���������." << endl;
            break;
        default:
            cout << "�������� ����. ���������� �����." << endl;
        }
    } while (choice != 4);
}

int main() {
    setlocale(LC_ALL, "Russian");
    menu();
    return 0;
}