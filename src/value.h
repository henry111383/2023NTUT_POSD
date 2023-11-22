#pragma once
#include <string>
#include "./value.h"
#include "./json_iterator.h"
#include "./visitor.h"

class Value {
public:
    Value(){};
    virtual ~Value(){};
    virtual std::string toString()=0;
    virtual JsonIterator * createIterator()=0;
    virtual void accept(JsonVisitor * visitor)=0;
};