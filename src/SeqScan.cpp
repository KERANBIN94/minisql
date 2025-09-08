#include "minisql/SeqScan.h"
#include "minisql/TransactionId.h"
#include "minisql/Tuple.h"
#include "minisql/DbFileIterator.h"
#include "minisql/DbFile.h"
#include "minisql/Database.h"
#include "minisql/Catalog.h"

namespace minisql
{

    SeqScan::SeqScan(TransactionId *tid, int tableid, const std::string &tableAlias)
        : tid(tid), tableid(tableid), tableAlias(tableAlias), it(nullptr) {}

    void SeqScan::open()
    {
        DbFile *file = Database::getInstance()->getCatalog()->getDbFile(tableid);
        it = file->iterator(tid);
        it->open();
    }

    bool SeqScan::hasNext()
    {
        if (it == nullptr)
        {
            return false;
        }
        return it->hasNext();
    }

    Tuple *SeqScan::next()
    {
        if (it == nullptr)
        {
            return nullptr;
        }
        return it->next();
    }

    void SeqScan::rewind()
    {
        if (it != nullptr)
        {
            it->rewind();
        }
    }

    void SeqScan::close()
    {
        if (it != nullptr)
        {
            it->close();
            delete it;
            it = nullptr;
        }
    }

} // namespace minisql