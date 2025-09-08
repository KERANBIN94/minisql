#pragma once

namespace minisql {

class TransactionId {
public:
    long long getId() const;
private:
    long long id;
};

} // namespace minisql
