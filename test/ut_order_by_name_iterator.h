#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include "../src/null_iterator.h"
#include <gtest/gtest.h>

class OrderByNameIteratorTest : public ::testing::Test
{
protected:
    Folder *home, *Documents, *Downloads, *favorites;
    File *hello, *my_profile, *hello2, *note, *clean, *cqrs, *domain, *funny;

    void SetUp() override
    {
        home = new Folder("structure/home");
        Documents = new Folder("structure/home/Documents");
        Downloads = new Folder("structure/home/Downloads");
        favorites = new Folder("structure/home/Documents/favorites");
        hello = new File("structure/home/hello.txt");
        my_profile = new File("structure/home/my_profile");
        hello2 = new File("structure/home/Documents/hello.txt");
        note = new File("structure/home/Documents/note.txt");
        clean = new File("structure/home/Documents/favorites/clean-architecture.pdf");
        cqrs = new File("structure/home/Documents/favorites/cqrs.pdf");
        domain = new File("structure/home/Documents/favorites/domain-driven-design.pdf");
        funny = new File("structure/home/Downloads/funny.png");

        home->add(Documents);
        home->add(Downloads);
        home->add(hello);
        home->add(my_profile);
        Documents->add(favorites);
        Documents->add(hello2);
        Documents->add(note);
        Downloads->add(funny);
        favorites->add(clean);
        favorites->add(cqrs);
        favorites->add(domain);
    }
    void TearDown() override {
        delete home;
        delete Documents;
        delete Downloads;
        delete favorites;
        delete hello;
        delete my_profile;
        delete hello2;
        delete note;
        delete clean;
        delete cqrs;
        delete domain;
        delete funny;
    }
};

TEST_F(OrderByNameIteratorTest, OrderByNameTest)
{
    Iterator* it = home->createIterator(OrderBy::Name);
    delete it;
}

TEST_F(OrderByNameIteratorTest, OrderByNameWithFolderFirstTest)
{
    Iterator* it = home->createIterator(OrderBy::NameWithFolderFirst);
    delete it;
}

TEST_F(OrderByNameIteratorTest, OrderByKindIteratorTest)
{
    Iterator* it = home->createIterator(OrderBy::Kind);
    delete it;
}