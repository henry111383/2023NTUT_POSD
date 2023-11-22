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
            JsonObject * compound = _compounds.top().second;
            compound->set(key, _value);
        }
        // _result = _jsons.front();
    };

    void buildObject(std::string key){
        JsonObject *tmpJson = new JsonObject();
        _compounds.push(std::make_pair(key, tmpJson));
    };

    void endObject(){
        if (!_compounds.empty()) {
            JsonObject * compound = _compounds.top().second;
            std::string _key = _compounds.top().first;
            _compounds.pop();
            if (_compounds.empty()) {
                JsonObject *json = new JsonObject();
                json->set(_key, compound);
                _jsons.push_back(json);
            } else {
                _compounds.top().second->set(_key, compound);
            }
        }
    };

    JsonObject * getJsonObject(){
        _result = _jsons.front();
        return _result;
    };

private:
    JsonObject *_result;
    std::list<JsonObject *> _jsons;
    std::stack<std::pair<std::string, JsonObject *>> _compounds;
};
