#ifndef MINISQL_DATABASE_H
#define MINISQL_DATABASE_H

namespace minisql {

	void startDatabase();

} // namespace minisql

#endif



//#pragma once
//
//#include "minisql/Catalog.h"
//#include "minisql/BufferPool.h"
//
//namespace minisql
//{
//
//    class Database
//    {
//    public:
//        static Database *getInstance();
//        Catalog *getCatalog();
//        BufferPool *getBufferPool();
//
//    private:
//        Database();
//        static Database *instance;
//        Catalog *catalog;
//        BufferPool *bufferPool;
//    };
//
//} // namespace minisql
