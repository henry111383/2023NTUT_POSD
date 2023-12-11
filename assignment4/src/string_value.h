#pragma once
#include <string>
#include "./json_iterator.h"
#include "./visitor.h"

class StringValue : public Value {
public:
    // StringValue(std::string key, std::string value):_key(key),_value(value){};
    StringValue(std::string value):_value(value){};
    ~StringValue(){};

    std::string toString() override {
        std::string result;
        result += "\"";
        result += _value;
        result += "\"";
        return result;
    };

    JsonIterator * createIterator() override {
        return new NullIterator();
    };

    void accept(JsonVisitor * visitor) override {
        visitor->visitStringValue(this);
    }
    
private:
    std::string _key;
    std::string _value;
};