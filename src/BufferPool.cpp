//#include "minisql/BufferPool.h"
//#include "minisql/Database.h"
//#include "minisql/Catalog.h"
//#include "minisql/DbFile.h"
//#include "minisql/Page.h"
//#include "minisql/PageId.h"
//#include <stdexcept>
//
//namespace minisql
//{
//
//    BufferPool::BufferPool(int numPages) : numPages(numPages) {}
//
//    Page *BufferPool::getPage(PageId *pid)
//    {
//        if (pages.count(pid))
//        {
//            // Page is in the buffer pool, move it to the front of the LRU list
//            lru.remove(pid);
//            lru.push_front(pid);
//            return pages[pid];
//        }
//
//        // Page is not in the buffer pool, read it from disk
//        if (pages.size() >= numPages)
//        {
//            evictPage();
//        }
//
//        // This is another design issue. BufferPool needs access to the DbFile
//        // to read the page. The diagram doesn't show this relationship.
//        // I'll assume we can get it from a global Database instance.
//        DbFile *file = Database::getInstance()->getCatalog()->getDbFile(pid->getTableId());
//        Page *page = file->readPage(pid);
//
//        pages[pid] = page;
//        lru.push_front(pid);
//
//        return page;
//    }
//
//    void BufferPool::flushPage(PageId *pid)
//    {
//        if (pages.count(pid))
//        {
//            Page *page = pages[pid];
//            // Another design issue: Need to know if the page is dirty.
//            // The diagram doesn't specify a dirty flag in Page.
//            // Assuming we flush it anyway.
//            DbFile *file = Database::getInstance()->getCatalog()->getDbFile(pid->getTableId());
//            file->writePage(page);
//        }
//    }
//
//    void BufferPool::evictPage()
//    {
//        if (lru.empty())
//        {
//            return;
//        }
//        PageId *pid = lru.back();
//        lru.pop_back();
//
//        flushPage(pid);
//        delete pages[pid];
//        pages.erase(pid);
//    }
//
//} // namespace minisql