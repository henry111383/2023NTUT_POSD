#pragma once

#include <list>
#include "node.h"
#include "iterator.h"
#include "dfs_iterator.h"

using namespace std;

class Folder: public Node {
    
private:
    list<Node *> _nodes;
    int _version = 1; //用來判斷資料夾底下結構有沒有變化

protected:
    void removeChild(Node * target) {
        _nodes.remove(target);
        _version++;
    }

public:
class FolderIterator : public Iterator {

    public:
        FolderIterator(Folder* composite):_host(composite), _version(composite->_version) {}

        FolderIterator(Folder* composite, int version):_host(composite), _version(version) {}

        ~FolderIterator() {}

        void first() {
            // if(_version != (_host->_version)) {
            //     std::cout << _host->_version << _version <<std::endl;
            //     throw "Structure has changed...";
            // }
                
            _current = _host->_nodes.begin();
        }

        Node * currentItem() const {
            if(_version != (_host->_version)) {
                std::cout << _host->_version << _version <<std::endl;
                throw "Structure has changed...";
            }
            return *_current;
        }

        void next() {
            if(_version != (_host->_version)) {
                std::cout << _host->_version << _version <<std::endl;
                throw "Structure has changed...";
            }
            _current++;
        }

        bool isDone() const {
            // if(_version != (_host->_version)) {
            //     std::cout << _host->_version << _version <<std::endl;
            //     throw "Structure has changed...";
            // }
            return _current == _host->_nodes.end();
        }

        
    private:
        Folder* const _host;
        int _version=1;
        std::list<Node *>::iterator _current;
    };    


public:
    Folder(string path): Node(path) {
        if (nodeType != "folder")
            throw(std::string("It is not Folder!"));
    }

    void add(Node * node) {
        if (node->path() != this->path() + "/" + node->name()) {
            throw string("Incorrect path of node: " + node -> path());
        }
        _nodes.push_back(node);
        node->parent(this);
        _version++;
    }

    Node * getChildByName(const char * name) const {
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            if ((*it)->name() == name) {
                return *it;
            }
        }
        return nullptr;
    }

    int numberOfFiles() const {
        int num = 0;
        if (_nodes.size() == 0) {
            return 0;
        }
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            num += (*it)->numberOfFiles();
        }
        return num;
    }

    Iterator * createIterator() {
        return new FolderIterator(this, _version);
    }

    Iterator * dfsIterator() {
        return new DfsIterator(this);
    }

    Node * find(string path) {
        if (this->path() == path) {
            return this;
        }

        size_t index = path.find(this->path());

        if (string::npos == index) {
            return nullptr;
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            Node * result = (*it)->find(path);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }

    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            std::list<string> paths = (*it)->findByName(name);
            for (auto i = paths.begin(); i != paths.end(); i++)
            {
                pathList.push_back(*i);  
            }
        }

        return pathList;
    }

    void remove(string path) {
        Node * target = find(path);
        if (target) {
            target->parent()->removeChild(target);
        }
    }

    void accept(Visitor * visitor) {
        visitor->visitFolder(this);
    }
};



