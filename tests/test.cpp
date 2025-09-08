'''#include "Database.h"
#include "Type.h"
#include "TupleDesc.h"
#include "HeapFile.h"
#include "SeqScan.h"
#include "Field.h"
#include "TransactionId.h"
#include <iostream>
#include <vector>
#include <cassert>

using namespace minisql;

void testHeapFile() {
    // 1. Create a Catalog
    Database::getInstance()->getCatalog()->clear();

    // 2. Create a TupleDesc
    std::vector<Type*> typeAr = {new IntType(), new IntType()};
    std::vector<std::string> fieldAr = {"field1", "field2"};
    TupleDesc* td = new TupleDesc(typeAr, fieldAr);

    // 3. Create a HeapFile
    const char* filename = "test.dat";
    remove(filename); // ensure file is clean
    HeapFile* file = new HeapFile(filename, td);

    // 4. Add the HeapFile to the Catalog
    Database::getInstance()->getCatalog()->addTable(file, "test_table", "field1");

    TransactionId tid;

    // 5. Insert some tuples
    for (int i = 0; i < 10; ++i) {
        Tuple* t = new Tuple(td);
        t->setField(0, new IntField(i));
        t->setField(1, new IntField(i * 2));
        file->insertTuple(&tid, t);
        delete t;
    }

    // 6. Scan the tuples and verify they are correct
    SeqScan scan(&tid, file->getId(), "test_table");
    scan.open();
    int count = 0;
    while (scan.hasNext()) {
        Tuple* t = scan.next();
        IntField* f1 = static_cast<IntField*>(t->getField(0));
        IntField* f2 = static_cast<IntField*>(t->getField(1));
        assert(f1->getValue() == count);
        assert(f2->getValue() == count * 2);
        count++;
    }
    scan.close();
    assert(count == 10);
    std::cout << "Insertion and Scan test passed." << std::endl;

    // 7. Delete a tuple
    Tuple* t_to_delete = new Tuple(td);
    t_to_delete->setField(0, new IntField(5));
    t_to_delete->setField(1, new IntField(10));
    // We need a record ID to delete. We'll get it from a scan.
    SeqScan scan2(&tid, file->getId(), "test_table");
    scan2.open();
    while(scan2.hasNext()){
        Tuple* t = scan2.next();
        if(static_cast<IntField*>(t->getField(0))->getValue() == 5){
            t_to_delete->setRecordId(t->getRecordId());
            break;
        }
    }
    scan2.close();
    file->deleteTuple(&tid, t_to_delete);
    delete t_to_delete;


    // 8. Scan again and verify the deletion
    SeqScan scan3(&tid, file->getId(), "test_table");
    scan3.open();
    count = 0;
    bool found_deleted = false;
    while (scan3.hasNext()) {
        Tuple* t = scan3.next();
        if (static_cast<IntField*>(t->getField(0))->getValue() == 5) {
            found_deleted = true;
        }
        count++;
    }
    scan3.close();
    assert(count == 9);
    assert(!found_deleted);
    std::cout << "Deletion test passed." << std::endl;

    // Clean up
    delete td;
    for(auto type : typeAr) {
        delete type;
    }
}

int main() {
    testHeapFile();
    return 0;
}
''