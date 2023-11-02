#pragma once
#include "./visitor.h"
#include "./json_object.h"
#include "./string_value.h"

class BeautifyVisitor : public JsonVisitor {
public:

    void visitJsonObject(JsonObject * obj){
        std::string _result;
        auto it = obj->createIterator();
        _result += "{";
        for(it->first(); !it->isDone(); it->next()) {
            _result += "\n";
            _result += _blank;
            _result += "\"";
            _result += it->currentKey();
            _result += "\"";
            _result += ":";
            StringValue * isStringValue = dynamic_cast<StringValue*>(it->currentValue());
            if(isStringValue){
                _result += it->currentValue()->toString();
            }
            else{
                it->currentValue()->accept(this);
            }
            _result += ",";
        }
        std::size_t found = _result.find_last_of(",");
        _result = _result.substr(0,found);
        _result += "\n";
        _result += "}";
    };

    void visitStringValue(StringValue * val){
        _result += val->toString();
    };

    std::string getResult() const {

        std::cout<<_result;
        return _result + "\n}";
    };

private:
    std::string _result = "{\n";
    std::string _blank="";


};


// Line breaks after a '{',
// a ':' is placed right after the key with no whitespace between them,
// a space exists after a ':' before the value,
// a ',' exists right after the value if there is other key-value pairs left,
// line breaks after the end of each value, and
// the indent of each level is 4 spaces.
// {
//     "books": {
//         "design pattern": {
//             "name": "Design Patterns Elements of Reusable Object-Oriented Software",
//             "author": "Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides"
//         },
//         "clean code": {
//             "name": "Clean Code",
//             "author": "Robert C. Martin"
//         }
//     }
// }
