#pragma once

namespace minisql {

/**
 * PageId is an interface to a specific page of a specific table.
 */
class PageId {
public:
    /**
     * @return the table associated with this PageId
     */
    virtual int getTableId() const = 0;

    /**
     * @return the page number in the table getTableId()
     */
    virtual int getPageNumber() const = 0;

    /**
     * Compares one PageId to another.
     * @param other The object to compare against.
     * @return true if the objects are equal, false otherwise.
     */
    virtual bool operator==(const PageId& other) const = 0;
};

} // namespace minisql
