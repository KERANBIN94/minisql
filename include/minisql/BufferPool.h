#pragma once

#include "minisql/common.h"
#include <unordered_map>
#include <list>

namespace minisql
{

class Page;
class PageId;

    class BufferPool
    {
    public:
        /**
         * Creates a BufferPool with the specified number of pages.
         * @param numPages the maximum number of pages in this buffer pool.
         */
        BufferPool(int numPages);

        /**
         * Retrieve the specified page from the buffer pool.
         * Should block if the page is not in the buffer pool and must be read from disk.
         *
         * @param pid the ID of the page
         * @return the page
         */
        Page *getPage(PageId *pid);

        /**
         * Flushes a certain page to disk
         * @param pid the ID of the page to flush
         */
        void flushPage(PageId *pid);

        /**
         * Discards a page from the buffer pool.
         * Flushes the page to disk to ensure dirty pages are updated on disk.
         */
        void evictPage();

    private:
        int numPages;
        std::unordered_map<PageId *, Page *> pages;
        std::list<PageId *> lru;
    };

} // namespace minisql