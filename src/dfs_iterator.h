#if !defined(DFS_ITERATOR_H)
#define DFS_ITERATOR_H
#include "node.h"
#include <stack>
#include <list>
class Node;

class DfsIterator: public Iterator {
public:
    DfsIterator(Node* composite):_node(composite)
    {
        this -> first();
    };

    void first() 
    {
        _current = _node -> child.begin();
    };


    Node * currentItem() const 
    {
        if (this->isDone()){
            throw std::string("No current item!");
        }
        return *_current;
    };

    void next() 
    {
        if (this->isDone()){
            throw std::string("Moving past the end!");
        }
        _current++;
    };

    bool isDone() const 
    {
        return _current == _node->child.end();
    };
private:
    std::stack<Node*> MyStk;  
    std::list<Node*> DFSlist;
    Node *_node;
    std::list<Node *>::iterator _current;
    
    
    void DFS()
    {
    }


};

class BfsIterator: public Iterator {
public:
    BfsIterator(Node* composite);
    void first();
    Node * currentItem() const;
    void next();
    bool isDone() const;

private:
    // std::queue<Node*> MyQue; 
    // Node *node;   
};

#endif // DFS_ITERATOR_H
