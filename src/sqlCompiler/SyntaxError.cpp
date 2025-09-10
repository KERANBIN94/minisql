#include "minisql/sqlCompiler/SyntaxError.h"

namespace minisql {

    SyntaxError::SyntaxError(const std::string& message, int line, int column)
        : std::runtime_error(message + " at line " + std::to_string(line) +
            ", column " + std::to_string(column)),
        line_(line), column_(column) {}

    SyntaxError::SyntaxError(const std::string& message, const Token& token)
        : SyntaxError(message, token.line, token.column) {}

    int SyntaxError::getLine() const { return line_; }
    int SyntaxError::getColumn() const { return column_; }

} // namespace minisql