#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include "../src/null_iterator.h"
#include <gtest/gtest.h>

class IteratorTest : public ::testing::Test
{
protected:
    Folder *D1, *D2, *D3;
    File *f1, *f2, *f3, *f4;

    void SetUp() override
    {
        char *tmp = get_current_dir_name();
        std::string cwd(tmp);
        free(tmp);

        D1 = new Folder(cwd + "/test/D1");
        f1 = new File(cwd + "/test/D1/f1");
        D2 = new Folder(cwd + "/test/D1/D2");
        f2 = new File(cwd + "/test/D1/f2");
        D1 -> add(f1);
        D1 -> add(D2);
        D1 -> add(f2);
        f3 = new File(cwd + "/test/D1/D2/f3");
        D3 = new Folder(cwd + "/test/D1/D2/D3");
        f4 = new File(cwd + "/test/D1/D2/f4");
        D2 -> add(f3);
        D2 -> add(D3);
        D2 -> add(f4);
        /*
                D1
            /   |   \
            f1   D2   f2
                / | \
            f3  D3 f4
        */
    }
    void TearDown() override {
        delete D1;
        delete D2;
        delete D3;
        delete f1;
        delete f2;
        delete f3;
        delete f4;
    }
};

TEST_F(IteratorTest, FolderIteratorShouldbeCorrectlyBuilded)
{
    ASSERT_NO_THROW(FolderIterator tmp(D1));
}

TEST_F(IteratorTest, FolderIteratorFirstShouldNotThrowException)
{   
    Iterator *it = new FolderIterator(D1);
    ASSERT_NO_THROW(it -> first());
    delete it;
}

TEST_F(IteratorTest, FolderIteratorIsDoneShouldbeCorrect)
{   
    Iterator *it = new FolderIterator(D1);
    ASSERT_NO_THROW(it -> first());
    ASSERT_FALSE(it -> isDone());
    delete it;
}

TEST_F(IteratorTest, FolderIteratorCurrentItemShouldbeCorrect)
{   
    Iterator *it = new FolderIterator(D1);
    ASSERT_NO_THROW(it -> first());
    ASSERT_FALSE(it -> isDone());
    ASSERT_EQ(it -> currentItem(), f1);
    delete it;
}


TEST_F(IteratorTest, FolderIteratorNextShouldbeCorrect)
{   
    Iterator *it = new FolderIterator(D1);
    ASSERT_NO_THROW(it -> first());
    ASSERT_FALSE(it -> isDone());
    ASSERT_EQ(it -> currentItem(), f1);
    ASSERT_NO_THROW(it -> next());
    ASSERT_EQ(it -> currentItem(), D2);
    delete it;
}

TEST_F(IteratorTest, FolderIteratorAllShouldbeCorrect)
{   
    Iterator *it = new FolderIterator(D1);
    ASSERT_NO_THROW(it -> first());
    ASSERT_FALSE(it -> isDone());
    ASSERT_EQ(it -> currentItem(), f1);
    ASSERT_NO_THROW(it -> next());
    ASSERT_EQ(it -> currentItem(), D2);
    ASSERT_NO_THROW(it -> next());
    ASSERT_EQ(it -> currentItem(), f2);
    ASSERT_NO_THROW(it -> next());
    ASSERT_TRUE(it -> isDone());
    delete it;
}

TEST_F(IteratorTest, EmptyFolderIteratorFirstShouldbeCorrect)
{   
    Iterator *it = D3 -> createIterator();
    ASSERT_NO_THROW(it -> first());
    delete it;
}

TEST_F(IteratorTest, EmptyFolderIteratorIsDoneShouldbeCorrect)
{   
    Iterator *it = D3 -> createIterator();
    ASSERT_NO_THROW(it -> first());
    ASSERT_TRUE(it -> isDone());
    delete it;
}

TEST_F(IteratorTest, EmptyFolderIteratorAllShouldbeCorrect)
{   
    Iterator *it = D3 -> createIterator();
    for(it->first(); !it->isDone(); it->next()){
        ASSERT_TRUE(0);
    }
    delete it;
}

