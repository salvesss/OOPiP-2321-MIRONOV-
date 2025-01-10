#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>

using namespace std;

class CustomException : public exception {
private:
    string message;
    double value;
    int errorCode;

public:
    CustomException(const string& msg, double val, int code)
        : message(msg), value(val), errorCode(code) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    double getValue() const {
        return value;
    }

    int getErrorCode() const {
        return errorCode;
    }
};

double calculateZ1(double a) {
    try {
        if (a == -2 || a == 0 || a == 2) {
            throw CustomException("������������ �������� 'a', ���������� � ������� �� ����", a, 1);
        }
        double part1 = (1 + a + (a * a)) / (2 * a + (a * a));
        double part2 = 2 - (1 - a + (a * a)) / (2 * a - a * a);
        double result = pow(part1 + part2, -1) * (5 - 2 * a * a);
        return result;
    }
    catch (const CustomException& e) {
        cout << "������ ��� ���������� Z1: " << e.what() << ", ��������: " << e.getValue() << ", ���: " << e.getErrorCode() << endl;
        throw;
    }
}

double calculateZ2(double x) {
    try {
        double result = (4 - x * x) / 2;
        return result;
    }
    catch (const exception& e) {
        throw CustomException("������ ��� ���������� Z2", x, 2);
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    try {
        double a, x;
        cout << "������� �������� ��� a: ";
        cin >> a;
        cout << "������� �������� ��� x: ";
        cin >> x;

        double Z1 = calculateZ1(a);
        double Z2 = calculateZ2(x);

        cout << fixed << setprecision(5);
        cout << "Z1 = " << Z1 << endl;
        cout << "Z2 = " << Z2 << endl;

        if (abs(Z1 - Z2) < 1e-5) {
            cout << "Z1 � Z2 �������������� �����." << endl;
        }
        else {
            cout << "Z1 � Z2 �� �����." << endl;
        }

    }
    catch (const CustomException& e) {
        cout << "���������� ����������: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "���������� ����������: " << e.what() << endl;
    }

    return 0;
}
