#pragma once
#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

#include <stdexcept>
#include <iostream>

using namespace std;

class ExceptionHandler {
public:
    static void handle(const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
};

#endif // EXCEPTIONHANDLER_H