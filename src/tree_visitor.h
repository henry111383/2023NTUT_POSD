#pragma once

#include "visitor.h"
#include "order_by.h"
#include "iterator_factories.h"

class TreeVisitor: public Visitor {
public:
    TreeVisitor(OrderBy orderBy): _orderBy(orderBy), _currentLevel(0), _notEndLevel(0) {
        if(_orderBy == OrderBy::Normal){
            _factory = new FolderIteratorFactory();
        }
        else if (_orderBy == OrderBy::Name)
        {
            _factory = new OrderByNameIteratorFactory();
        }
        else if (_orderBy == OrderBy::NameWithFolderFirst)
        {
            _factory = new OrderByNameWithFolderFirstIteratorFactory();
        }
        else{
            _factory = new OrderByKindIteratorFactory();
        }
    }
    TreeVisitor(IteratorFactory *factory): _factory(factory){}

    void visitFile(File * file) {
        _result += file->name() + "\n";
    }
    void visitFolder(Folder * folder) {
        if (_result == "") {
            _result += ".\n";
        } else {
            _result += folder->name() + "\n";
        }

        // Iterator * it = folder->createIterator(_orderBy);
        Iterator * it = folder->createIterator(_factory);
        it->first();
        while (!it->isDone()) {
            Node * current = it->currentItem();
            it->next();

            ++_currentLevel;
            int notEndLevel = _notEndLevel;
            for (int i = 1; i < _currentLevel; ++i) {
                if (i <= _notEndLevel) {
                    _result += "│   ";
                } else {
                    _result += "    ";
                }
            }

            if (it->isDone()) {
                _result += "└── ";
            } else {
                _result += "├── ";
                ++_notEndLevel;
            }
            current->accept(this);

            --_currentLevel;
            _notEndLevel = notEndLevel;
        }
    }

    void visitLink(Link * link) override {
        _result += link->name() + "\n";
    }

    string getTree() {
        return _result;
    }

private:
    OrderBy _orderBy;
    std::string _result;
    int _currentLevel;
    int _notEndLevel;
    IteratorFactory *_factory;
};