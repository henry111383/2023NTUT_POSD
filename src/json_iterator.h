#pragma once
#include "./json_object.h"

class Value;

class JsonIterator {
public:
    virtual void first() = 0;

    virtual std::string currentKey() const = 0;

    virtual Value * currentValue() const = 0;

    virtual void next() = 0;
    
    virtual bool isDone() const = 0;
};

class NullIterator : public JsonIterator {
public:
    void first() override
    {
        throw std::string("no child member");
    }
    std::string currentKey() const override
    {
        throw std::string("no child member");
    }
    Value *currentValue() const override
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


