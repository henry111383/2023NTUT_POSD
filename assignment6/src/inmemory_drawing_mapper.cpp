#include "inmemory_drawing_mapper.h"

InMemoryDrawingMapper::InMemoryDrawingMapper(){};
InMemoryDrawingMapper * InMemoryDrawingMapper::instance() {
    if(_instance == nullptr) {
        _instance = new InMemoryDrawingMapper();
    }
    return _instance;
}
