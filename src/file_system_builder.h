#pragma once

#include <string>
#include <list>
#include <stack>


#include "folder.h"

using std::string;

class FileSystemBuilder {
public:
    Folder * getRoot() const{
        // return dynamic_cast<Folder*>(_files.back());
        return nullptr;
    };

    void buildFile(string path){
        Node *file = new File(path);
        if(_folders.empty()){
            _files.push_back(file);
        } else {
            _folders.top()->add(file);
        }
    };

    void buildFolder(string path){
        _folders.push(new Folder(path));
    };

    void endFolder(){
        if(!_folders.empty()){
            Folder *folder = _folders.top();
            _folders.pop();
            if(_folders.empty()){
                _files.push_back(folder);
            } else {
                _folders.top()->add(folder);
            }
        }
    };

private:
    std::list<Node *> _files;
    std::stack<Folder *> _folders;
};
