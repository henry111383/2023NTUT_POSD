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
        addOpening();
        MyResult += file->name();
        MyResult += '\n';
    };

    void visitFolder(Folder * folder) override {
        addOpening();
        MyResult += folder->name();
        MyResult += '\n';
        level++;
        levelisDone.push_back(false);
        Iterator *it = folder->createIterator(_orderBy);
        for(it->first();!it->isDone();){
            Node* tmp = it->currentItem();
            it->next();
            opening = "├";
            if(it->isDone()){
                levelisDone[level-1] = true;
                opening = "└";
                // MyResult += "endChild\n";
            }
            tmp -> accept(this);
        }
        delete it;
        level--;
    };

    std::string getTree(){
        auto index = MyResult.find_first_of("\n");
        MyResult.erase(0, index-1);
        MyResult[0] = '.';
        return MyResult;
    };

private:
    OrderBy _orderBy;
    std::string MyResult;
    std::string opening;
    int level = 0;
    std::vector<bool> levelisDone;

    void addOpening(){
        for(int j=0; j<level; j++){
            if(j==(level-1)){
                MyResult += opening;
                MyResult += "── ";
            }
            else{
                if(!levelisDone[j]){
                MyResult += "│   ";
                }
                else{
                    MyResult += "    "; 
                }
            }  
        }
    }
};