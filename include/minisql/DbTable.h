#pragma once

#include <string>

namespace minisql {

class DbFile;

class DbTable {
public:
    DbTable(DbFile* file, const std::string& name, const std::string& pkeyField);

    DbFile* getFile() const;
    const std::string& getName() const;
    const std::string& getPkeyField() const;

private:
    DbFile* file;
    std::string name;
    std::string pkeyField;
};

} // namespace minisql