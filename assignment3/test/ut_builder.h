#include "../src/file_system_builder.h"
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include "../src/tree_visitor.h"
#include <gtest/gtest.h>

TEST(BuilderTest, BuilderShouldbeCorrectlyBuilt){
    FileSystemBuilder *builder;
    ASSERT_NO_THROW(builder = new FileSystemBuilder());
    delete builder;
}

TEST(BuilderTest, BuilderbuilderFileShouldbeCorrect){
    FileSystemBuilder *builder;
    ASSERT_NO_THROW(builder = new FileSystemBuilder());
    ASSERT_NO_THROW(builder->buildFile("structure/home/Documents/programming/cpp.pub"));
    delete builder;
}

TEST(BuilderTest, BuilderbuilderFolderShouldbeCorrect){
    FileSystemBuilder *builder;
    ASSERT_NO_THROW(builder = new FileSystemBuilder());
    ASSERT_NO_THROW(builder->buildFolder("structure/home"));
    delete builder;
}

TEST(BuilderTest, BuilderendFolderShouldbeCorrect){
    FileSystemBuilder *builder;
    ASSERT_NO_THROW(builder = new FileSystemBuilder());
    ASSERT_NO_THROW(builder->buildFolder("structure/home"));
    ASSERT_NO_THROW(builder->endFolder());
    delete builder;
}

TEST(BuilderTest, BuilderGetRootShouldbeCorrect){
    FileSystemBuilder *builder;
    ASSERT_NO_THROW(builder = new FileSystemBuilder());
    ASSERT_NO_THROW(builder->buildFolder("structure/home"));
    ASSERT_NO_THROW(builder->buildFolder("structure/home/Documents"));
    ASSERT_NO_THROW(builder->buildFolder("structure/home/Documents/programming"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/Documents/programming/cpp.pub"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/Documents/programming/oop.pdf"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/Documents/programming/python.pub"));
    ASSERT_NO_THROW(builder->endFolder());
    ASSERT_NO_THROW(builder->buildFile("structure/home/Documents/clean-architecture.pdf"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/Documents/domain-driven-design.pub"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/Documents/hello.txt"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/Documents/note.txt"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/Documents/object-oriented-analysis-and-design.pdf"));
    ASSERT_NO_THROW(builder->endFolder());
    ASSERT_NO_THROW(builder->buildFolder("structure/home/Downloads"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/Downloads/funny.png"));
    ASSERT_NO_THROW(builder->endFolder());
    ASSERT_NO_THROW(builder->buildFile("structure/home/hello.txt"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/my_profile"));
    ASSERT_NO_THROW(builder->endFolder());
    ASSERT_EQ(builder->getRoot()->numberOfFiles(), 11);
    delete builder;
}

TEST(BuilderTest, BuilderAllShouldbeCorrect){
    FileSystemBuilder *builder;
    ASSERT_NO_THROW(builder = new FileSystemBuilder());
    ASSERT_NO_THROW(builder->buildFolder("structure/home"));
    ASSERT_NO_THROW(builder->buildFolder("structure/home/Documents"));
    ASSERT_NO_THROW(builder->buildFolder("structure/home/Documents/programming"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/Documents/programming/cpp.pub"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/Documents/programming/oop.pdf"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/Documents/programming/python.pub"));
    ASSERT_NO_THROW(builder->endFolder());
    ASSERT_NO_THROW(builder->buildFile("structure/home/Documents/clean-architecture.pdf"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/Documents/domain-driven-design.pub"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/Documents/hello.txt"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/Documents/note.txt"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/Documents/object-oriented-analysis-and-design.pdf"));
    ASSERT_NO_THROW(builder->endFolder());
    ASSERT_NO_THROW(builder->buildFolder("structure/home/Downloads"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/Downloads/funny.png"));
    ASSERT_NO_THROW(builder->endFolder());
    ASSERT_NO_THROW(builder->buildFile("structure/home/hello.txt"));
    ASSERT_NO_THROW(builder->buildFile("structure/home/my_profile"));
    ASSERT_NO_THROW(builder->endFolder());
    ASSERT_EQ(builder->getRoot()->numberOfFiles(), 11);
    

    TreeVisitor *visitor = new TreeVisitor(OrderBy::Kind);
    visitor->visitFolder(builder->getRoot());
    std::string res = visitor->getTree();
    std::string expected;
    expected += ".\n";
    expected += "├── my_profile\n";
    expected += "├── Documents\n";
    expected += "│   ├── programming\n";
    expected += "│   │   ├── oop.pdf\n";
    expected += "│   │   ├── cpp.pub\n";
    expected += "│   │   └── python.pub\n";
    expected += "│   ├── clean-architecture.pdf\n";
    expected += "│   ├── object-oriented-analysis-and-design.pdf\n";
    expected += "│   ├── domain-driven-design.pub\n";
    expected += "│   ├── hello.txt\n";
    expected += "│   └── note.txt\n";
    expected += "├── Downloads\n";
    expected += "│   └── funny.png\n";
    expected += "└── hello.txt\n";
    // std::cout << res <<std::endl;
    ASSERT_EQ(res, expected);
    delete visitor;
    delete builder;
}