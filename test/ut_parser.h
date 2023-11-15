#include "../src/file_system_parser.h"
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include <gtest/gtest.h>

TEST(ParserTest, ParserTestOK){
    std::string _path = "OK";
    std::string name = "name";
    std::cout << (_path + "/" + name) << std::endl;

}
