//#pragma once
//
//#include "minisql/PageId.h"
//
//namespace minisql {
//
//class HeapPageId : public PageId {
//public:
//    HeapPageId(int tableId, int pgNo);
//
//    int getTableId() const override;
//    int getPageNumber() const override;
//    bool operator==(const PageId& other) const override;
//
//private:
//    int tableId;
//    int pgNo;
//};
//
//} // namespace minisql