#pragma once

#include "minisql/Page.h"
#include <vector>
#include <iterator>

namespace minisql {

class HeapPageId;
class Tuple;
class TupleDesc;

class HeapPage : public Page {
public:
    class HeapPageIterator : public std::iterator<std::input_iterator_tag, Tuple> {
    public:
        HeapPageIterator(HeapPage* page, int index);
        HeapPageIterator& operator++();
        bool operator!=(const HeapPageIterator& other) const;
        Tuple operator*();
    private:
        HeapPage* page;
        int currentIndex;
        void findNextUsed();
    };

    HeapPage(HeapPageId* id, TupleDesc* td, const std::vector<char>& data);

    PageId* getId() const override;
    char* getPageData() override;

    int getNumTuples() const;
    int getNumSlots() const;
    int getNumEmptySlots() const;

    bool isSlotUsed(int i) const;
    void setSlotUsed(int i, bool value);

    HeapPageIterator begin();
    HeapPageIterator end();

    void insertTuple(Tuple* t);
    void deleteTuple(Tuple* t);

private:
    HeapPageId* pid;
    TupleDesc* td;
    std::vector<char> pageData;
    int numSlots;
    std::vector<unsigned char> header;

    void calculateNumSlots();
    int getHeaderSize() const;
};

} // namespace minisql