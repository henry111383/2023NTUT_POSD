#pragma once

#include <string>

#include "folder.h"
#include "file_system_builder.h"
#include "file_system_scanner.h"

using std::string;

class FileSystemParser {
private:


public:
    FileSystemParser(FileSystemBuilder * builder): _builder(builder);

    Folder * getRoot() const;

    void parse();

    void setPath(string path);
};
