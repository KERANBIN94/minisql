#include "minisql/sqlCompiler/LexicalError.h"

namespace minisql {

    LexicalError::LexicalError(const std::string& message, int line, int column)
        : std::runtime_error(message + " at line " + std::to_string(line) +
            ", column " + std::to_string(column)),
        line_(line), column_(column) {}

    int LexicalError::getLine() const { return line_; }
    int LexicalError::getColumn() const { return column_; }

} // namespace minisql