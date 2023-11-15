#include "../src/file_system_builder.h"
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include <gtest/gtest.h>


class BuilderTest : public ::testing::Test
{
protected:
    Folder *home, *Documents, *Downloads, *programming;
    File *clean, *domain, *hello, *note, *object, *cpp, *oop, *python, *funny, *hello2, *my_profile;

    void SetUp() override
    {
    home = new Folder("structure/home");
    Documents = new Folder("structure/home/Documents");
    Downloads = new Folder("structure/home/Downloads");
    programming = new Folder("structure/home/Documents/programming");
    clean = new File("structure/home/Documents/clean-architecture.pdf");
    domain = new File("structure/home/Documents/domain-driven-design.pub");
    hello = new File("structure/home/Documents/hello.txt");
    note = new File("structure/home/Documents/note.txt");
    object = new File("structure/home/Documents/object-oriented-analysis-and-design.pdf");
    cpp = new File("structure/home/Documents/programming/cpp.pub");
    oop = new File("structure/home/Documents/programming/oop.pdf");
    python = new File("structure/home/Documents/programming/python.pub");
    funny = new File("structure/home/Downloads/funny.png");
    hello2 = new File("structure/home/hello.txt");
    my_profile = new File("structure/home/my_profile");

    home->add(Documents);
    home->add(Downloads);
    home->add(hello2);
    home->add(my_profile);
    Documents->add(clean);
    Documents->add(domain);
    Documents->add(hello);
    Documents->add(note);
    Documents->add(object);
    Documents->add(programming);
    programming->add(cpp);
    programming->add(oop);
    programming->add(python);
    Downloads->add(funny);

    }
    
    void TearDown() override {
    delete home;
    delete Documents;
    delete Downloads;
    delete programming;
    delete clean;
    delete domain;
    delete hello;
    delete note;
    delete object;
    delete cpp;
    delete oop;
    delete python;
    delete funny;
    delete hello2;
    delete my_profile;
        
    }
};

TEST(BuilderTest, BuilderShouldbeCorrectlyBuilt){
    FileSystemBuilder *builder = new FileSystemBuilder();

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