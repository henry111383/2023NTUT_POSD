#pragma once
#if !defined(FOLDER)
#define FOLDER

#include <string>
#include <list>
#include <algorithm>
#include "./iterator.h"
#include "./null_iterator.h"
#include "./node.h"

struct IsMatchingName {
    IsMatchingName(const std::string& key) : key_(key) {}
    bool operator()(const Node* node) const {
        return (node->name()) == key_;
    }
    std::string key_;
};

class Folder: public Node {
public:
    std::list<Node *> child;

    Folder(std::string path):_path(path) 
    {
        _name = _path.substr(_path.find_last_of("/\\") + 1);
    };

    ~Folder(){};

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
        child.push_back(node);
    }

    void remove(std::string path) override 
    {
        throw "Current node (file) shouldn't have a child node!";
    }

    Node * getChildByName(const char * name) const override 
    {
        auto it = std::find_if(child.begin(), child.end(), IsMatchingName(name));
        if(it != child.end()){
            return *it;
        } else {
            return nullptr;
        }
        return nullptr;
    }

    Node * find(std::string path) override 
    {
        throw "Current node (file) shouldn't have a child node!";
    }

    int numberOfFiles() const override 
    {
        throw "Current node (file) shouldn't have a child node!";
    }

    Iterator * createIterator() override 
    {
        return new FolderIterator(this);
    }

    

private:
    std::string _name;
    std::string _path;
    
};


#endif // FOLDER
