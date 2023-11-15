#include "../src/file_system_parser.h"
#include "../src/file_system_builder.h"
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include <gtest/gtest.h>

TEST(ParserTest, ParserTestOK){
    std::string path = "structure/home";
    FileSystemBuilder *builder = new FileSystemBuilder();
    FileSystemParser *parser = new FileSystemParser(builder);

    parser->setPath(path);
    parser->parse();

    delete parser;

}
