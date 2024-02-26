#include <gtest/gtest.h>
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <list>
#include "../src/unit_of_work.h"
#include "../src/drawing_mapper.h"
#include "../src/drawing.h"
#include "../src/triangle.h"
#include "../src/shape.h"
#include "../src/painter.h"
#include "../src/db_mode.h"
#include <memory>

TEST(dbControl, DbModeShouldbeOK){
    DbMode *db_mode = DbMode::instance();
    db_mode->setMode(mode::InMemory);
    ASSERT_EQ(mode::InMemory, db_mode->getMode());

}