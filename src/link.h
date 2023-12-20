#pragma once
#include <stdio.h>
#include "node.h"
#include "visitor.h"

class Link: public Node {
private:
    Node * _target = nullptr; 

public:
    Link(std::string path, Node * target): Node(path), _target(target) {
        std::cout << path << std::endl;
        struct stat fileInfo;
        const char *c = path.c_str();
        if(lstat(c, &fileInfo) == 0){ // check link
            if(S_ISLNK(fileInfo.st_mode))
                // struct stat fileInfo;
                // const char *c = path.c_str();
                // if(lstat(c, &fileInfo) == 0){ // check target
                //     if(S_ISLNK(fileInfo.st_mode)){
                //         return;
                //     }
                // }
                return;
        }
        throw "No Link exists";
    }

    Node * getTarget() {
        return _target;
    }
    
    int numberOfFiles() const override {
        if(_target!=nullptr){
            return _target->numberOfFiles();
        }
        throw "error";
    }

    Node * find(string path) override {
        if(_target!=nullptr){
            return _target->find(path);
        }
        throw "error";
    }

    std::list<string> findByName(string name) override {
        if(_target!=nullptr){
            return _target->findByName(name);
        }
        throw "error";
    }

    void add(Node *node) override {
        if(_target!=nullptr){
            _target->add(node);
        }
        throw "error";
    }

    void remove(std::string path) override {
        if(_target!=nullptr){
            _target->remove(path);
        }
        throw "error";
    }

    Node * getChildByName(const char * name) const override {
        if(_target!=nullptr){
            return _target->getChildByName(name);
        }
        throw "error";
    }
    void accept(Visitor * visitor) override {
        visitor->visitLink(this);
    }

    void updateChildren() override {
        if(_target!=nullptr){
            _target->updateChildren();
        }
        throw "error";
    };

};
