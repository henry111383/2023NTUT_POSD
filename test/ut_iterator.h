#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include "../src/null_iterator.h"
#include <gtest/gtest.h>

class IteratorTest : public ::testing::Test
{
protected:
    File *afile1, *afile2, *afile3;
    Folder *afolder, *achildfolder, *aemptyfolder;

    Iterator *anullIterator, *afolderIterator;

    void SetUp() override
    {
        afolder = new Folder("/home/A");
        afile1 = new File("/home/A/1");
        achildfolder = new Folder("/home/A/B");
        afile2 = new File("/home/A/B/2");
        afile3 = new File("/home/A/B/3");
        aemptyfolder = new Folder("/home/C");

        afolder -> add(afile1);
        afolder -> add(achildfolder);
        achildfolder -> add(afile2);
        achildfolder -> add(afile3);

        anullIterator = new NullIterator();
        afolderIterator = new FolderIterator(afolder);
    }

    void TearDown() override
    {
        delete afolder;
        delete afile1;
        delete achildfolder;
        delete afile2;
        delete afile3;
        delete aemptyfolder;
        delete anullIterator;
        delete afolderIterator;
    }
};

TEST_F(IteratorTest, FolderIteratorShouldbeCorrectlyBuilded)
{
    ASSERT_NO_THROW(FolderIterator tmp(afolder));
}

TEST_F(IteratorTest, FolderIteratorFirstShouldNotThrowException)
{   
    ASSERT_NO_THROW(afolderIterator -> first());
}

TEST_F(IteratorTest, FolderIteratorCurrentItemShouldbeCorrect)
{   
    ASSERT_EQ(afolderIterator -> currentItem(), afile1);
}

TEST_F(IteratorTest, FolderIteratorNextShouldbeCorrect)
{   
    ASSERT_EQ(afolderIterator -> currentItem(), afile1);
    ASSERT_NO_THROW(afolderIterator -> next());
    ASSERT_EQ(afolderIterator -> currentItem(), achildfolder);
}

TEST_F(IteratorTest, FolderIteratorIsDoneShouldbeCorrect)
{   
    ASSERT_NO_THROW(afolderIterator -> next());
    ASSERT_NO_THROW(afolderIterator -> next());
    ASSERT_TRUE(afolderIterator -> isDone());
}

TEST_F(IteratorTest, EmptyFolderIteratorFirstShouldbeCorrect)
{   
    Iterator *it = aemptyfolder -> createIterator();
    ASSERT_NO_THROW(it -> first());
    delete it;
}

TEST_F(IteratorTest, EmptyFolderIteratorFirstShouldNotThrowException)
{   
    Iterator *it = aemptyfolder -> createIterator();
    ASSERT_NO_THROW(it -> first());
    delete it;
}

TEST_F(IteratorTest, EmptyFolderIteratorCurrentItemShouldThrowException)
{   
    Iterator *it = aemptyfolder -> createIterator();
    ASSERT_ANY_THROW(it -> currentItem());
    delete it;
}

TEST_F(IteratorTest, EmptyFolderIteratorNextShouldThrowException)
{   
    Iterator *it = aemptyfolder -> createIterator();
    ASSERT_ANY_THROW(it -> next());
    delete it;
}

TEST_F(IteratorTest, EmptyFolderIteratorIsDoneShouldbeCorrect)
{   
    Iterator *it = aemptyfolder -> createIterator();
    ASSERT_TRUE(it -> isDone());
    delete it;
}