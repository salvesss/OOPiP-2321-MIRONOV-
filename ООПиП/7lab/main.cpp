#include "Stack.h"
#include <iostream>
#include <string>

int main() {
    setlocale(LC_ALL, "RU");
    try {
        Stack<int> intStack = { 1, -2, 3, -4, 5 };

        std::cout << "Прямой обход стека (снизу вверх):\n";
        auto forwardIterator = intStack.getForwardIterator();
        while (forwardIterator.hasNext()) {
            std::cout << forwardIterator.next() << " ";
        }
        std::cout << "\n";

        std::cout << "Обратный обход стека (сверху вниз):\n";
        auto reverseIterator = intStack.getReverseIterator();
        while (reverseIterator.hasNext()) {
            std::cout << reverseIterator.next() << " ";
        }
        std::cout << "\n";

    }
    catch (const CustomException& e) {
        std::cerr << "Исключение: " << e.what() << "\n";
    }

    return 0;
}