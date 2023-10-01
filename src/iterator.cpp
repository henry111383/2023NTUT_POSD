#include "folder.h"
#include "iterator.h"


FolderIterator::FolderIterator(Folder* composite):_folder(composite){
    this -> first();
};

void FolderIterator::first() 
{
    _current = _folder -> ChildMap.begin();
};


Node * FolderIterator::currentItem() const 
{
    if (_folder->ChildMap.empty() || this->isDone()){
        throw std::string("No current item!");
    }
    return _current->second;
};

void FolderIterator::next() 
{
    if (_folder->ChildMap.empty() || this->isDone()){
        throw std::string("Moving past the end!");
    }
    _current++;
};

bool FolderIterator::isDone() const 
{
    return _current == _folder->ChildMap.end();
};

