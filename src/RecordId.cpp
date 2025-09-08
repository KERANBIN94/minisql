#include "minisql/RecordId.h"
#include "minisql/PageId.h"

namespace minisql
{

    RecordId::RecordId(PageId *pid, int tupleno) : pid(pid), tupleno(tupleno) {}

    int RecordId::getTupleNumber() const
    {
        return tupleno;
    }

    PageId *RecordId::getPageId() const
    {
        return pid;
    }

    bool RecordId::operator==(const RecordId &other) const
    {
        return pid->getTableId() == other.pid->getTableId() && pid->getPageNumber() == other.pid->getPageNumber() && tupleno == other.tupleno;
    }

} // namespace minisql