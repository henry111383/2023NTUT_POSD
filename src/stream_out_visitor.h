#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"
#include "iterator.h"
#include <fstream>
#include <iostream>
#include <sstream>

class StreamOutVisitor : public Visitor {
public:

    void visitFile(File * file){
        std::ifstream ifs;
        std::string content;
        std::string buffer;

        ifs.open(file->path());
        if (!ifs.is_open()) {
            throw "Opening failed...";
        }

        _result += "_____________________________________________\n";
        _result += file->path();
        _result += "\n";
        _result += "---------------------------------------------\n";

        while (std::getline(ifs, buffer)) {
            content += buffer;
            content += "\n";
            std::cout << buffer << std::endl;
        }

        ifs.close();
        _result += content;
        _result += "_____________________________________________\n";
    };

    void visitFolder(Folder * folder){
        Iterator *it = folder->createIterator(); 
        for (it->first(); !it->isDone(); it->next()) {
            it->currentItem()->accept(this);
        }
        delete it;
    };

    string getResult() const{
        return _result;
    };

private:
    string _result;
};