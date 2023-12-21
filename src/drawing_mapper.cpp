#include "drawing_mapper.h"
#include "sqlite_drawing_mapper.h"
#include "inmemory_drawing_mapper.h"
#include <sqlite3.h>
#include <string>
#include <map>
#include "drawing.h"
#include "triangle.h"
#include "parser.h"
#include "scanner.h"
#include "builder.h"
#include "domain_object.h"
#include "db_mode.h"


// DrawingMapper* DrawingMapper::_instance = nullptr;

// // DrawingMapper::DrawingMapper(){}


DrawingMapper* DrawingMapper::instance() {
    DbMode *db_mode = DbMode::instance();

    if(_instance == nullptr) {
        if(db_mode->getMode()==mode::SQLite){
            _instance = SQLiteDrawingMapper::instance();
            return _instance;
        }
        if(db_mode->getMode()==mode::InMemory){
            _instance = InMemoryDrawingMapper::instance();
            return _instance;
        }
    }
    return _instance;
}

