//#include "minisql/HeapPage.h"
//#include "minisql/common.h"
//#include "minisql/Field.h"
//#include "minisql/HeapPageId.h"
//#include "minisql/Tuple.h"
//#include "minisql/TupleDesc.h"
//#include "minisql/RecordId.h"
//#include "minisql/PageId.h"
//#include <stdexcept>
//#include <algorithm>
//
//namespace minisql {
//
//// HeapPageIterator
//HeapPage::HeapPageIterator::HeapPageIterator(HeapPage* page, int index)
//    : page(page), currentIndex(index) {
//    findNextUsed();
//}
//
//HeapPage::HeapPageIterator& HeapPage::HeapPageIterator::operator++() {
//    currentIndex++;
//    findNextUsed();
//    return *this;
//}
//
//bool HeapPage::HeapPageIterator::operator!=(const HeapPageIterator& other) const {
//    return currentIndex != other.currentIndex;
//}
//
//Tuple HeapPage::HeapPageIterator::operator*() {
//    // This is complex. We need to deserialize a tuple from the page data.
//    Tuple t(page->td);
//    int offset = page->getHeaderSize() + currentIndex * page->td->getSize();
//    for (int i = 0; i < page->td->numFields(); ++i) {
//        // This is a simplification. We need to handle different field types.
//        // For now, assuming IntField.
//        int val = *reinterpret_cast<int*>(&page->pageData[offset + i * 4]);
//        t.setField(i, new IntField(val));
//    }
//    RecordId* rid = new RecordId(page->pid, currentIndex);
//    t.setRecordId(rid);
//    return t;
//}
//
//void HeapPage::HeapPageIterator::findNextUsed() {
//    while (currentIndex < page->numSlots && !page->isSlotUsed(currentIndex)) {
//        currentIndex++;
//    }
//}
//
//// HeapPage
//HeapPage::HeapPage(HeapPageId* id, TupleDesc* td, const std::vector<char>& data)
//    : pid(id), td(td), pageData(data) {
//    calculateNumSlots();
//    int headerSize = getHeaderSize();
//    header.assign(pageData.begin(), pageData.begin() + headerSize);
//}
//
//PageId* HeapPage::getId() const {
//    return pid;
//}
//
//char* HeapPage::getPageData() {
//    // Update header in pageData before returning
//    std::copy(header.begin(), header.end(), pageData.begin());
//    return pageData.data();
//}
//
//int HeapPage::getNumTuples() const {
//    int count = 0;
//    for (int i = 0; i < numSlots; ++i) {
//        if (isSlotUsed(i)) {
//            count++;
//        }
//    }
//    return count;
//}
//
//int HeapPage::getNumSlots() const {
//    return numSlots;
//}
//
//int HeapPage::getNumEmptySlots() const {
//    return numSlots - getNumTuples();
//}
//
//bool HeapPage::isSlotUsed(int i) const {
//    if (i < 0 || i >= numSlots) {
//        throw std::out_of_range("Slot index out of range.");
//    }
//    int byteIndex = i / 8;
//    int bitIndex = i % 8;
//    return (header[byteIndex] >> bitIndex) & 1;
//}
//
//void HeapPage::setSlotUsed(int i, bool value) {
//    if (i < 0 || i >= numSlots) {
//        throw std::out_of_range("Slot index out of range.");
//    }
//    int byteIndex = i / 8;
//    int bitIndex = i % 8;
//    if (value) {
//        header[byteIndex] |= (1 << bitIndex);
//    } else {
//        header[byteIndex] &= ~(1 << bitIndex);
//    }
//}
//
//HeapPage::HeapPageIterator HeapPage::begin() {
//    return HeapPageIterator(this, 0);
//}
//
//HeapPage::HeapPageIterator HeapPage::end() {
//    return HeapPageIterator(this, numSlots);
//}
//
//void HeapPage::insertTuple(Tuple* t) {
//    if (getNumEmptySlots() == 0) {
//        throw std::runtime_error("Page is full.");
//    }
//    if (*t->getTupleDesc() != *td) {
//        throw std::invalid_argument("TupleDesc mismatch.");
//    }
//
//    for (int i = 0; i < numSlots; ++i) {
//        if (!isSlotUsed(i)) {
//            setSlotUsed(i, true);
//            int offset = getHeaderSize() + i * td->getSize();
//            // Serialize tuple to pageData
//            for (int j = 0; j < td->numFields(); ++j) {
//                // Simplification: assuming IntField
//                IntField* f = static_cast<IntField*>(t->getField(j));
//                *reinterpret_cast<int*>(&pageData[offset + j * 4]) = f->getValue();
//            }
//            RecordId* rid = new RecordId(pid, i);
//            t->setRecordId(rid);
//            return;
//        }
//    }
//}
//
//void HeapPage::deleteTuple(Tuple* t) {
//    RecordId* rid = t->getRecordId();
//    if (rid == nullptr || rid->getPageId()->getTableId() != pid->getTableId() || rid->getPageId()->getPageNumber() != pid->getPageNumber()) {
//        throw std::invalid_argument("Tuple does not belong to this page.");
//    }
//    int tupleNo = rid->getTupleNumber();
//    if (!isSlotUsed(tupleNo)) {
//        throw std::invalid_argument("Tuple is not on this page.");
//    }
//    setSlotUsed(tupleNo, false);
//}
//
//
//void HeapPage::calculateNumSlots() {
//    int tupleSize = td->getSize();
//    if (tupleSize == 0) {
//        numSlots = 0;
//        return;
//    }
//    numSlots = (PAGE_SIZE * 8) / (tupleSize * 8 + 1);
//}
//
//int HeapPage::getHeaderSize() const {
//    return (numSlots + 7) / 8;
//}
//
//} // namespace minisql