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

TEST_F(NullIteratorTest, firstShouldNotThrowException)
{
    ASSERT_NO_THROW(aIterator -> first());
}

TEST_F(NullIteratorTest, currentItemShouldThrowNullptr)
{
    ASSERT_EQ(nullptr, aIterator -> currentItem());
}

TEST_F(NullIteratorTest, isDoneShouldbeTrue)
{
    ASSERT_TRUE(aIterator -> isDone());
}

TEST_F(NullIteratorTest, AllshouldbeCorrect)
{
    for(aIterator->first(); !aIterator->isDone(); aIterator->next()){
        ASSERT_TRUE(0);
    }
}
