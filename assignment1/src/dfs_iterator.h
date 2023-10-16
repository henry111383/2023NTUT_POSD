#pragma once
#if !defined(DFS_ITERATOR_H)
#define DFS_ITERATOR_H
#include "node.h"
#include "folder.h"
#include <stack>
#include <queue>
#include <list>


// ========= DFSIterator ========= 
class DfsIterator: public Iterator {
public:
    DfsIterator(Node* composite):_node(composite){};

    void first() 
    {
        DFS();
        _current = DFSlist.begin();
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
        return _current == DFSlist.end();
    };

private:
    std::list<Node*> DFSlist;
    Node *_node;
    std::list<Node *>::iterator _current;
    
    void DFS()
    {
        std::stack<std::pair<Node*, int>> MyStk;
        /* ---------------------------------
        Algorithm:
        (1) Push node's children in stack.
        (2) If top of stack is a leaf, pop it and put it in list.
        (3) If top of stack is a not traveled non-leaf, don't pop and push its children in stack.
        (4) If top of stack is a traveled non-leaf, pop it and put it in list.
        (5) Check (2)(3)(4) until stack is empty.
        (6) Reverse the list and it is the result.
           --------------------------------- */
        
        if(_node->child.empty()) return;
        MyStk.push(std::make_pair(_node, 0));

        Node *tmp;
        while(!MyStk.empty())
        {
            tmp = MyStk.top().first;
            // std::cout << tmp->name();
            bool isleaf = MyStk.top().first->child.empty();
            bool istraveled = (MyStk.top().second == 1);
            if(!isleaf && !istraveled)
            {
                MyStk.top().second = 1;
                for(Node *ch : tmp->child) 
                {
                    MyStk.push(std::make_pair(ch, 0));
                }
            } else
            {
                DFSlist.push_back(tmp);
                MyStk.pop();
            }
        }
        DFSlist.reverse();
        DFSlist.pop_front();

        // Checking 
        // for(Node * tt : DFSlist) 
        // {
        //     std::cout << tt->name();
        // }
    }


};


// ========= BFSIterator ========= 
class BfsIterator: public Iterator {
public:
    BfsIterator(Node* composite):_node(composite){};
    
    void first() 
    {
        BFS();
        _current = BFSlist.begin();
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
        return _current == BFSlist.end();
    };

private:
    std::list<Node*> BFSlist;
    Node *_node;
    std::list<Node *>::iterator _current;
    
    void BFS()
    {
        std::queue<Node*> MyQue;
        /* ---------------------------------
        Algorithm:
        (1) Push node's children in queue.
        (2) If first element is a leaf, pop it and put it in list.
        (3) If first element is a non-leaf, pop it, put it in list and push its children in queue.
        (4) Check (2)(3) until queue is empty.
        (5) The list is the result.
           --------------------------------- */

        if(_node->child.empty()) return;
        MyQue.push(_node);
        
        Node *tmp;
        while(!MyQue.empty())
        {
            tmp = MyQue.front();
            bool isleaf = tmp->child.empty();
            if(!isleaf){
                for(Node *ch : tmp->child) 
                {
                    MyQue.push(ch);
                }
            }
            MyQue.pop();
            BFSlist.push_back(tmp);
        }
        BFSlist.pop_front();

        // Checking 
        // for(Node * tt : BFSlist) 
        // {
        //     std::cout << tt->name();
        // }
    }
};

#endif // DFS_ITERATOR_H
