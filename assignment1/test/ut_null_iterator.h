#include "../src/null_iterator.h"
#include <gtest/gtest.h>

class NullIteratorTest : public ::testing::Test
{
protected:
    NullIterator * aIterator;

    void SetUp() override
    {
		aIterator = new NullIterator();
    }

    void TearDown() override 
    {
		delete aIterator;
    }
};

TEST_F(NullIteratorTest, NullIteratorShouldbeCorrectlyBuilded) 
{
    ASSERT_NO_THROW(NullIterator tmp);
}

TEST_F(NullIteratorTest, firstShouldThrowException)
{
    ASSERT_ANY_THROW(aIterator -> first());
}

TEST_F(NullIteratorTest, currentItemShouldThrowException)
{
    ASSERT_ANY_THROW(aIterator -> currentItem());
}

TEST_F(NullIteratorTest, nextShouldThrowException)
{
    ASSERT_ANY_THROW(aIterator -> next());
}

TEST_F(NullIteratorTest, isDoneShouldbeTrue)
{
    ASSERT_TRUE(aIterator -> isDone());
}