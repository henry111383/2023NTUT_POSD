#pragma once
#if !defined(NODE_H)
#define NODE_H

#include <string>
#include <list>
#include "./iterator.h"


class Node {
public:
    Node(){};

    virtual ~Node() {};

    virtual std::string name() const = 0;
    
    virtual std::string path() const = 0;
    
    virtual void add(Node * node) = 0;

    virtual void remove(std::string path) =0;
    
    virtual Node * getChildByName(const char * name) const = 0;

    virtual Node * find(std::string path) = 0;

    virtual int numberOfFiles() const = 0;

    virtual Iterator * createIterator() = 0;

    std::list<Node *> child;

    std::string nodeType;

    Node* parentFolder;
};


#endif // NODE_H
