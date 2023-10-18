#include "../src/file.h"
#include <string>
#include <gtest/gtest.h>

class FileTest : public ::testing::Test
{
protected:
    std::string path ="/home/2023POSD/text.txt";
    std::string name = "text.txt"; 
    File * file;

    void SetUp() override
    {
		file = new File(path);
    }

    void TearDown() override {
		delete file;
    }
};

TEST_F(FileTest, FileShouldbeCorrectlyBuilded) 
{
    ASSERT_NO_THROW(File f(path));
}

TEST_F(FileTest, PathShouldbeCorrect)
{
	ASSERT_EQ(file->path(), path);
}

TEST_F(FileTest, NameShouldbeCorrect)
{
	ASSERT_EQ(file->name(), name);
}

TEST_F(FileTest, AddShouldThrowException)
{
	ASSERT_ANY_THROW(file->add(nullptr));
}

TEST_F(FileTest, RemoveShouldThrowException)
{
	ASSERT_ANY_THROW(file->remove(""));
}

TEST_F(FileTest, getChildByNameShouldbeNullptr)
{
	ASSERT_EQ(nullptr, file->getChildByName(""));
}

TEST_F(FileTest, FindShouldbeNull)
{
	ASSERT_EQ(file->find(""), nullptr);
}

TEST_F(FileTest, numberOfFilesShouldbeOne)
{
	ASSERT_EQ(1, file->numberOfFiles());
}

TEST_F(FileTest, createIteratorShouldbeNullIterator)
{
	Iterator * tmpIterator;
	ASSERT_NO_THROW(tmpIterator = file->createIterator());
	delete tmpIterator;
}

