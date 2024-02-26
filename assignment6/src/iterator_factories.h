#pragma once

#include "iterator_factory.h"
#include "folder.h"

class FolderIteratorFactory: public IteratorFactory {
public:
    static IteratorFactory * instance() {
        if(_instance == nullptr){
            _instance = new FolderIteratorFactory();
        }
        return _instance;
    }
    
private:
    Iterator * create(Folder * node, int operationCount) override {
        return new Folder::FolderIterator(node, operationCount);
    };

private:
    static IteratorFactory *_instance;
};

class OrderByNameIteratorFactory: public IteratorFactory {
public:
    static IteratorFactory * instance() {
        if(_instance == nullptr){
            _instance = new OrderByNameIteratorFactory();
        }
        return _instance;
    }

private:
    Iterator * create(Folder * node, int operationCount) override {
        return new Folder::OrderByNameIterator(node, operationCount);
    };

private:
    static IteratorFactory *_instance;
};

class OrderByNameWithFolderFirstIteratorFactory: public IteratorFactory {
public:
    static IteratorFactory * instance() {
        if(_instance == nullptr){
            _instance = new OrderByNameWithFolderFirstIteratorFactory();
        }
        return _instance;
    }

private:
    Iterator * create(Folder * node, int operationCount) override {
        return new Folder::OrderByNameWithFolderFirstIterator(node, operationCount);
    };

private:
    static IteratorFactory *_instance;
};

class OrderByKindIteratorFactory: public IteratorFactory {
public:
    static IteratorFactory * instance() {
        if(_instance == nullptr){
            _instance = new OrderByKindIteratorFactory();
        }
        return _instance;
    }

private:
    Iterator * create(Folder * node, int operationCount) override {
        return new Folder::OrderByKindIterator(node, operationCount);
    };

private:
    static IteratorFactory *_instance;
};

IteratorFactory *FolderIteratorFactory::_instance = nullptr;
IteratorFactory *OrderByNameIteratorFactory::_instance = nullptr;
IteratorFactory *OrderByNameWithFolderFirstIteratorFactory::_instance = nullptr;
IteratorFactory *OrderByKindIteratorFactory::_instance = nullptr;
