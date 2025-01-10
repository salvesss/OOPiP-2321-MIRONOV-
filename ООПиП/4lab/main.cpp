#include "Stack.h"
#include "ExceptionHandler.h"
#include <iostream>
#include <string>

using namespace std;

void menu() {
    cout << "1. Push\n2. Pop\n3. Top\n4. Size\n5. Exit\n";
}

int main() {
    try {
        Stack<int> intStack;
        Stack<double> doubleStack;
        Stack<string> stringStack({ "Hello", "World" });

        int choice;
        while (true) {
            menu();
            cin >> choice;

            if (choice == 5) break;

            switch (choice) {
            case 1: {
                int value;
                cout << "Enter value: ";
                cin >> value;
                intStack.push(value);
                break;
            }
            case 2:
                intStack.pop();
                break;
            case 3:
                cout << "Top: " << intStack.top() << endl;
                break;
            case 4:
                cout << "Size: " << intStack.size() << endl;
                break;
            default:
                cout << "Invalid option\n";
            }
        }
    }
    catch (const exception& e) {
        ExceptionHandler::handle(e);
    }

    return 0;
}