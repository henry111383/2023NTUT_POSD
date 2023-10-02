#include "../src/folder.h"
#include "../src/file.h"
#include <string>
#include <gtest/gtest.h>
#include <list>

class FolderTest : public ::testing::Test
{
protected:
    std::string path = "/home/2023POSD/Documents";
    std::string name = "Documents"; 
    Folder *folder;
	File *file1, *file2;

    void SetUp() override
    {
		folder = new Folder(path);
		file1  = new File("/home/2023POSD/Documents/test1.txt");
		file2  = new File("/home/2023POSD/test2");
    }

    void TearDown() override {
		delete folder;
		delete file1;
		delete file2;
    }
};


TEST_F(FolderTest, FolderShouldbeCorrectlyBuilded) 
{
    ASSERT_NO_THROW(Folder f(path));
}

TEST_F(FolderTest, PathShouldbeCorrect)
{
	ASSERT_EQ(folder->path(), path);
}

TEST_F(FolderTest, NameShouldbeCorrect)
{
	ASSERT_EQ(folder->name(), name);
}

TEST_F(FolderTest, EmptyFoldergetChildmapShouldbeEmpty)
{
	std::list <Node *> MyMap;
	MyMap = folder -> child;
	ASSERT_TRUE(MyMap.empty());
}

TEST_F(FolderTest, AddShouldbeCorrect)
{
	ASSERT_NO_THROW(folder -> add(file1));
}

TEST_F(FolderTest, getChildByNameShouldbeCorrectIfExisting)
{
	folder -> add(file1);
	const char *file1_name = (file1 -> name()).c_str(); 
	Node *temp = folder->getChildByName(file1_name);
	ASSERT_EQ(file1, temp);
}

TEST_F(FolderTest, getChildByNameShouldbeCorrectIfNotExisting)
{
	folder -> add(file1);
	const char *file2_name = (file2 -> name()).c_str(); 
	Node *temp = folder->getChildByName(file2_name);
	ASSERT_EQ(nullptr, temp);
}

TEST_F(FolderTest, FindShouldbeCorrectIfExisting)
{
	
}

// TEST_F(FolderTest, RemoveShouldThrowException){
// 	ASSERT_ANY_THROW(folder->remove(""));
// }

// TEST_F(FolderTest, getChildByNameShouldThrowException){
// 	ASSERT_ANY_THROW(folder->getChildByName(""));
// }

// TEST_F(FolderTest, FindShouldThrowException){
// 	ASSERT_ANY_THROW(folder->find(""));
// }

// TEST_F(FolderTest, numberOfFilesShouldThrowException){
// 	ASSERT_ANY_THROW(folder->numberOfFiles());
// }

// TEST_F(FolderTest, createIteratorShouldbeNullIterator){
// 	Iterator * tmpIterator;
// 	ASSERT_NO_THROW(tmpIterator = folder->createIterator());
// 	delete tmpIterator;
// }

