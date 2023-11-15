#include "../src/file_system_scanner.h"
#include <gtest/gtest.h>

TEST(ScannerTest, OK){
    std::string name;
    FileSystemScanner *scanner = new FileSystemScanner();
    ASSERT_NO_THROW(scanner->setPath("structure/home"));

    // std::cout << scanner->isDone() << std::endl;
    scanner->nextNode();
    while(!scanner->isDone()){
        name = scanner->currentNodeName();
        std::cout << name << std::endl;
        scanner->nextNode();
    }
    // ASSERT_NO_THROW(scanner->nextNode());
    // ASSERT_FALSE(scanner->isDone());
    // ASSERT_NO_THROW(name = scanner->currentNodeName());
    // ASSERT_EQ(name, ".");
    // ASSERT_FALSE(scanner->isFile());
    // ASSERT_TRUE(scanner->isFolder());

    // ASSERT_NO_THROW(scanner->nextNode());
    // ASSERT_FALSE(scanner->isDone());
    // ASSERT_NO_THROW(name = scanner->currentNodeName());
    // ASSERT_EQ(name, "..");
    // ASSERT_FALSE(scanner->isFile());
    // ASSERT_TRUE(scanner->isFolder());

    // ASSERT_NO_THROW(scanner->nextNode());
    // ASSERT_FALSE(scanner->isDone());
    // ASSERT_NO_THROW(name = scanner->currentNodeName());
    // ASSERT_EQ(name, "Documents");
    // ASSERT_FALSE(scanner->isFile());
    // ASSERT_TRUE(scanner->isFolder());

    // ASSERT_NO_THROW(scanner->nextNode());
    // ASSERT_FALSE(scanner->isDone());
    // ASSERT_NO_THROW(name = scanner->currentNodeName());
    // ASSERT_EQ(name, "Downloads");
    // ASSERT_FALSE(scanner->isFile());
    // ASSERT_TRUE(scanner->isFolder());

    // ASSERT_NO_THROW(scanner->nextNode());
    // ASSERT_FALSE(scanner->isDone());
    // ASSERT_NO_THROW(name = scanner->currentNodeName());
    // ASSERT_EQ(name, "hello.txt");
    // ASSERT_TRUE(scanner->isFile());
    // ASSERT_FALSE(scanner->isFolder());

    
    // ASSERT_NO_THROW(scanner->nextNode());
    // ASSERT_FALSE(scanner->isDone());
    // ASSERT_NO_THROW(name = scanner->currentNodeName());
    // ASSERT_EQ(name, "my_profile");
    // ASSERT_TRUE(scanner->isFile());
    // ASSERT_FALSE(scanner->isFolder());

    // ASSERT_NO_THROW(scanner->nextNode());
    // ASSERT_TRUE(scanner->isDone());

    delete scanner;
}