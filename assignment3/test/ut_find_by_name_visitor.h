#include "../src/find_by_name_visitor.h"
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include <string>
#include <gtest/gtest.h>

class FindbyNameVisitorTest : public ::testing::Test
{
protected:
    Node *folder, *folder1, *folder2, *file1, *file2, *emptyfolder;
    std::string cwd;
    void SetUp() override
    {

        folder  = new Folder("test/documents");
        folder1 = new Folder("test/documents/folder1");
        folder -> add(folder1);
        folder2 = new Folder("test/documents/folder2");
        folder -> add(folder2);
        file1   = new File("test/documents/folder1/file.txt");
        folder1 -> add(file1);
        file2   = new File("test/documents/folder2/file.txt");
        folder2 -> add(file2);
        emptyfolder = new Folder("test/documents/folder1/folder1");
        folder1 -> add(emptyfolder);
    }
    void TearDown() override {
        delete folder;
        delete folder1;
        delete folder2;
        delete file1;
        delete file2;
        delete emptyfolder;
    }
};

TEST_F(FindbyNameVisitorTest, VisitorShouldbeCorrectlyBuilt){
    ASSERT_NO_THROW(FindByNameVisitor visitor("test"));
}

TEST_F(FindbyNameVisitorTest, VisitorFileWithNotExistingFileNameShouldbeCorrect){
    FindByNameVisitor *visitor = new FindByNameVisitor("test");

    file2->accept(visitor);

    ASSERT_TRUE(visitor->getPaths().empty());
    delete visitor;
}

TEST_F(FindbyNameVisitorTest, VisitorFileWithExistingFileNameShouldbeCorrect){
    FindByNameVisitor *visitor = new FindByNameVisitor("file.txt");

    file2->accept(visitor);

    ASSERT_EQ("test/documents/folder2/file.txt", visitor->getPaths().front());
    delete visitor;
}


TEST_F(FindbyNameVisitorTest, VisitorFolderWithNotExistingNameShouldbeCorrect){
    FindByNameVisitor *visitor = new FindByNameVisitor("Hellp");

    folder->accept(visitor);

    ASSERT_TRUE(visitor->getPaths().empty());
    delete visitor;
}

TEST_F(FindbyNameVisitorTest, VisitorFolderWithItselfNameShouldbeCorrect){
    FindByNameVisitor *visitor = new FindByNameVisitor("documents");

    folder->accept(visitor);

    ASSERT_EQ("test/documents", visitor->getPaths().front());
    delete visitor;
}

TEST_F(FindbyNameVisitorTest, VisitorFolderWithExistingFolderNameShouldbeCorrect){
    FindByNameVisitor *visitor = new FindByNameVisitor("folder1");

    folder->accept(visitor);

    ASSERT_EQ(2, visitor->getPaths().size());
    ASSERT_EQ("test/documents/folder1", visitor->getPaths().front());
    ASSERT_EQ("test/documents/folder1/folder1", visitor->getPaths().back());
    delete visitor;
}

TEST_F(FindbyNameVisitorTest, VisitorFolderWithExistingFileNameShouldbeCorrect){
    FindByNameVisitor *visitor = new FindByNameVisitor("file.txt");

    folder->accept(visitor);

    ASSERT_EQ(2, visitor->getPaths().size());
    ASSERT_EQ("test/documents/folder1/file.txt", visitor->getPaths().front());
    ASSERT_EQ("test/documents/folder2/file.txt", visitor->getPaths().back());
    delete visitor;
}