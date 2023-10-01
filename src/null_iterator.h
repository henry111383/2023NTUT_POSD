#pragma once
#if !defined(NULL_ITERATOR_H)
#define NULL_ITERATOR_H

class NullIterator : public Iterator {
public:
    void first() override
    {
        throw std::string("no child member");
    }
    Node *currentItem() const override
    {
        throw std::string("no child member");
    }
    void next() override
    {
        throw std::string("no child member");
    }
    bool isDone() const override
    {
        return true;
    }
};

#endif // NULL_ITERATOR_H
