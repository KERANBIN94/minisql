#pragma once

#include "minisql/Catalog.h"
#include "minisql/BufferPool.h"

namespace minisql
{

    class Database
    {
    public:
        static Database *getInstance();
        Catalog *getCatalog();
        BufferPool *getBufferPool();

    private:
        Database();
        static Database *instance;
        Catalog *catalog;
        BufferPool *bufferPool;
    };

} // namespace minisql
