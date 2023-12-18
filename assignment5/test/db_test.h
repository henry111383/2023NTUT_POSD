#include <gtest/gtest.h>
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <list>
#include <memory>
#include "../src/unit_of_work.h"
#include "../src/drawing_mapper.h"
#include "../src/painter_mapper.h"
#include "../src/drawing.h"

class DBSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {
        create_drawing_table();
        create_painter_table();
        populate_drawings();
        populate_painters();
        dm = DrawingMapper::instance();
        dm->setDB("resource/drawing.db");
        pm = PainterMapper::instance();
        pm->setDB("resource/painter.db");
        uw = UnitOfWork::instance();
    }

    void TearDown() override
    {
        drop_drawing_table();
        drop_painter_table();
        sqlite3_close(db);
        sqlite3_close(db_p);
        // delete dm;
        // delete pm;
    }

    void create_drawing_table()
    {
        ASSERT_EQ(0, sqlite3_open("resource/drawing.db", &db));
        const char *stmt = "CREATE TABLE drawing ("
                           "ID         char(6) PRIMARY KEY     not null,"
                           "painter    varchar(50)             not null,"
                           "shapes varchar(1028),"
                           "FOREIGN KEY(painter) REFERENCES painter(ID))";
        int rc = sqlite3_exec(db, stmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void drop_drawing_table()
    {
        const char *dropStmt = "DROP TABLE drawing";
        int rc = sqlite3_exec(db, dropStmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void create_painter_table()
    {
        ASSERT_EQ(0, sqlite3_open("resource/painter.db", &db_p));
        const char *stmt = "CREATE TABLE painter ("
                           "ID         char(6) PRIMARY KEY     not null,"
                           "name    varchar(50)             not null)";
        int rc = sqlite3_exec(db_p, stmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void drop_painter_table()
    {
        const char *dropStmt = "DROP TABLE painter";
        int rc = sqlite3_exec(db_p, dropStmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void populate_drawings()
    {
        const char *s1 = "INSERT INTO drawing"
                         "(ID, painter, shapes)"
                         "values"
                         "('d_0001', 'p_0001', 'triangle 1 1 1')";
        int rc = sqlite3_exec(db, s1, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s2 = "INSERT INTO drawing"
                         "(ID,  painter,   shapes)"
                         "values"
                         "('d_0002', 'p_0001', 'triangle 2 2 2')";
        rc = sqlite3_exec(db, s2, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s3 = "INSERT INTO drawing"
                         "(ID,  painter,   shapes)"
                         "values"
                         "('d_0003', 'p_0002', 'compound { triangle 1 1 1 triangle 2 2 2 } triangle 3 3 3')";
        rc = sqlite3_exec(db, s3, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);
    }

    void populate_painters()
    {
        const char *s1 = "INSERT INTO painter"
                         "(ID, name)"
                         "values"
                         "('p_0001', 'Patrick')";
        int rc = sqlite3_exec(db_p, s1, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s2 = "INSERT INTO painter"
                         "(ID, name)"
                         "values"
                         "('p_0002', 'Mary')";
        rc = sqlite3_exec(db_p, s2, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);
    }

    void display_err_msg_and_fail_if_any(int rc)
    {
        if (rc)
        {
            std::cout << "db error: " << err_msg << std::endl;
            sqlite3_free(err_msg);
        }
        ASSERT_EQ(SQLITE_OK, rc);
    }

    sqlite3 *db;
    sqlite3 *db_p;
    char *err_msg = nullptr;
    DrawingMapper *dm;
    PainterMapper *pm;
    UnitOfWork *uw;
};

TEST_F(DBSuite, Sanity)
{
}

TEST_F(DBSuite, DrawingFindStsmtShouldbeCorrect)
{
    Drawing *drawing = dm->find("d_0001");
    std::string expected = "SELECT * FROM drawing WHERE ID = 'd_0001'";
    ASSERT_EQ(expected, DrawingMapper::instance()->findByIdStmt(drawing->id()));
}

TEST_F(DBSuite, PainterFindStsmtShouldbeCorrect)
{
    Painter *painter = pm->find("p_0001");
    std::string expected = "SELECT * FROM painter WHERE ID = 'p_0001'";
    ASSERT_EQ(expected, PainterMapper::instance()->findByIdStmt(painter->id()));
}

TEST_F(DBSuite, DrawingAddStsmtShouldbeCorrect)
{
    Drawing *drawing = dm->find("d_0001");
    std::string expected = "INSERT INTO drawing (ID, painter, shapes) VALUES ('d_0001', 'p_0001', 'triangle 1 1 1\n')";
    ASSERT_EQ(expected, DrawingMapper::instance()->addStmt(drawing));
}

TEST_F(DBSuite, PainterAddStsmtShouldbeCorrect)
{
    Painter *painter = pm->find("p_0001");
    std::string expected = "INSERT INTO painter (ID, name) VALUES ('p_0001', 'Patrick')";
    ASSERT_EQ(expected, PainterMapper::instance()->addStmt(painter));
}

TEST_F(DBSuite, DrawingUpdateStsmtShouldbeCorrect)
{
    Drawing *drawing = dm->find("d_0001");
    std::string expected = "UPDATE drawing SET Painter='p_0001' WHERE ID='d_0001'";
    ASSERT_EQ(expected, DrawingMapper::instance()->updateStmt(drawing));
}

TEST_F(DBSuite, PainterUpdateStsmtShouldbeCorrect)
{
    Painter *painter = pm->find("p_0001");
    std::string expected = "UPDATE painter SET Name = 'Patrick' WHERE ID='p_0001'";
    ASSERT_EQ(expected, PainterMapper::instance()->updateStmt(painter));
}

TEST_F(DBSuite, DrawingDeleteStsmtShouldbeCorrect)
{
    Drawing *drawing = dm->find("d_0001");
    std::string expected = "DELETE FROM drawing WHERE ID='d_0001'";
    ASSERT_EQ(expected, DrawingMapper::instance()->deleteByIdStmt(drawing->id()));
}

TEST_F(DBSuite, PainterDeleteStsmtShouldbeCorrect)
{
    Painter *painter = pm->find("p_0001");
    std::string expected = "DELETE FROM painter WHERE ID = 'p_0001'";
    ASSERT_EQ(expected, PainterMapper::instance()->deleteByIdStmt(painter->id()));
}

TEST_F(DBSuite, DrawingMapperShouldbeSingleton){
    ASSERT_EQ(dm, DrawingMapper::instance());
}

TEST_F(DBSuite, PainterMapperShouldbeSingleton){
    ASSERT_EQ(pm, PainterMapper::instance());
}

TEST_F(DBSuite, UnitOfWorkShouldbeSingleton){
    ASSERT_EQ(uw, UnitOfWork::instance());
}

TEST_F(DBSuite, findDrawing1)
{
    Drawing *drawing = dm->find("d_0001");
    EXPECT_TRUE(UnitOfWork::instance()->inClean("d_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("d_0001"));
    EXPECT_TRUE(UnitOfWork::instance()->inClean("p_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("p_0001"));
    ASSERT_EQ(drawing->id(), "d_0001");
    ASSERT_EQ(drawing->getShape(0)->perimeter(), 3);
    ASSERT_EQ(drawing->painter()->id(), "p_0001");
    ASSERT_EQ(drawing->painter()->name(), "Patrick");
}

TEST_F(DBSuite, findDrawing2)
{
    Drawing *drawing = dm->find("d_0002");

    EXPECT_TRUE(UnitOfWork::instance()->inClean("d_0002"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("d_0002"));
    EXPECT_TRUE(UnitOfWork::instance()->inClean("p_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("p_0001"));
    ASSERT_EQ(drawing->id(), "d_0002");
    ASSERT_EQ(drawing->getShape(0)->perimeter(), 6);
    ASSERT_EQ(drawing->painter()->id(), "p_0001");
    ASSERT_EQ(drawing->painter()->name(), "Patrick");
}

TEST_F(DBSuite, findDrawing3)
{
    Drawing *drawing = dm->find("d_0003");

    EXPECT_TRUE(UnitOfWork::instance()->inClean("d_0003"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("d_0003"));
    EXPECT_TRUE(UnitOfWork::instance()->inClean("p_0002"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("p_0002"));
    ASSERT_EQ(drawing->id(), "d_0003");
    ASSERT_EQ(drawing->getShape(0)->perimeter(), 9);
    ASSERT_EQ(drawing->painter()->id(), "p_0002");
    ASSERT_EQ(drawing->painter()->name(), "Mary");
}

TEST_F(DBSuite, findNotExistingDrawing)
{
    Drawing *drawing = dm->find("Hi");
    ASSERT_EQ(nullptr, drawing);
}

TEST_F(DBSuite, findNotExistingPainter)
{
    Painter *painter = pm->find("Hi");
    ASSERT_EQ(nullptr, painter);
}

TEST_F(DBSuite, NewDrawingAndPainterThroughUoWAndFind){
    DomainObject *painter_1 = new Painter("p_0004", "Richard");
    DomainObject *drawing = new Drawing("d_0005", static_cast<Painter *>(painter_1));

    UnitOfWork::instance()->registerNew(painter_1);
    UnitOfWork::instance()->registerNew(drawing);
    UnitOfWork::instance()->commit();

    Drawing *drawing_2 = dm->find("d_0005");

    if(drawing_2 == nullptr){
        std::cout << "NULLPTR" <<std::endl;
    }

    ASSERT_EQ(drawing_2->id(), "d_0005");
    ASSERT_EQ(drawing_2->painter()->name(), "Richard");
}

TEST_F(DBSuite, DeletePainterInClean){
    DomainObject *painter = pm->find("p_0002");
    ASSERT_TRUE(UnitOfWork::instance()->inClean("p_0002"));
    UnitOfWork::instance()->registerDeleted(painter);
    UnitOfWork::instance()->commit();
    ASSERT_EQ(pm->find("p_0002"), nullptr); 
}

TEST_F(DBSuite, DeletePainterInNewWithoutCommit){
    DomainObject *painter = new Painter("p_1234", "1234");
    UnitOfWork::instance()->registerNew(painter);
    UnitOfWork::instance()->registerDeleted(painter);
    ASSERT_FALSE(UnitOfWork::instance()->inNew(painter->id()));
}