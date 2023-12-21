#include "painter_mapper.h"
#include "sqlite_painter_mapper.h"
#include "inmemory_painter_mapper.h"
#include "db_mode.h"
#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"
#include "sqlite_abstract_mapper.h"

PainterMapper* PainterMapper::_instance = nullptr;

PainterMapper* PainterMapper::instance() {
    DbMode *db_mode = DbMode::instance();

    if(_instance == nullptr) {
        if(db_mode->getMode()==mode::SQLite){
            _instance = SQLitePainterMapper::instance();
            return _instance;
        }
        if(db_mode->getMode()==mode::InMemory){
            _instance = InMemoryPainterMapper::instance();
            return _instance;
        }
    }
    return _instance;
}
