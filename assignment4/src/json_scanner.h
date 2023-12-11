#pragma once

#include <string>
#include <sstream>

class JsonScanner {
public:
    void setInput(std::string input) {
        _input = input;
        ss.str(_input);
    }

    char next() {
        char token;
        if(ss.get(token)){
            return token;
        } else if (ss.eof()){
            return '\0';
        } else {
            return '\0';
        }
        
    }
    
    bool isDone() const {
        return ss.eof();
    }

private:
    std::string _input;
    std::stringstream ss;
};
