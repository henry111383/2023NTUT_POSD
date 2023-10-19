#include <gtest/gtest.h>
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"


TEST(NodeTest, FileWithPolymorphismShouldBeCorrectlyBuilt)
{
	Node *tmp;
	ASSERT_NO_THROW(tmp = new File("D1/f1"));
	delete tmp;
}

TEST(NodeTest, FoderWithPolymorphismShouldBeCorrectlyBuilt)
{
	Node *tmp;
	ASSERT_NO_THROW(tmp = new Folder("D1/D2"));
	delete tmp;
}

TEST(NodeTest, NameWithPolymorphismShouldBeCorrect)
{
	Node *D1, *D2, *D3, *f1, *f2, *f3, *f4;
	D1 = new Folder("D1");
	f1 = new File("D1/f1");
	D2 = new Folder("D1/D2");
	f2 = new File("D1/f2");
	f3 = new File("D1/D2/f3");
	D3 = new Folder("D1/D2/D3");
	f4 = new File("D1/D2/f4");

	ASSERT_EQ("D1", D1->name());
  	ASSERT_EQ("D2", D2->name());
	ASSERT_EQ("D3", D3->name());
	ASSERT_EQ("f1", f1->name());
	ASSERT_EQ("f2", f2->name());
	ASSERT_EQ("f3", f3->name());
	ASSERT_EQ("f4", f4->name());

	delete D1;
	delete D2;
	delete D3;
	delete f1;
	delete f2;
	delete f3;
	delete f4;
}

TEST(NodeTest, PathWithPolymorphismShouldBeCorrect)
{
	Node *D1, *D2, *D3, *f1, *f2, *f3, *f4;
	D1 = new Folder("D1");
	f1 = new File("D1/f1");
	D2 = new Folder("D1/D2");
	f2 = new File("D1/f2");
	f3 = new File("D1/D2/f3");
	D3 = new Folder("D1/D2/D3");
	f4 = new File("D1/D2/f4");

	ASSERT_EQ("D1", D1->path());
	ASSERT_EQ("D1/D2", D2->path());
	ASSERT_EQ("D1/D2/D3", D3->path());
	ASSERT_EQ("D1/f1", f1->path());
	ASSERT_EQ("D1/f2", f2->path());
	ASSERT_EQ("D1/D2/f3", f3->path());
	ASSERT_EQ("D1/D2/f4", f4->path());

	delete D1;
	delete D2;
	delete D3;
	delete f1;
	delete f2;
	delete f3;
	delete f4;
}

TEST(NodeTest, addWithPolymorphismShouldBeCorrect)
{
	Node *D1, *D2, *D3, *f1, *f2, *f3, *f4;
	D1 = new Folder("D1");
	f1 = new File("D1/f1");
	D2 = new Folder("D1/D2");
	f2 = new File("D1/f2");

	ASSERT_NO_THROW(D1 -> add(f1));
	ASSERT_NO_THROW(D1 -> add(D2));
	ASSERT_NO_THROW(D1 -> add(f2));

	f3 = new File("D1/D2/f3");
	D3 = new Folder("D1/D2/D3");
	f4 = new File("D1/D2/f4");

	ASSERT_NO_THROW(D2 -> add(f3));
	ASSERT_NO_THROW(D2 -> add(D3));
	ASSERT_NO_THROW(D2 -> add(f4));

	delete D1;
	delete D2;
	delete D3;
	delete f1;
	delete f2;
	delete f3;
	delete f4;
}

TEST(NodeTest, RemoveWithPolymorphismShouldBeCorrect)
{
	Node *D1, *D2, *D3, *f1, *f2, *f3, *f4;
	D1 = new Folder("D1");
	f1 = new File("D1/f1");
	D2 = new Folder("D1/D2");
	f2 = new File("D1/f2");

	ASSERT_NO_THROW(D1 -> add(f1));
	ASSERT_NO_THROW(D1 -> add(D2));
	ASSERT_NO_THROW(D1 -> add(f2));

	f3 = new File("D1/D2/f3");
	D3 = new Folder("D1/D2/D3");
	f4 = new File("D1/D2/f4");

	ASSERT_NO_THROW(D2 -> add(f3));
	ASSERT_NO_THROW(D2 -> add(D3));
	ASSERT_NO_THROW(D2 -> add(f4));

	ASSERT_NO_THROW(D1->remove("D1/f1"));
	ASSERT_NO_THROW(D1->remove("D1/D2"));
	ASSERT_NO_THROW(D1->remove("D1/f2"));
	ASSERT_NO_THROW(D1->remove("D1/D2/D3"));

	delete D1;
	delete D2;
	delete D3;
	delete f1;
	delete f2;
	delete f3;
	delete f4;
}

TEST(NodeTest, GetChildByNameWithPolymorphismShouldBeCorrect)
{
	Node *D1, *D2, *D3, *f1, *f2, *f3, *f4;
	D1 = new Folder("D1");
	f1 = new File("D1/f1");
	D2 = new Folder("D1/D2");
	f2 = new File("D1/f2");

	ASSERT_NO_THROW(D1 -> add(f1));
	ASSERT_NO_THROW(D1 -> add(D2));
	ASSERT_NO_THROW(D1 -> add(f2));

	f3 = new File("D1/D2/f3");
	D3 = new Folder("D1/D2/D3");
	f4 = new File("D1/D2/f4");

	ASSERT_NO_THROW(D2 -> add(f3));
	ASSERT_NO_THROW(D2 -> add(D3));
	ASSERT_NO_THROW(D2 -> add(f4));

	ASSERT_EQ(f1, D1->getChildByName("f1"));
	ASSERT_EQ(nullptr, D1->getChildByName("f3"));

	delete D1;
	delete D2;
	delete D3;
	delete f1;
	delete f2;
	delete f3;
	delete f4;
}

TEST(NodeTest, FindWithPolymorphismShouldBeCorrect)
{
	Node *D1, *D2, *D3, *f1, *f2, *f3, *f4;
	D1 = new Folder("D1");
	f1 = new File("D1/f1");
	D2 = new Folder("D1/D2");
	f2 = new File("D1/f2");

	ASSERT_NO_THROW(D1 -> add(f1));
	ASSERT_NO_THROW(D1 -> add(D2));
	ASSERT_NO_THROW(D1 -> add(f2));

	f3 = new File("D1/D2/f3");
	D3 = new Folder("D1/D2/D3");
	f4 = new File("D1/D2/f4");

	ASSERT_NO_THROW(D2 -> add(f3));
	ASSERT_NO_THROW(D2 -> add(D3));
	ASSERT_NO_THROW(D2 -> add(f4));

	ASSERT_EQ(D3, D1->find("D1/D2/D3"));
	ASSERT_EQ(nullptr, D1->find("D1/D2/D4"));

	delete D1;
	delete D2;
	delete D3;
	delete f1;
	delete f2;
	delete f3;
	delete f4;
}

TEST(NodeTest, NumberOfFilesWithPolymorphismShouldBeCorrect)
{
	Node *D1, *D2, *D3, *f1, *f2, *f3, *f4;
	D1 = new Folder("D1");
	f1 = new File("D1/f1");
	D2 = new Folder("D1/D2");
	f2 = new File("D1/f2");

	ASSERT_NO_THROW(D1 -> add(f1));
	ASSERT_NO_THROW(D1 -> add(D2));
	ASSERT_NO_THROW(D1 -> add(f2));

	f3 = new File("D1/D2/f3");
	D3 = new Folder("D1/D2/D3");
	f4 = new File("D1/D2/f4");

	ASSERT_NO_THROW(D2 -> add(f3));
	ASSERT_NO_THROW(D2 -> add(D3));
	ASSERT_NO_THROW(D2 -> add(f4));

	ASSERT_EQ(4, D1->numberOfFiles());
	ASSERT_EQ(2, D2->numberOfFiles());
	ASSERT_EQ(0, D3->numberOfFiles());

	delete D1;
	delete D2;
	delete D3;
	delete f1;
	delete f2;
	delete f3;
	delete f4;
}