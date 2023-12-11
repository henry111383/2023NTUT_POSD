#pragma once
#include "./visitor.h"
#include "./json_object.h"
#include "./string_value.h"

class BeautifyVisitor : public JsonVisitor {
public:
    BeautifyVisitor(){}

    void visitJsonObject(JsonObject * obj){
        auto it = obj->createIterator();
        _result += "{";
        level++;
        for(it->first(); !it->isDone(); it->next()) {
            _result += '\n';
            addOpening();
            _result += '\"';
            _result += it->currentKey();
            _result += '\"';
            _result += ": ";
            it->currentValue()->accept(this);
            _result += ",";
        }
        level--;
        std::size_t found = _result.find_last_of(",");
        _result = _result.substr(0, found);
        _result += "\n";
        addOpening();
        _result += "}";
        delete it;
    };

    void visitStringValue(StringValue * val){
        _result += val->toString();
    };

    std::string getResult() const {
        return _result;
    };

private:
    std::string _result;
    std::string _blank="    ";
    int level =0;

    void addOpening(){
        for(int i=0; i<level; i++){
            _result += _blank;
        }
    }
};