#ifndef MINISQL_LEXER_H
#define MINISQL_LEXER_H

#include "minisql/sqlCompiler/Token.h"
#include "minisql/sqlCompiler/LexicalError.h"
#include <vector>
#include <string>

namespace minisql {

    class Lexer {
    public:
        Lexer(const std::string& input);
        std::vector<Token> tokenize();

    private:
        std::string input;
        int index = 0;
        int line = 1;
        int column = 1;

        char peek();
        char advance();
        void skipWhitespace();
        bool isKeyword(const std::string& word) const;
        Token readWord();
        Token readNumber();
        Token readString();
        Token readOperator();
        Token readDelimiter();
    };

} // namespace minisql

#endif