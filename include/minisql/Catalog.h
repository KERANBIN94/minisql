#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace minisql {

class DbFile;
class DbTable;
class TupleDesc;

class Catalog {
public:
    /**
     * Add a new table to the catalog.
     * This table's contents are stored in the specified DbFile.
     * @param file the contents of the table to add;  file.getId() is the identfier of
     *    this file/tupledesc param for the calls getTupleDesc and getFile
     * @param name the name of the table -- may be an empty string.  May not be null.  If a name
     * conflict exists, use the last table to be added as the table for a given name.
     * @param pkeyField the name of the primary key field
     */
    void addTable(DbFile* file, const std::string& name, const std::string& pkeyField);

    /**
     * Return the id of the table with a specified name,
     * @throws std::invalid_argument if the table doesn't exist
     */
    int getTableId(const std::string& name) const;

    /**
     * Returns the tuple descriptor (schema) of the specified table
     * @param tableid The id of the table, as specified by the DbFile.getId()
     *     function passed to addTable
     * @throws std::invalid_argument if the table doesn't exist
     */
    TupleDesc* getTupleDesc(int tableid) const;

    /**
     * Returns the DbFile that can be used to read the contents of the
     * specified table.
     * @param tableid The id of the table, as specified by the DbFile.getId()
     *     function passed to addTable
     */
    DbFile* getDbFile(int tableid) const;

    std::string getPrimaryKey(int tableid) const;

    std::string getTableName(int tableid) const;

    /**
     * Removes all tables from the catalog
     */
    void clear();

private:
    std::unordered_map<int, DbTable*> tables;
    std::unordered_map<std::string, int> nameToId;
};

} // namespace minisql
