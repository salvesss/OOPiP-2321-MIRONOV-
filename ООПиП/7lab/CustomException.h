#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include <stdexcept>
#include <string>

class CustomException : public std::runtime_error {
public:
    explicit CustomException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif