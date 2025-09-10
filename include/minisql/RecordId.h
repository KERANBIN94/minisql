//#pragma once
//
//namespace minisql {
//
//class PageId;
//
///**
// * A RecordId is a reference to a specific tuple on a specific page of a
// * specific table.
// */
//class RecordId {
//public:
//    /**
//     * Creates a new RecordId referring to the specified PageId and tuple number.
//     * @param pid the pageid of the page on which the tuple resides
//     * @param tupleno the tuple number within the page.
//     */
//    RecordId(PageId* pid, int tupleno);
//
//    /**
//     * @return the tuple number this RecordId refers to.
//     */
//    int getTupleNumber() const;
//
//    /**
//     * @return the page id this RecordId refers to.
//     */
//    PageId* getPageId() const;
//
//    /**
//     * Two RecordId objects are equal if they represent the same tuple.
//     * @param other The object to compare against.
//     * @return true if the objects are equal, false otherwise.
//     */
//    bool operator==(const RecordId& other) const;
//
//private:
//    PageId* pid;
//    int tupleno;
//};
//
//} // namespace minisql