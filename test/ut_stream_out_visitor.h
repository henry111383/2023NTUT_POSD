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
    Node *folder, *folder1, *folder2, *file1, *file2, *tmp;

    void SetUp() override
    {
        folder  = new Folder("./documents");
        folder1 = new Folder("./documents/folder1");
        folder -> add(folder1);
        folder2 = new Folder("./documents/folder2");
        folder -> add(folder2);
        file1   = new File("./documents/folder1/file.txt");
        folder1 -> add(file1);
        file2   = new File("./documents/folder2/file.txt");
        folder2 -> add(file2);
        tmp = new Folder("./documents/folder1/folder1");
        folder1 -> add(tmp);
    }
    void TearDown() override {
        delete folder;
        delete folder1;
        delete folder2;
        delete file1;
        delete file2;
        delete tmp;
    }
};

TEST_F(StreamOutVisitorTest, VisitorShouldbeCorrectlyBuilt){
    ASSERT_NO_THROW(StreamOutVisitor visitor);
}

TEST_F(StreamOutVisitorTest, XX){
    StreamOutVisitor *visitor = new StreamOutVisitor;
    folder->accept(visitor);

    // std::string ans("This is file 2\nThis is second line\nthis is end of file\n");
    std::string res;
    res = visitor->getResult();
    std::cout << res << std::endl;
    // ASSERT_EQ(ans, res);
    delete visitor;
}