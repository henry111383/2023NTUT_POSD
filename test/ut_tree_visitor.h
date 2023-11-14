#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include "../src/null_iterator.h"
#include "../src/tree_visitor.h"
#include <gtest/gtest.h>

class TreeVisitorTest : public ::testing::Test
{
protected:
    Folder *home, *Documents, *Downloads, *programming;
    File *clean, *domain, *hello, *note, *object, *cpp, *oop, *python, *funny, *hello2, *my_profile;

    void SetUp() override
    {
    home = new Folder("structure/home");
    Documents = new Folder("structure/home/Documents");
    Downloads = new Folder("structure/home/Downloads");
    programming = new Folder("structure/home/Documents/programming");
    clean = new File("structure/home/Documents/clean-architecture.pdf");
    domain = new File("structure/home/Documents/domain-driven-design.pub");
    hello = new File("structure/home/Documents/hello.txt");
    note = new File("structure/home/Documents/note.txt");
    object = new File("structure/home/Documents/object-oriented-analysis-and-design.pdf");
    cpp = new File("structure/home/Documents/programming/cpp.pub");
    oop = new File("structure/home/Documents/programming/oop.pdf");
    python = new File("structure/home/Documents/programming/python.pub");
    funny = new File("structure/home/Downloads/funny.png");
    hello2 = new File("structure/home/hello.txt");
    my_profile = new File("structure/home/my_profile");

    home->add(Documents);
    home->add(Downloads);
    home->add(hello2);
    home->add(my_profile);
    Documents->add(clean);
    Documents->add(domain);
    Documents->add(hello);
    Documents->add(note);
    Documents->add(object);
    Documents->add(programming);
    programming->add(cpp);
    programming->add(oop);
    programming->add(python);
    Downloads->add(funny);

    }
    
    void TearDown() override {
    delete home;
    delete Documents;
    delete Downloads;
    delete programming;
    delete clean;
    delete domain;
    delete hello;
    delete note;
    delete object;
    delete cpp;
    delete oop;
    delete python;
    delete funny;
    delete hello2;
    delete my_profile;
        
    }
};

TEST_F(TreeVisitorTest, OrderByNormalTest)
{
    TreeVisitor *visitor = new TreeVisitor(OrderBy::Normal);
    visitor->visitFolder(home);
    std::string res = visitor->getTree();
    std::cout << res <<std::endl;
    delete visitor;
}

TEST_F(TreeVisitorTest, OrderByNameTest)
{
    TreeVisitor *visitor = new TreeVisitor(OrderBy::Name);
    visitor->visitFolder(home);
    std::string res = visitor->getTree();
    std::cout << res <<std::endl;
    delete visitor;
}

TEST_F(TreeVisitorTest, OrderByNameWithFolderFirstTest)
{
    TreeVisitor *visitor = new TreeVisitor(OrderBy::NameWithFolderFirst);
    visitor->visitFolder(home);
    std::string res = visitor->getTree();
    std::cout << res <<std::endl;
    delete visitor;
}

TEST_F(TreeVisitorTest, OrderByKindTest)
{
    TreeVisitor *visitor = new TreeVisitor(OrderBy::Kind);
    visitor->visitFolder(home);
    std::string res = visitor->getTree();
    std::cout << res <<std::endl;
    delete visitor;
}