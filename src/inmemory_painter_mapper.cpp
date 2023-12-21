#include "inmemory_painter_mapper.h"

InMemoryPainterMapper::InMemoryPainterMapper(){};
InMemoryPainterMapper * InMemoryPainterMapper::instance() {
    if(_instance == nullptr) {
        _instance = new InMemoryPainterMapper();
    }
    return _instance;
}
