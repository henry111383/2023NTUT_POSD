#include "../src/folder.h"
#include "../src/file.h"
#include <string>
#include <gtest/gtest.h>
#include <list>
// typeid 
class FolderTest : public ::testing::Test
{
protected:
    std::string path = "/home/2023POSD/Documents";
    std::string name = "Documents"; 
    Folder *folder;
	File *file1, *file2;
	Folder *D1, *D2, *D3;
	File *f1, *f2, *f3, *f4;

    void SetUp() override
    {
		folder = new Folder(path);
		file1  = new File("/home/2023POSD/Documents/test1.txt");
		file2  = new File("/home/2023POSD/test2");
		D1 = new Folder("/D1");
		f1 = new File("/D1/f1");
		D2 = new Folder("/D1/D2");
		f2 = new File("/D1/f2");
		D1 -> add(f1);
		D1 -> add(D2);
		D1 -> add(f2);
		f3 = new File("/D1/D2/f3");
		D3 = new Folder("/D1/D2/D3");
		f4 = new File("/D1/D2/f4");
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
		delete folder;
		delete file1;
		delete file2;
		delete D1;
		delete D2;
		delete D3;
		delete f1;
		delete f2;
		delete f3;
		delete f4;
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
	std::list <Node *> MyChild;
	MyChild = folder -> child;
	ASSERT_TRUE(MyChild.empty());
}

TEST_F(FolderTest, AddShouldbeCorrect)
{
	ASSERT_NO_THROW(folder -> add(file1));
}

TEST_F(FolderTest, RemoveFileShouldbeCorrect)
{
	ASSERT_EQ(D1->find(f2->path()), f2);
	ASSERT_NO_THROW(D1 -> remove("/D1/f2"));
	ASSERT_EQ(D1->find(f2->path()), nullptr);
	ASSERT_ANY_THROW(D1 -> remove("/D2/f2"));
	
}

TEST_F(FolderTest, RemoveFolderShouldbeCorrect)
{
	ASSERT_EQ(D1->find(D2->path()), D2);
	ASSERT_NO_THROW(D1 -> remove("/D1/D2"));
	ASSERT_EQ(D1->find(D2->path()), nullptr);
	ASSERT_ANY_THROW(D1 -> remove("/D1/D2"));
	ASSERT_EQ(D1->find(f3->path()), nullptr);
	ASSERT_EQ(D1->find(D3->path()), nullptr);
	ASSERT_EQ(D1->find(f4->path()), nullptr);
}

TEST_F(FolderTest, GetChildByNameShouldbeCorrectIfExisting)
{
	folder -> add(file1);
	const char *file1_name = (file1 -> name()).c_str(); 
	Node *temp = folder->getChildByName(file1_name);
	ASSERT_EQ(file1, temp);
}

TEST_F(FolderTest, GetChildByNameShouldbeCorrectIfNotExisting)
{
	folder -> add(file1);
	const char *file2_name = (file2 -> name()).c_str(); 
	Node *temp = folder->getChildByName(file2_name);
	ASSERT_EQ(nullptr, temp);
}

TEST_F(FolderTest, FindShouldbeCorrectIfExisting)
{
	ASSERT_EQ(D1->find(f1->path()), f1);
	ASSERT_EQ(D1->find(D2->path()), D2);
	ASSERT_EQ(D1->find(f2->path()), f2);
	ASSERT_EQ(D1->find(f3->path()), f3);
	ASSERT_EQ(D1->find(D3->path()), D3);
	ASSERT_EQ(D1->find(f4->path()), f4);
}

TEST_F(FolderTest, FinditselfShouldbeCorrect)
{
	ASSERT_EQ(D1->find(D1->path()), nullptr);
}

TEST_F(FolderTest, NumberOfFilesShouldbeCorrect)
{
	ASSERT_EQ(D1->numberOfFiles(), 4);
	ASSERT_EQ(D2->numberOfFiles(), 2);
	ASSERT_EQ(D3->numberOfFiles(), 0);
}


