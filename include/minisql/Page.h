#pragma once

namespace minisql {

class PageId;

class Page {
public:
    /**
     * @return the ID of this page.
     */
    virtual PageId* getId() const = 0;

    /**
     * @return a pointer to the data of this page.
     */
    virtual char* getPageData() = 0;
};

} // namespace minisql