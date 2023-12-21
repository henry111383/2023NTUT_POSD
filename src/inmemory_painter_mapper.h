#include "painter_mapper.h"

class InMemoryPainterMapper : public PainterMapper {


public:
    static InMemoryPainterMapper * instance();

private:
    static InMemoryPainterMapper * _instance;
};