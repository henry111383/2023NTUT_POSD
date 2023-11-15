#pragma once

#include <string>

#include "folder.h"
#include "file_system_builder.h"
#include "file_system_scanner.h"

using std::string;

class FileSystemParser {
private:


public:
    FileSystemParser(FileSystemBuilder * builder): _builder(builder){
        
    };

    ~FileSystemParser(){};

    Folder * getRoot() const {
        return _builder->getRoot();
    };

    void parse(){
        FileSystemScanner *_scanner = new FileSystemScanner();
        _scanner->setPath(_path);
        
        _scanner->nextNode();
        while(!_scanner->isDone()){
            std::string name = _scanner->currentNodeName();

            if(name == ".") {
                _scanner->nextNode();
                continue;
            }
            if(name == "..") {
                _scanner->nextNode();
                continue;
            }

            if(_scanner->isFile()){
                _builder->buildFile((_path + "/" + name));
            }
            else if(_scanner->isFolder()){
                FileSystemParser *parser = new FileSystemParser(_builder);
                parser->setPath((_path + "/" + name));
                parser->parse();
                delete parser;

                _builder->endFolder();
                std::cout << "endFolder~!!!" << std::endl;
                
            }
        
            _scanner->nextNode();
        }
        _builder->endFolder();

        delete _scanner;
    };

    void setPath(string path){
        _path = path;
        _builder->buildFolder(_path);
    };

private:
    std::string _path;
    FileSystemScanner *_scanner;
    FileSystemBuilder *_builder;
};
