#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/iterator.h"
#include "../src/dfs_iterator.h"
#include "../src/iterator_factories.h"
#include <gtest/gtest.h>

class AbstractFactoryTest: public ::testing::Test {
protected:
    virtual void SetUp() {
        home = new Folder("structure/home");

        profile = new File("structure/home/my_profile");
        home->add(profile);

        document = new Folder("structure/home/Documents");
        home->add(document);

        favorite = new Folder("structure/home/Documents/favorites");
        document->add(favorite);
        ddd = new File("structure/home/Documents/favorites/domain-driven-design.pdf");
        favorite->add(ddd);
        ca = new File("structure/home/Documents/favorites/clean-architecture.pdf");
        favorite->add(ca);
        cqrs = new File("structure/home/Documents/favorites/cqrs.pdf");
        favorite->add(cqrs);

        note = new File("structure/home/Documents/note.txt");
        document->add(note);

        download = new Folder("structure/home/Downloads");
        home->add(download);

        funny = new File("structure/home/Downloads/funny.png");
        download->add(funny);
    }

    void TearDown() {
        delete home;
        home = nullptr;
        profile = nullptr;
        download = nullptr;
        document = nullptr;
        note = nullptr;
        favorite = nullptr;
        ddd = nullptr;
        ca = nullptr;
        cqrs = nullptr;
        funny = nullptr;
    }
    
    Node * home;
    Node * profile;
    Node * download;
    Node * document;
    Node * note;
    Node * favorite;
    Node * ddd;
    Node * ca;
    Node * cqrs;
    Node * funny;
    IteratorFactory *factory;
};

TEST_F(AbstractFactoryTest, FolderIteratorFactoryCanBeBuilt) {
    ASSERT_NO_THROW(factory = new FolderIteratorFactory());
    delete factory;
}

TEST_F(AbstractFactoryTest, FolderIteratorFactoryShouldbeSingletonPattern) {
    ASSERT_NO_THROW(factory = FolderIteratorFactory::instance());
    IteratorFactory *tmp = FolderIteratorFactory::instance();
    ASSERT_EQ(factory, tmp);
    delete factory;
}

TEST_F(AbstractFactoryTest, FolderIteratorFactoryShouldbeCorrect) {
    ASSERT_NO_THROW(factory = new FolderIteratorFactory());
    Iterator * it = home->createIterator(factory);
    // for(it->first();!it->isDone();it->next()) std::cout << it->currentItem()->name() << std::endl;
    ASSERT_NO_THROW(it->first());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("my_profile", it->currentItem()->name());
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("Documents", it->currentItem()->name());
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("Downloads", it->currentItem()->name());
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());
    delete factory;
    delete it;
}

TEST_F(AbstractFactoryTest, OrderByNameIteratorFactoryCanBeBuilt) {
    ASSERT_NO_THROW(factory = new OrderByNameIteratorFactory());
    delete factory;
}

TEST_F(AbstractFactoryTest, OrderByNameIteratorFactoryShouldbeSingletonPattern) {
    ASSERT_NO_THROW(factory = OrderByNameIteratorFactory::instance());
    ASSERT_EQ(factory, OrderByNameIteratorFactory::instance());
    delete factory;
}

TEST_F(AbstractFactoryTest, OrderByNameIteratorFactoryShouldbeCorrect) {
    ASSERT_NO_THROW(factory = new OrderByNameIteratorFactory());
    Iterator * it = home->createIterator(factory);
    // for(it->first();!it->isDone();it->next()) std::cout << it->currentItem()->name() << std::endl;
    ASSERT_NO_THROW(it->first());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("Documents", it->currentItem()->name());
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("Downloads", it->currentItem()->name());
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("my_profile", it->currentItem()->name());
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());
    delete factory;
    delete it;
}

TEST_F(AbstractFactoryTest, OrderByNameWithFolderFirstIteratorFactoryCanBeBuilt) {
    ASSERT_NO_THROW(factory = new OrderByNameWithFolderFirstIteratorFactory());
    delete factory;
}

TEST_F(AbstractFactoryTest, OrderByNameWithFolderFirstIteratorFactoryShouldbeSingletonPattern) {
    ASSERT_NO_THROW(factory = OrderByNameWithFolderFirstIteratorFactory::instance());
    IteratorFactory *tmp = OrderByNameWithFolderFirstIteratorFactory::instance();
    ASSERT_EQ(factory, tmp);
    delete factory;
}

TEST_F(AbstractFactoryTest, OrderByNameWithFolderFirstIteratorFactoryShouldbeCorrect) {
    ASSERT_NO_THROW(factory = new OrderByNameWithFolderFirstIteratorFactory());
    Iterator * it = home->createIterator(factory);
    // for(it->first();!it->isDone();it->next()) std::cout << it->currentItem()->name() << std::endl;
    ASSERT_NO_THROW(it->first());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("Documents", it->currentItem()->name());
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("Downloads", it->currentItem()->name());
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("my_profile", it->currentItem()->name());
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());
    delete factory;
    delete it;
}


TEST_F(AbstractFactoryTest, OrderByKindIteratorFactoryCanBeBuilt) {
    ASSERT_NO_THROW(factory = new OrderByKindIteratorFactory());
    delete factory;
}

TEST_F(AbstractFactoryTest, OrderByKindIteratorFactoryShouldbeSingletonPattern) {
    ASSERT_NO_THROW(factory = OrderByKindIteratorFactory::instance());
    IteratorFactory *tmp = OrderByKindIteratorFactory::instance();
    ASSERT_EQ(factory, tmp);
    delete factory;
}

TEST_F(AbstractFactoryTest, OrderByKindIteratorFactoryShouldbeCorrect) {
    ASSERT_NO_THROW(factory = new OrderByKindIteratorFactory());
    Iterator * it = home->createIterator(factory);
    // for(it->first();!it->isDone();it->next()) std::cout << it->currentItem()->name() << std::endl;
    ASSERT_NO_THROW(it->first());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("my_profile", it->currentItem()->name());
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("Documents", it->currentItem()->name());
    ASSERT_NO_THROW(it->next());
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("Downloads", it->currentItem()->name());
    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());
    delete factory;
    delete it;
}

