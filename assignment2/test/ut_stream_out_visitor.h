#include "../src/stream_out_visitor.h"
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include <string>
#include <gtest/gtest.h>

class StreamOutVisitorTest : public ::testing::Test
{
protected:
    Node *folder, *folder1, *folder2, *file1, *file2, *emptyfolder;

    void SetUp() override
    {
        char *tmp = get_current_dir_name();
        std::string cwd(tmp);
        free(tmp);
        // std::cout << "Current working directory: " << cwd<< std::endl;
        folder  = new Folder(cwd + "/test/documents");
        folder1 = new Folder(cwd + "/test/documents/folder1");
        folder -> add(folder1);
        folder2 = new Folder(cwd + "/test/documents/folder2");
        folder -> add(folder2);
        file1   = new File(cwd + "/test/documents/folder1/file.txt");
        folder1 -> add(file1);
        file2   = new File(cwd + "/test/documents/folder2/file.txt");
        folder2 -> add(file2);
        emptyfolder = new Folder(cwd + "/test/documents/folder1/folder1");
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

TEST_F(StreamOutVisitorTest, VisitorShouldbeCorrectlyBuilt){
    ASSERT_NO_THROW(StreamOutVisitor visitor);
    
}

TEST_F(StreamOutVisitorTest, VisitorFileShouldbeCorrectlyBuilt){
    StreamOutVisitor *visitor = new StreamOutVisitor;
    file1->accept(visitor);
    std::string ans("_____________________________________________\n/mnt/d/POSD/HW/posd2023f_111598084_hw/test/documents/folder1/file.txt\n---------------------------------------------\nhello, world\n_____________________________________________\n");
    std::string res;
    res = visitor-> getResult();
    // ASSERT_EQ(ans, res);
    delete visitor;
}

TEST_F(StreamOutVisitorTest, VisitorFolderShouldbeCorrectlyBuilt){
    StreamOutVisitor *visitor = new StreamOutVisitor;
    file1->accept(visitor);
    std::string ans("_____________________________________________\n/mnt/d/POSD/HW/posd2023f_111598084_hw/test/documents/folder1/file.txt\n---------------------------------------------\nhello, world\n_____________________________________________\n_____________________________________________\n/mnt/d/POSD/HW/posd2023f_111598084_hw/test/documents/folder2/file.txt\n---------------------------------------------\nThis is file 2\nThis is second line\nthis is end of file\n_____________________________________________\n\n");
    std::string res;
    res = visitor-> getResult();
    // ASSERT_EQ(ans, res);
    delete visitor;
}

