#pragma once 
#include <iostream>
#include<string>
#include <sys/stat.h>
#include "iterator.h"
#include "null_iterator.h"
#include "visitor.h"

using namespace std;

class Node {
private:

    string _path;
    Node * _parent;
    struct stat _st;
    

protected:
    string nodeType;

    Node(string path): _path(path) {
        if (lstat(_path.c_str(), &_st) != 0){
            // std::cout << std::string("Node is not exist!") << " " << path <<std::endl;
            throw(std::string("Node is not exist!"));
        }
            

        switch (_st.st_mode & S_IFMT)
        {
        case S_IFREG:
            nodeType = "file";
            break;
        case S_IFDIR:
            nodeType = "folder";
            break;
        }
    }

public:
    virtual ~Node() {}

    Node * parent() {
        return _parent;
    }

    void parent(Node * parent) {
        _parent = parent;
    }
    
    virtual void removeChild(Node * target) {
        throw string("This node does not support removing sub node");
    }

    string name() const {
        size_t slash = _path.rfind("/");
        return _path.substr(slash+1);
    }
    
    string path() const {
        return _path;
    }
    
    virtual void add(Node * node) {
        throw string("This node does not support adding sub node");
    }

    virtual Node * getChildByName(const char * name) const {
        return nullptr;
    }

    virtual int numberOfFiles() const = 0;

    virtual Iterator * createIterator() {
        return new NullIterator();
    }

    virtual Iterator * dfsIterator() {
        return new NullIterator();
    }

    virtual Node * find(string path) = 0;
    
    virtual std::list<string> findByName(string name) = 0;
    
    virtual void remove(string path) {
        throw string("This node does not support deleting sub node");
    }

    virtual void accept(Visitor * visitor) = 0;
};