#include "drawing_mapper.h"

class InMemoryDrawingMapper : public DrawingMapper {


public:
    static InMemoryDrawingMapper * instance();

private:
    static InMemoryDrawingMapper * _instance;
};