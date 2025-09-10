#ifndef MINISQL_TOKEN_H
#define MINISQL_TOKEN_H

#include <string>

namespace minisql {

    enum class TokenType {
        KEYWORD,
        IDENTIFIER,
        CONST_INT,
        CONST_STR,
        OPERATOR,
        DELIMITER,
        END
    };

    struct Token {
        TokenType type;
        std::string lexeme;
        int line;
        int column;

        Token(TokenType t, const std::string& l, int ln, int col)
            : type(t), lexeme(l), line(ln), column(col) {}
    };

} // namespace minisql

#endif