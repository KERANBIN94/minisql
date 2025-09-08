#pragma once

#include "minisql/Tuple.h"

namespace minisql {

class DbFileIterator {
public:
    virtual void open() = 0;
    virtual bool hasNext() = 0;
    virtual Tuple* next() = 0;
    virtual void rewind() = 0;
    virtual void close() = 0;
};

} // namespace minisql