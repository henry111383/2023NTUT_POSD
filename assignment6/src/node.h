#pragma once

#include <string>
#include <sys/stat.h>
#include "iterator.h"
#include "visitor.h"
#include "null_iterator.h"
#include "order_by.h"
#include "iterator_factory.h"

using namespace std;

class Node {
private:

protected:
    string _path;
    Node * _parent;
    Node(string path): _path(path) {}

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

    virtual Iterator * createIterator(IteratorFactory * factory){
        return new NullIterator();
    }

    virtual Iterator * createIterator(OrderBy orderBy) {
        return new NullIterator();
    }

    virtual Node * find(string path) = 0;

    virtual std::list<string> findByName(string name) = 0;

    virtual void remove(string path) {
        throw string("This node does not support deleting sub node");
    }

    virtual void accept(Visitor * visitor) = 0;

    void rename(std::string name) {
        if(name.empty()){
            throw "Error";
        }
        // update name
        size_t slash = _path.rfind("/");
        if(slash != std::string::npos ){
            _path = _path.substr(0, slash+1) + name;
        }
        else {
            _path = name;
        }
        // update children's path
        updateChildren();
    }

    virtual void updateChildren() = 0;
    
    void updatePath(){
        if(_parent != nullptr){
            _path = _parent->path() + "/" + name();
        }
    }
};
