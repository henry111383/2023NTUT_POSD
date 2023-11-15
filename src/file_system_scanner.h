#pragma once

#include <string>
#include <dirent.h>

using std::string;

class FileSystemScanner {
public:
    FileSystemScanner(){};
    ~FileSystemScanner(){
        closedir(dir);
    };

    bool isFile(){
        return entry->d_type == DT_REG;
    };

    bool isFolder(){
        return entry->d_type == DT_DIR;
    };

    bool isDone(){
        return entry == NULL;
    };

    void setPath(string path){
        _path = path;
        dir = opendir(path.c_str());

    };

    string currentNodeName(){
        return entry->d_name;
    };

    void nextNode(){
        entry = readdir(dir);
    };

private:
    std::string _path;
    DIR *dir;
    struct dirent* entry;
};
