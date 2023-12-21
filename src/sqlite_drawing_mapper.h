#pragma once

#include <string>

#include <sqlite3.h>

#include "drawing.h"
#include "drawing_mapper.h"
#include "sqlite_abstract_mapper.h"
#include "painter_mapper.h"
#include "scanner.h"
#include "builder.h"
#include "parser.h"

class SQLiteDrawingMapper : public SQLiteAbstractMapper, public DrawingMapper {
public:

    ~SQLiteDrawingMapper () {
        delete _parser;
    }

    void add(DomainObject * Drawing) override;

    Drawing* find(std::string id) override;

    void update(std::string id) override;

    void del(std::string id) override;

    static SQLiteDrawingMapper * instance();

    void cleanCache();

protected:
    SQLiteDrawingMapper ();

    static int callback(void* notUsed, int argc, char** argv, char** colNames);

    std::list<Shape *> convertShapes(char * shape_string);

    std::string addStmt(DomainObject * domainObject) const;
    std::string findByIdStmt(std::string id) const;
    std::string updateStmt(DomainObject * domainObject) const;
    std::string deleteByIdStmt(std::string id) const;

private:
    static SQLiteDrawingMapper * _instance;
    Parser * _parser;
};