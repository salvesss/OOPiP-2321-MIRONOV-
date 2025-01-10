#ifndef ITERATORINTERFACE_H
#define ITERATORINTERFACE_H

template <typename T>
class IteratorInterface {
public:
    virtual ~IteratorInterface() = default;
    virtual bool hasNext() const = 0;    
    virtual T next() = 0;               
};

#endif