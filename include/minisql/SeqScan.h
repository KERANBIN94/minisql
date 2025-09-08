#pragma once

#include "minisql/DbFileIterator.h"
#include <string>

namespace minisql {

class TransactionId;
class Tuple;

class SeqScan : public DbFileIterator {
public:
    /**
     * Creates a sequential scan over the specified table as a part of the
     * specified transaction.
     *
     * @param tid The transaction this scan is running as a part of.
     * @param tableid the table to scan.
     * @param tableAlias the alias of this table (needed by the parser);
     *         the returned tupleDesc should have fields with name tableAlias.fieldName
     *         (note: this class is not responsible for handling a case where tableAlias
     *         is null.  It shouldn't crash if it is, but the resulting name can be null.fieldName,
     *         tableAlias.null, or null.null).
     */
    SeqScan(TransactionId* tid, int tableid, const std::string& tableAlias);

    void open() override;
    bool hasNext() override;
    Tuple* next() override;
    void rewind() override;
    void close() override;

private:
    TransactionId* tid;
    int tableid;
    std::string tableAlias;
    DbFileIterator* it;
};

} // namespace minisql