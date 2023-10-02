#pragma once
#if !defined(ITERATOR_H)
#define ITERATOR_H


#include <list>

class Node;
class Folder;

class Iterator {
public:
    virtual ~Iterator(){};
    virtual void first() = 0;
    virtual Node * currentItem() const = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
};



class FolderIterator : public Iterator {
public:
    FolderIterator(Folder* composite);
    void first() override;
    Node *currentItem() const override;
    void next() override;
    bool isDone() const override;

private:
    Folder * _folder;
    std::list<Node *>::iterator _current;
};


#endif // ITERATOR_H
