#include "../src/file.h"

TEST(File, normal) {
    File hello("structure/file.txt");
    ASSERT_EQ("file.txt", hello.name());
    ASSERT_EQ("structure/file.txt", hello.path());
}


TEST(File, invalid_file) {
    ASSERT_ANY_THROW(File("/NOT/EXIST/PATH"));
}

TEST(File, invalid_file_2) {
    ASSERT_ANY_THROW(File("structure/home"));
}

TEST(File, RenameWithEmptyShouldThrow){
    File hello("structure/file.txt");
    ASSERT_EQ("file.txt", hello.name());
    ASSERT_EQ("structure/file.txt", hello.path());
    ASSERT_ANY_THROW(hello.rename(""));
}

TEST(File, RenameShouldbeCorrect){
    File hello("structure/file.txt");
    ASSERT_EQ("file.txt", hello.name());
    ASSERT_EQ("structure/file.txt", hello.path());
    ASSERT_NO_THROW(hello.rename("HELLO.pdf"));
    ASSERT_EQ("HELLO.pdf", hello.name());
    ASSERT_EQ("structure/HELLO.pdf", hello.path());
}