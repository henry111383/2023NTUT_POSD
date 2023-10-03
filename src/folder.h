#pragma once
#if !defined(FOLDER)
#define FOLDER

#include <string>
#include <list>
#include <algorithm>
#include "iterator.h"
#include "null_iterator.h"
#include "node.h"
#include "file.h"
#include "dfs_iterator.h"

struct IsMatchingName {
    IsMatchingName(const std::string& key) : key_(key) {}
    bool operator()(const Node* node) const {
        return (node->name()) == key_;
    }
    std::string key_;
};

class Folder: public Node {
public:

    Folder(std::string path):_path(path) 
    {
        _name = _path.substr(_path.find_last_of("/\\") + 1);
        nodeType = "Folder";
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
        std::string parent_path;
        parent_path = node->path().substr(0, node->path().find_last_of("/\\"));
        if(parent_path == (this->path()) )
        {
            child.push_back(node);
            node->parentFolder = this;
        } else {
            throw "worng path...";
        }
    }

    void remove(std::string path) override 
    {
        Node *node = this->find(path);
        if(node)
        { 
            node->parentFolder->child.remove(node);
        } else {
            throw "not existing file or folder";
        }
        
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
        for(auto it=child.begin();it!=child.end();it++)
        {
            if(((*it) -> path())==path) return *it;
            Folder *isFolder = dynamic_cast<Folder*>(*it);
            if(isFolder)
            {
                Node *isFind = (*it)->find(path);
                if(isFind){
                    return isFind;
                }
            }
        }
        return nullptr;
    }

    int numberOfFiles() const override 
    {
        int num =0;
        for(auto it=child.begin();it!=child.end();it++)
        {
            File *isFile = dynamic_cast<File*>(*it);
            if(isFile)
            {
                num++;
            } else {
                num += (*it)->numberOfFiles();
            }
        }
        return num;
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
