#include "../src/file_system_scanner.h"
#include <gtest/gtest.h>
#include <set>

TEST(ScannerTest, ScannerShouldbeCorrectlyBuilt){
    FileSystemScanner *scanner;
    ASSERT_NO_THROW(scanner = new FileSystemScanner());
    delete scanner;
}

TEST(ScannerTest, ScannerSetPathShouldNotThrow){
    FileSystemScanner *scanner;
    ASSERT_NO_THROW(scanner = new FileSystemScanner());
    ASSERT_NO_THROW(scanner->setPath("structure/home"));
    delete scanner;
}

TEST(ScannerTest, ScannerNextNodeShouldNotThrow){
    FileSystemScanner *scanner;
    ASSERT_NO_THROW(scanner = new FileSystemScanner());
    ASSERT_NO_THROW(scanner->setPath("structure/home"));
    ASSERT_NO_THROW(scanner->nextNode());
    delete scanner;
}


TEST(ScannerTest, ScannerAllShouldbeCorrectlyBuilt){
    std::string name;
    FileSystemScanner *scanner = new FileSystemScanner();
    ASSERT_NO_THROW(scanner->setPath("structure/home"));

    std::set<std::string> expected;
    std::set<std::string> res;
    std::set<std::string>::iterator it_expected;
    std::set<std::string>::iterator it_res;

    expected.insert(".");
    expected.insert("..");
    expected.insert("Documents");
    expected.insert("Downloads");
    expected.insert("hello.txt");
    expected.insert("my_profile");

    
    scanner->nextNode();
    while(!scanner->isDone()){
        name = scanner->currentNodeName();
        // std::cout << name << std::endl;
        res.insert(name);
        scanner->nextNode();
    }
    
    for(it_expected=expected.begin(), it_res=res.begin(); it_expected!=expected.end(); it_expected++, it_res++){
        ASSERT_EQ(*it_res, *it_expected);
    }

    delete scanner;
}