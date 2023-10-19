#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"
#include "iterator.h"

class FindByNameVisitor : public Visitor {
public:
    FindByNameVisitor(string name): _name(name){};

    void visitFile(File * file) override {
        if (file->name() == _name) {
            _pathList.push_back(file->path());
        }
    };

    void visitFolder(Folder * folder) override {
        if (folder->name() == _name) {
            _pathList.push_back(folder->path());
        }

        Iterator *it = folder->createIterator(); 
        for (it->first(); !it->isDone(); it->next()) {
            it->currentItem()->accept(this);
        }
        delete it;
    };

    std::list<string> getPaths() const {
        return _pathList;
    };


private:
    std::string _name;
    std::list<string> _pathList;
};