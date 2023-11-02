#pragma once
#include <map>
#include <list>
#include <stack>
#include "./json_object.h"
#include "./string_value.h"

class JsonBuilder {
public:
    void buildValue(std::string key, std::string value){
        StringValue *_value = new StringValue(value);
        JsonObject *tmpJson = new JsonObject();
        tmpJson->set(key, _value);
        
        if (_compounds.empty()) {
            _jsons.push_back(tmpJson);
        } else {
            _compounds.top()->set(key, _value);
        }
        _result = _jsons.front();
    };

    void buildObject(){
        _compounds.push(new JsonObject());
    };

    void buildObject(std::string key){
        _compounds.push(new JsonObject(key));
    };

    void endObject(){
        if (!_compounds.empty()) {
            JsonObject * compound = _compounds.top();
            _compounds.pop();
            if (_compounds.empty()) {
                _jsons.push_back(compound);
            } else {
                _compounds.top()->set(_compounds.top()->getKey(), compound);
            }
            _result = compound;
        }
        
    };

    JsonObject * getJsonObject(){
        return _result;
    };

private:
    JsonObject *_result;
    std::list<JsonObject *> _jsons;
    std::stack<JsonObject *> _compounds;
};
