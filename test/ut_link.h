#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/iterator.h"
#include "../src/dfs_iterator.h"
#include "../src/iterator_factories.h"
#include "../src/link.h"
#include <gtest/gtest.h>

TEST(LinkTEST, LinkShouldbeCorrectlyBuilt){
    Node *folder = new Folder("structure2/home/Documents/programming");
    Node *lnk;
    ASSERT_NO_THROW(lnk = new Link("structure2/home/link_to_programming", folder));
    delete lnk;
    delete folder;
}

TEST(LinkTEST, numberOfFilesShouldbeCorrect){
    Node *folder = new Folder("structure2/home/Documents/programming");
    Node *lnk;
    ASSERT_NO_THROW(lnk = new Link("structure2/home/link_to_programming", folder));
    ASSERT_EQ(folder->numberOfFiles(), lnk->numberOfFiles());
    delete lnk;
    delete folder;
}

TEST(LinkTEST, findShouldbeCorrect){
    Node *folder = new Folder("structure2/home/Documents/programming");
    Node *cpp = new File("structure2/home/Documents/programming/cpp.pub");
    folder->add(cpp);
    Node *lnk;
    ASSERT_NO_THROW(lnk = new Link("structure2/home/link_to_programming", folder));
    ASSERT_EQ("cpp.pub", folder->find("structure2/home/Documents/programming/cpp.pub")->name());
    ASSERT_EQ(folder->find("structure2/home/Documents/programming/cpp.pub"), lnk->find("structure2/home/Documents/programming/cpp.pub"));
    delete lnk;
    delete folder;
}

TEST(LinkTEST, findByNameShouldbeCorrect){
    Node *folder = new Folder("structure2/home/Documents/programming");
    Node *cpp = new File("structure2/home/Documents/programming/cpp.pub");
    folder->add(cpp);
    Node *lnk;
    ASSERT_NO_THROW(lnk = new Link("structure2/home/link_to_programming", folder));
    ASSERT_EQ("structure2/home/Documents/programming/cpp.pub", folder->findByName("cpp.pub").front());
    ASSERT_EQ(folder->findByName("cpp.pub").front(), lnk->findByName("cpp.pub").front());
    delete lnk;
    delete folder;
}

TEST(LinkTEST, LinkToFile){
    Node *folder = new Folder("structure/home");
    Node *lnk = new Link("structure/link_to_home", folder);
    Node *cpp = new File("structure/home/hello.txt");
    lnk->add(cpp);
    delete lnk;
    delete folder;
}