#pragma once

#include <vector>

namespace minisql {

// Forward declaration
class Page;
class PageId;
class Tuple;
class TupleDesc;
class TransactionId;
class DbFileIterator;

class DbFile {
public:
    /**
     * Reads the specified page from disk.
     */
    virtual Page* readPage(PageId* pid) = 0;

    /**
     * Pushes the specified page to disk.
     */
    virtual void writePage(Page* p) = 0;

    /**
     * Inserts the specified tuple to the file on behalf of transaction.
     * This method will acquire a lock on the affected pages of the file, and
     * may block until the lock can be acquired.
     *
     * @param tid The transaction performing the update
     * @param t The tuple to add.  This tuple should be updated to reflect its
     *  new log sequence number and record id.
     * @return a vector containing a single Page object, representing the
     *  page that was modified.
     */
    virtual std::vector<Page*> insertTuple(TransactionId* tid, Tuple* t) = 0;

    /**
     * Removes the specified tuple from the file on behalf of the specified
     * transaction.
     * This method will acquire a lock on the affected pages of the file, and
     * may block until the lock can be acquired.
     *
     * @param tid The transaction performing the update
     * @param t The tuple to delete.  This tuple should be updated to reflect its
     *  new log sequence number and record id.
     * @return a vector containing a single Page object, representing the
     *  page that was modified.
     */
    virtual std::vector<Page*> deleteTuple(TransactionId* tid, Tuple* t) = 0;

    /**
     * Returns an iterator over all the tuples stored in this DbFile.
     *
     * @return an iterator over all the tuples stored in this DbFile.
     */
    virtual DbFileIterator* iterator(TransactionId* tid) = 0;

    /**
     * Returns a unique ID for this DbFile.
     */
    virtual int getId() const = 0;

    /**
     * Returns the TupleDesc for the tuples stored in this file.
     * @return the TupleDesc for the tuples stored in this file.
     */
    virtual const TupleDesc* getTupleDesc() const = 0;
};

} // namespace minisql