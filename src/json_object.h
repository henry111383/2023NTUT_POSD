#pragma once
#include <string>
#include <map>
#include "./value.h"
#include "./string_value.h"
#include "./json_iterator.h"
#include "./visitor.h"


class JsonObject : public Value {

private:
    std::string _key;
    Value * _string_value;
    std::map<std::string, Value *> _myMap;

public:
class JsonObjectIterator : public JsonIterator {

    public:
        JsonObjectIterator(JsonObject* j){
            _itMap = j->_myMap;
        }
        void first() override {
            it = _itMap.begin();
        };

        std::string currentKey() const override {
            return it->first;
        };

        Value * currentValue() const override {
            return it->second;
        };

        void next() override {
            it++;
        };

        bool isDone() const override {
            if(it==_itMap.end()) return true;
            return false;
        };

    private:
        std::map<std::string, Value *> _itMap;
        std::map<std::string, Value *>::iterator it;
};

    JsonObject(){};
    JsonObject(std::string key):_key(key){};
    ~JsonObject(){};

    std::string toString() override {
        std::string result;
        JsonIterator* it = this->createIterator();
        result += "{";
        for(it->first(); !it->isDone(); it->next()){
            result += "\n";
            result += "\"";
            result += it->currentKey();
            result += "\"";
            result += ":";
            result += it->currentValue()->toString();
            result += ",";
        }
        std::size_t found = result.find_last_of(",");
        result = result.substr(0,found);
        result += "\n";
        result += "}";
        return result;
    }
    
    JsonIterator * createIterator() override {
        return new JsonObjectIterator(this);
    };

    void set(std::string key, Value * value){
        _key = key;
        _string_value = value;
        _myMap.insert (std::pair<std::string, Value *>(key, value));
    }

    Value * getValue(std::string key){
        auto it = this->createIterator();
        for(it->first(); !it->isDone(); it->next())
        {
            if(it->currentKey()==key){
                return it->currentValue();
            }
        }
        return nullptr;
    }

    void accept(JsonVisitor * visitor) override {
        visitor->visitJsonObject(this);
    }

    std::string getKey(){
        return _key;
    }
};



