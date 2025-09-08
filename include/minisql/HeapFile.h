#pragma once

#include "minisql/DbFile.h"
#include "minisql/DbFileIterator.h"
#include <string>
#include <fstream>
#include <vector>

namespace minisql {

class TupleDesc;
class Tuple;
class TransactionId;
class Page;
class PageId;

class HeapFile : public DbFile {
public:
    class HeapFileIterator : public DbFileIterator {
    public:
        HeapFileIterator(HeapFile* file, TransactionId* tid);
        void open() override;
        bool hasNext() override;
        Tuple* next() override;
        void rewind() override;
        void close() override;
    private:
        HeapFile* file;
        TransactionId* tid;
        int currentPage;
        std::vector<Tuple> tuples;
        int tupleIndex;
        void fetchTuples();
    };

    HeapFile(const std::string& file, TupleDesc* td);
    ~HeapFile();

    const std::string& getFile() const;
    int getId() const override;
    const TupleDesc* getTupleDesc() const override;

    Page* readPage(PageId* pid) override;
    void writePage(Page* p) override;

    std::vector<Page*> insertTuple(TransactionId* tid, Tuple* t) override;
    std::vector<Page*> deleteTuple(TransactionId* tid, Tuple* t) override;

    DbFileIterator* iterator(TransactionId* tid) override;

    int getNumPages() const;

private:
    std::string file;
    TupleDesc* td;
    int tableId;
    mutable std::fstream f;
};

} // namespace minisql