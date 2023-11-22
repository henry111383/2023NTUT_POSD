#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include "../src/null_iterator.h"
#include <gtest/gtest.h>

class OrderByNameIteratorTest : public ::testing::Test
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

// Normal
TEST_F(OrderByNameIteratorTest, OrderByNormalShouldbeCorrectlyBuilt)
{
    Iterator* it;
    ASSERT_NO_THROW(it = home->createIterator(OrderBy::Normal));
    delete it;
}

// OrderByName
TEST_F(OrderByNameIteratorTest, OrderByNameShouldbeCorrectlyBuilt)
{
    Iterator* it;
    ASSERT_NO_THROW(it = home->createIterator(OrderBy::Name));
    delete it;
}

TEST_F(OrderByNameIteratorTest, OrderByNameFirstShouldNotThrowException)
{
    Iterator* it = home->createIterator(OrderBy::Name);
    ASSERT_NO_THROW(it->first());
    delete it;
}

TEST_F(OrderByNameIteratorTest, OrderByNameCurrentItemShouldbeCorrect)
{
    Iterator* it = home->createIterator(OrderBy::Name);
    ASSERT_NO_THROW(it->first());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/Documents");
    delete it;
}

TEST_F(OrderByNameIteratorTest, OrderByNameNextShouldbeCorrect)
{
    Iterator* it = home->createIterator(OrderBy::Name);
    ASSERT_NO_THROW(it->first());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/Documents");
    ASSERT_NO_THROW(it->next());
    delete it;
}

TEST_F(OrderByNameIteratorTest, OrderByNameisDoneShouldbeCorrect)
{
    Iterator* it = home->createIterator(OrderBy::Name);
    ASSERT_NO_THROW(it->first());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/Documents");
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    delete it;
}

TEST_F(OrderByNameIteratorTest, OrderByNameAllShouldbeCorrect)
{
    Iterator* it = home->createIterator(OrderBy::Name);
    ASSERT_NO_THROW(it->first());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/Documents");
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/Downloads");
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/hello.txt");
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/my_profile");
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());
    delete it;
}
// OrderByNameWithFolderFirst
TEST_F(OrderByNameIteratorTest, OrderByNameWithFolderFirstShouldbeCorrectlyBuilt)
{
    Iterator* it;
    ASSERT_NO_THROW(it = home->createIterator(OrderBy::NameWithFolderFirst));
    delete it;
}

TEST_F(OrderByNameIteratorTest, OrderByNameWithFolderFirstFirstShouldNotThrowException)
{
    Iterator* it = home->createIterator(OrderBy::NameWithFolderFirst);
    ASSERT_NO_THROW(it->first());
    delete it;
}

TEST_F(OrderByNameIteratorTest, OrderByNameWithFolderFirstCurrentItemShouldbeCorrect)
{
    Iterator* it = home->createIterator(OrderBy::NameWithFolderFirst);
    ASSERT_NO_THROW(it->first());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/Documents");
    delete it;
}

TEST_F(OrderByNameIteratorTest, OrderByNameWithFolderFirstNextShouldbeCorrect)
{
    Iterator* it = home->createIterator(OrderBy::NameWithFolderFirst);
    ASSERT_NO_THROW(it->first());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/Documents");
    ASSERT_NO_THROW(it->next());
    delete it;
}

TEST_F(OrderByNameIteratorTest, OrderByNameWithFolderFirstisDoneShouldbeCorrect)
{
    Iterator* it = home->createIterator(OrderBy::NameWithFolderFirst);
    ASSERT_NO_THROW(it->first());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/Documents");
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    delete it;
}

TEST_F(OrderByNameIteratorTest, OrderByNameWithFolderFirstAllShouldbeCorrect)
{
    Iterator* it = home->createIterator(OrderBy::NameWithFolderFirst);
    ASSERT_NO_THROW(it->first());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/Documents");
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/Downloads");
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/hello.txt");
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/my_profile");
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());
    delete it;
}
// OrderByKind
TEST_F(OrderByNameIteratorTest, OrderByKindShouldbeCorrectlyBuilt)
{
    Iterator* it;
    ASSERT_NO_THROW(it = home->createIterator(OrderBy::Kind));
    delete it;
}

TEST_F(OrderByNameIteratorTest, OrderByKindFirstShouldNotThrowException)
{
    Iterator* it = home->createIterator(OrderBy::Kind);
    ASSERT_NO_THROW(it->first());
    delete it;
}

TEST_F(OrderByNameIteratorTest, OrderByKindCurrentItemShouldbeCorrect)
{
    Iterator* it = home->createIterator(OrderBy::Kind);
    ASSERT_NO_THROW(it->first());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/my_profile");
    delete it;
}

TEST_F(OrderByNameIteratorTest, OrderByKindNextShouldbeCorrect)
{
    Iterator* it = home->createIterator(OrderBy::Kind);
    ASSERT_NO_THROW(it->first());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/my_profile");
    ASSERT_NO_THROW(it->next());
    delete it;
}

TEST_F(OrderByNameIteratorTest, OrderByKindisDoneShouldbeCorrect)
{
    Iterator* it = home->createIterator(OrderBy::Kind);
    ASSERT_NO_THROW(it->first());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/my_profile");
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    delete it;
}

TEST_F(OrderByNameIteratorTest, OrderByKindAllShouldbeCorrect)
{
    Iterator* it = home->createIterator(OrderBy::Kind);
    ASSERT_NO_THROW(it->first());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/my_profile");
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/Documents");
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/Downloads");
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(it->currentItem()->path(), "structure/home/hello.txt");
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());
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