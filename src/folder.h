#pragma once
#if !defined(FOLDER)
#define FOLDER

#include <string>
#include <map>
#include "./iterator.h"
#include "./null_iterator.h"
#include "./node.h"


class Folder: public Node {
public:
    std::map<std::string, Node *> ChildMap;

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
        ChildMap[node->name()] = node;
    }

    void remove(std::string path) override 
    {
        throw "Current node (file) shouldn't have a child node!";
    }

    Node * getChildByName(const char * name) const override 
    {
        auto it = ChildMap.find(name);
        if(it != ChildMap.end()){
            return it->second;
        } else {
            return nullptr;
        }
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
