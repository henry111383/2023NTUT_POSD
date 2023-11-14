#pragma once

#include "visitor.h"
#include "order_by.h"
#include "iterator.h"
#include "node.h"
#include <vector>

class TreeVisitor: public Visitor {
public:
    TreeVisitor(OrderBy orderBy) : _orderBy(orderBy){
        level=0;
    };

    ~TreeVisitor(){};

    void visitFile(File * file) override {
        MyResult += file->name();
        MyResult += '\n';
    };

    void visitFolder(Folder * folder) override {
        MyResult += folder->name();
        MyResult += '\n';

        level++;
        Iterator *it = folder->createIterator(_orderBy);
        for(it->first();!it->isDone();it->next()){
            it->currentItem()->accept(this);
        }
        delete it;
        level--;
    };

    std::string getTree(){
        return MyResult;
    };

private:
    OrderBy _orderBy;
    std::string MyResult;
    std::string opening;
    int level = 0;
};