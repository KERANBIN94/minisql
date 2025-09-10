//#include "minisql/Catalog.h"
//#include "minisql/DbFile.h"
//#include "minisql/DbTable.h"
//#include "minisql/TupleDesc.h"
//#include <stdexcept>
//
//namespace minisql {
//
//void Catalog::addTable(DbFile* file, const std::string& name, const std::string& pkeyField) {
//    int tableid = file->getId();
//    tables[tableid] = new DbTable(file, name, pkeyField);
//    nameToId[name] = tableid;
//}
//
//int Catalog::getTableId(const std::string& name) const {
//    if (nameToId.count(name)) {
//        return nameToId.at(name);
//    }
//    throw std::invalid_argument("Table not found.");
//}
//
//TupleDesc* Catalog::getTupleDesc(int tableid) const {
//    if (tables.count(tableid)) {
//        return const_cast<TupleDesc*>(tables.at(tableid)->getFile()->getTupleDesc());
//    }
//    throw std::invalid_argument("Table not found.");
//}
//
//DbFile* Catalog::getDbFile(int tableid) const {
//    if (tables.count(tableid)) {
//        return tables.at(tableid)->getFile();
//    }
//    throw std::invalid_argument("Table not found.");
//}
//
//std::string Catalog::getPrimaryKey(int tableid) const {
//    if (tables.count(tableid)) {
//        return tables.at(tableid)->getPkeyField();
//    }
//    throw std::invalid_argument("Table not found.");
//}
//
//std::string Catalog::getTableName(int tableid) const {
//    if (tables.count(tableid)) {
//        return tables.at(tableid)->getName();
//    }
//    throw std::invalid_argument("Table not found.");
//}
//
//void Catalog::clear() {
//    tables.clear();
//    nameToId.clear();
//}
//
//} // namespace minisql