//#include "minisql/HeapFile.h"
//#include "minisql/HeapPage.h"
//#include "minisql/HeapPageId.h"
//#include "minisql/BufferPool.h"
//#include "minisql/Database.h"
//#include "minisql/common.h"
//#include "minisql/RecordId.h"
//#include <stdexcept>
//
//namespace minisql
//{
//
//    // HeapFileIterator
//    HeapFile::HeapFileIterator::HeapFileIterator(HeapFile *file, TransactionId *tid)
//        : file(file), tid(tid), currentPage(0), tupleIndex(-1) {}
//
//    void HeapFile::HeapFileIterator::open()
//    {
//        currentPage = 0;
//        tupleIndex = 0;
//        fetchTuples();
//    }
//
//    bool HeapFile::HeapFileIterator::hasNext()
//    {
//        if (tupleIndex < tuples.size())
//        {
//            return true;
//        }
//        if (currentPage >= file->getNumPages() - 1)
//        {
//            return false;
//        }
//        currentPage++;
//        fetchTuples();
//        return tupleIndex < tuples.size();
//    }
//
//    Tuple *HeapFile::HeapFileIterator::next()
//    {
//        if (!hasNext())
//        {
//            throw std::out_of_range("No more tuples.");
//        }
//        return &tuples[tupleIndex++];
//    }
//
//    void HeapFile::HeapFileIterator::rewind()
//    {
//        close();
//        open();
//    }
//
//    void HeapFile::HeapFileIterator::close()
//    {
//        currentPage = 0;
//        tupleIndex = -1;
//        tuples.clear();
//    }
//
//    void HeapFile::HeapFileIterator::fetchTuples()
//    {
//        if (currentPage >= file->getNumPages())
//        {
//            tuples.clear();
//            tupleIndex = 0;
//            return;
//        }
//        HeapPageId pid(file->getId(), currentPage);
//        HeapPage *page = static_cast<HeapPage *>(Database::getInstance()->getBufferPool()->getPage(&pid));
//        tuples.clear();
//        for (auto it = page->begin(); it != page->end(); ++it)
//        {
//            tuples.push_back(*it);
//        }
//        tupleIndex = 0;
//    }
//
//    // HeapFile
//    HeapFile::HeapFile(const std::string &file, TupleDesc *td)
//        : file(file), td(td)
//    {
//        tableId = reinterpret_cast<intptr_t>(this); // Simple unique ID
//        f.open(file, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
//        if (!f.is_open())
//        {
//            // if file does not exist, create it
//            f.open(file, std::ios::out | std::ios::binary);
//            f.close();
//            f.open(file, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
//        }
//    }
//
//    HeapFile::~HeapFile()
//    {
//        if (f.is_open())
//        {
//            f.close();
//        }
//    }
//
//    const std::string &HeapFile::getFile() const
//    {
//        return file;
//    }
//
//    int HeapFile::getId() const
//    {
//        return tableId;
//    }
//
//    const TupleDesc *HeapFile::getTupleDesc() const
//    {
//        return td;
//    }
//
//    Page *HeapFile::readPage(PageId *pid)
//    {
//        if (pid->getTableId() != getId())
//        {
//            throw std::invalid_argument("Page does not belong to this table.");
//        }
//        int pgNo = pid->getPageNumber();
//        int offset = pgNo * PAGE_SIZE;
//
//        f.seekg(0, std::ios::end);
//        if (offset >= f.tellg())
//        {
//            throw std::invalid_argument("Page number out of range.");
//        }
//
//        std::vector<char> data(PAGE_SIZE);
//        f.seekg(offset, std::ios::beg);
//        f.read(data.data(), PAGE_SIZE);
//
//        return new HeapPage(static_cast<HeapPageId *>(pid), const_cast<TupleDesc *>(td), data);
//    }
//
//    void HeapFile::writePage(Page *p)
//    {
//        PageId *pid = p->getId();
//        int pgNo = pid->getPageNumber();
//        int offset = pgNo * PAGE_SIZE;
//
//        f.seekp(offset, std::ios::beg);
//        f.write(p->getPageData(), PAGE_SIZE);
//    }
//
//    std::vector<Page *> HeapFile::insertTuple(TransactionId *tid, Tuple *t)
//    {
//        for (int i = 0; i < getNumPages(); ++i)
//        {
//            HeapPageId pid(getId(), i);
//            HeapPage *page = static_cast<HeapPage *>(Database::getInstance()->getBufferPool()->getPage(&pid));
//            if (page->getNumEmptySlots() > 0)
//            {
//                page->insertTuple(t);
//                return {page};
//            }
//        }
//
//        // No page with empty slots found, create a new one
//        int newPgNo = getNumPages();
//        HeapPageId pid(getId(), newPgNo);
//        std::vector<char> data(PAGE_SIZE, 0);
//        HeapPage *newPage = new HeapPage(&pid, const_cast<TupleDesc *>(td), data);
//        newPage->insertTuple(t);
//        writePage(newPage);
//        return {newPage};
//    }
//
//    std::vector<Page *> HeapFile::deleteTuple(TransactionId *tid, Tuple *t)
//    {
//        RecordId *rid = t->getRecordId();
//        if (rid == nullptr)
//        {
//            throw std::invalid_argument("Tuple has no RecordId.");
//        }
//        PageId *pid = rid->getPageId();
//        HeapPage *page = static_cast<HeapPage *>(Database::getInstance()->getBufferPool()->getPage(pid));
//        page->deleteTuple(t);
//        return {page};
//    }
//
//    DbFileIterator *HeapFile::iterator(TransactionId *tid)
//    {
//        return new HeapFileIterator(this, tid);
//    }
//
//    int HeapFile::getNumPages() const
//    {
//        f.seekg(0, std::ios::end);
//        long long size = f.tellg();
//        if (size == -1)
//            return 0;
//        return size / PAGE_SIZE;
//    }
//
//} // namespace minisql
