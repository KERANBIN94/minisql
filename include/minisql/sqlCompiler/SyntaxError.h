#ifndef MINISQL_SYNTAX_ERROR_H
#define MINISQL_SYNTAX_ERROR_H

#include <stdexcept>
#include <string>
#include "minisql/sqlCompiler/Token.h"

namespace minisql {

    class SyntaxError : public std::runtime_error {
    public:
        SyntaxError(const std::string& message, int line, int column);
        SyntaxError(const std::string& message, const Token& token);

        int getLine() const;
        int getColumn() const;

    private:
        int line_;
        int column_;
    };

} // namespace minisql

#endif