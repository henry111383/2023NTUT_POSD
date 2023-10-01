#pragma once
#if !defined(NODE_H)
#define NODE_H

#include <string>
#include "./iterator.h"


class Node {
public:
    virtual std::string name() const = 0;
    
    virtual std::string path() const = 0;
    
    virtual void add(Node * node) = 0;

    virtual void remove(std::string path) =0;
    
    virtual Node * getChildByName(const char * name) const = 0;

    virtual Node * find(std::string path) = 0;

    virtual int numberOfFiles() const = 0;

    virtual Iterator * createIterator() = 0;
};


#endif // NODE_H
