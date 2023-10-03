#include "../src/dfs_iterator.h"
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include <gtest/gtest.h>

class DfsIteratorTest : public ::testing::Test
{
protected:
    Node *D1, *D2, *D3, *f1, *f2, *f3, *f4;

    void SetUp() override
    {
        D1 = new Folder("/D1");
        f1 = new File("/D1/f1");
        D2 = new Folder("/D1/D2");
        f2 = new File("D1/f2");
        D1 -> add(f1);
        D1 -> add(D2);
        D1 -> add(f2);
        f3 = new File("D1/D2/f3");
        D3 = new Folder("D1/D2/D3");
        f4 = new File("D1/D2/f4");
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

TEST_F(DfsIteratorTest, test1)
{
    Iterator *dfs_it =  new DfsIterator(D1);
    // ASSERT_NO_THROW(dfs_it -> first());
    // ASSERT_EQ(f1, dfs_it -> currentItem());
    // ASSERT_NO_THROW(dfs_it -> next());
    // ASSERT_EQ(f3, dfs_it -> currentItem());
    // ASSERT_NO_THROW(dfs_it -> next());
    // ASSERT_EQ(D3, dfs_it -> currentItem());
    // ASSERT_NO_THROW(dfs_it -> next());
    // ASSERT_EQ(f4, dfs_it -> currentItem());
    // ASSERT_NO_THROW(dfs_it -> next());
    // ASSERT_EQ(D2, dfs_it -> currentItem());
    // ASSERT_NO_THROW(dfs_it -> next());
    // ASSERT_EQ(f2, dfs_it -> currentItem());
    // ASSERT_NO_THROW(dfs_it -> next());
    // ASSERT_TRUE(dfs_it -> isDone());
    delete dfs_it;
}