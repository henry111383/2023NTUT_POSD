#pragma once
#if !defined(FILE_H)
#define FILE_H
#include <string>

class File: public Node {

public:
    File(std::string path);

private:
    std::string _name;
    std::string _path;

};

#endif // FILE_H
