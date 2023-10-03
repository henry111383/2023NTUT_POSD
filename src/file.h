#pragma once
#if !defined(FILE_H)
#define FILE_H
#include <string>
#include "node.h"
#include "iterator.h"
#include "null_iterator.h"

class File: public Node {

public:
    File(std::string path):_path(path) 
    {
        _name = _path.substr(_path.find_last_of("/\\") + 1);
        nodeType = "File";
    };

    ~File(){};

    std::string name() const override
    {
        return _name;
    };
    
    std::string path() const override
    {
        return _path;
    };

    void add(Node * node) override 
    {
        throw "Current node (file) shouldn't add a child node!";
    }

    void remove(std::string path) override 
    {
        throw "Current node (file) shouldn't have a child node!";
    }

    Node * getChildByName(const char * name) const override 
    {
        throw "Current node (file) shouldn't have a child node!";
    }

    Node * find(std::string path) override 
    {
        // throw "Current node (file) shouldn't have a child node!";
        return nullptr;
    }

    int numberOfFiles() const override 
    {
        throw "Current node (file) shouldn't have a child node!";
    }

    Iterator * createIterator() override 
    {
        return new NullIterator();
    }
    
private:
    std::string _name;
    std::string _path;
};

#endif // FILE_H
