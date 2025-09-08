#include "minisql/HeapPageId.h"

namespace minisql {

HeapPageId::HeapPageId(int tableId, int pgNo) : tableId(tableId), pgNo(pgNo) {}

int HeapPageId::getTableId() const {
    return tableId;
}

int HeapPageId::getPageNumber() const {
    return pgNo;
}

bool HeapPageId::operator==(const PageId& other) const {
    const HeapPageId* hpid = dynamic_cast<const HeapPageId*>(&other);
    if (hpid) {
        return tableId == hpid->tableId && pgNo == hpid->pgNo;
    }
    return false;
}

} // namespace minisql