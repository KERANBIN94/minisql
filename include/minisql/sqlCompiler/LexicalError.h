#ifndef MINISQL_LEXICAL_ERROR_H
#define MINISQL_LEXICAL_ERROR_H

#include <stdexcept>
#include <string>

namespace minisql {

    class LexicalError : public std::runtime_error {
    public:
        LexicalError(const std::string& message, int line, int column);

        int getLine() const;
        int getColumn() const;

    private:
        int line_;
        int column_;
    };

} // namespace minisql

#endif