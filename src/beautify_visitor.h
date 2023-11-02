#pragma once
#include "./visitor.h"
#include "./json_object.h"
#include "./string_value.h"

class BeautifyVisitor : public JsonVisitor {
public:
    void visitJsonObject(JsonObject * obj){
        std::string tmp;
        auto it = obj->createIterator();
        for(it->first(); !it->isDone(); it->next()){
            _blank += "    ";
            tmp += _blank;
            tmp += "\"";
            tmp += it->currentKey();
            tmp += "\"";
            tmp += ":";
            tmp += it->currentValue()->toString();
        }
        _result += tmp;
    };

    void visitStringValue(StringValue * val){
        _result += val->toString();
    };

    std::string getResult() const {
        _result += "\n}"; 
        std::cout<<_result;
        return _result;
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
