#include "../src/file_system_parser.h"
#include "../src/file_system_builder.h"
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include <gtest/gtest.h>

TEST(ParserTest, ParserShouldbeCorrectlyBuilt){
    std::string path = "structure/home";
    FileSystemBuilder *builder = new FileSystemBuilder();
    FileSystemParser *parser;
    ASSERT_NO_THROW(parser = new FileSystemParser(builder));
    delete parser;
}

TEST(ParserTest, ParserSetPathShouldNotThrow){
    std::string path = "structure/home";
    FileSystemBuilder *builder = new FileSystemBuilder();
    FileSystemParser *parser;
    ASSERT_NO_THROW(parser = new FileSystemParser(builder));
    ASSERT_NO_THROW(parser->setPath(path));
    delete parser;
}

TEST(ParserTest, ParserParseShouldNotThrow){
    std::string path = "structure/home";
    FileSystemBuilder *builder = new FileSystemBuilder();
    FileSystemParser *parser;
    ASSERT_NO_THROW(parser = new FileSystemParser(builder));
    ASSERT_NO_THROW(parser->setPath(path));
    ASSERT_NO_THROW(parser->parse());
    delete parser;
}

TEST(ParserTest, ParserGetRootShouldbeCorrect){
    std::string path = "structure/home";
    FileSystemBuilder *builder = new FileSystemBuilder();
    FileSystemParser *parser;
    ASSERT_NO_THROW(parser = new FileSystemParser(builder));
    ASSERT_NO_THROW(parser->setPath(path));
    ASSERT_NO_THROW(parser->parse());
    Folder *root;
    ASSERT_NO_THROW(root = parser->getRoot());
    ASSERT_EQ(root->numberOfFiles(), 11);
    delete parser;
}

TEST(ParserTest, ParserAllShouldbeCorrect){
    std::string path = "structure/home";
    FileSystemBuilder *builder = new FileSystemBuilder();
    FileSystemParser *parser;
    ASSERT_NO_THROW(parser = new FileSystemParser(builder));
    ASSERT_NO_THROW(parser->setPath(path));
    ASSERT_NO_THROW(parser->parse());
    Folder *root;
    ASSERT_NO_THROW(root = parser->getRoot());
    ASSERT_EQ(root->numberOfFiles(), 11);

    TreeVisitor *visitor = new TreeVisitor(OrderBy::Kind);
    visitor->visitFolder(root);
    std::string res = visitor->getTree();
    std::string expected;
    expected += ".\n";
    expected += "├── my_profile\n";
    expected += "├── Documents\n";
    expected += "│   ├── programming\n";
    expected += "│   │   ├── oop.pdf\n";
    expected += "│   │   ├── cpp.pub\n";
    expected += "│   │   └── python.pub\n";
    expected += "│   ├── clean-architecture.pdf\n";
    expected += "│   ├── object-oriented-analysis-and-design.pdf\n";
    expected += "│   ├── domain-driven-design.pub\n";
    expected += "│   ├── hello.txt\n";
    expected += "│   └── note.txt\n";
    expected += "├── Downloads\n";
    expected += "│   └── funny.png\n";
    expected += "└── hello.txt\n";
    // std::cout << res <<std::endl;
    ASSERT_EQ(res, expected);
    
    delete visitor;
    delete parser;
}
