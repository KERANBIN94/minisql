#include "minisql/Database.h"

namespace minisql
{

    Database *Database::instance = nullptr;

    Database::Database()
    {
        catalog = new Catalog();
        bufferPool = new BufferPool(100); // Default 100 pages
    }

    Database *Database::getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Database();
        }
        return instance;
    }

    Catalog *Database::getCatalog()
    {
        return catalog;
    }

    BufferPool *Database::getBufferPool()
    {
        return bufferPool;
    }

} // namespace minisql
