#include "minisql/sqlCompiler/Lexer.h"
#include "minisql/sqlCompiler/LexicalError.h"
#include <cctype>
#include <unordered_map>

namespace minisql {

    // 关键字映射表
    const std::unordered_map<std::string, TokenType> keywords = {
        {"SELECT", TokenType::KEYWORD},
        {"FROM",   TokenType::KEYWORD},
        {"WHERE",  TokenType::KEYWORD},
        {"CREATE", TokenType::KEYWORD},
        {"TABLE",  TokenType::KEYWORD},
        {"INSERT", TokenType::KEYWORD},
        {"INTO",   TokenType::KEYWORD},
        {"VALUES", TokenType::KEYWORD},
        {"DELETE", TokenType::KEYWORD}
    };

    Lexer::Lexer(const std::string& input) : input(input) {}

    std::vector<Token> Lexer::tokenize() {
        std::vector<Token> tokens;
        while (index < input.size()) {
            skipWhitespace();
            if (index >= input.size()) break;

            char c = peek();
            if (isalpha(c) || c == '_') {
                tokens.push_back(readWord());
            }
            else if (isdigit(c)) {
                tokens.push_back(readNumber());
            }
            else if (c == '\'') {
                tokens.push_back(readString());
            }
            else if (c == '=' || c == '>' || c == '<' || c == '!') {
                tokens.push_back(readOperator());
            }
            else if (c == ',' || c == ';' || c == '(' || c == ')' || c == '*') {
                tokens.push_back(readDelimiter());
            }
            else {
                throw LexicalError(
                    "Lexical error: invalid character '" + std::string(1, c) + "'",
                    line, column
                );
            }
        }
        tokens.push_back(Token(TokenType::END, "", line, column));
        return tokens;
    }

    char Lexer::peek() {
        return input[index];
    }

    char Lexer::advance() {
        if (index >= input.size()) return '\0';
        char c = input[index++];
        if (c == '\n') {
            line++;
            column = 1;
        }
        else {
            column++;
        }
        return c;
    }

    void Lexer::skipWhitespace() {
        while (index < input.size() && isspace(peek())) {
            advance();
        }
    }

    bool Lexer::isKeyword(const std::string& word) const {
        return keywords.find(word) != keywords.end();
    }

    Token Lexer::readWord() {
        int startLine = line, startCol = column;
        std::string word;
        while (index < input.size() && (isalnum(peek()) || peek() == '_')) {
            word += advance();
        }
        if (isKeyword(word)) {
            return Token(TokenType::KEYWORD, word, startLine, startCol);
        }
        else {
            return Token(TokenType::IDENTIFIER, word, startLine, startCol);
        }
    }

    Token Lexer::readNumber() {
        int startLine = line, startCol = column;
        std::string num;
        while (index < input.size() && isdigit(peek())) {
            num += advance();
        }
        return Token(TokenType::CONST_INT, num, startLine, startCol);
    }

    Token Lexer::readString() {
        int startLine = line, startCol = column;
        advance(); // 跳过开头的 '
        std::string str;
        while (index < input.size() && peek() != '\'') {
            str += advance();
        }
        if (peek() == '\'') {
            advance(); // 跳过结尾的 '
        }
        else {
            throw LexicalError("Unclosed string", startLine, startCol);
        }
        return Token(TokenType::CONST_STR, str, startLine, startCol);
    }

    Token Lexer::readOperator() {
        int startLine = line, startCol = column;
        std::string op;
        op += advance();
        if (peek() == '=') { // 处理 >=, <=, !=
            op += advance();
        }
        return Token(TokenType::OPERATOR, op, startLine, startCol);
    }

    Token Lexer::readDelimiter() {
        int startLine = line, startCol = column;
        std::string delim(1, advance());
        return Token(TokenType::DELIMITER, delim, startLine, startCol);
    }

} // namespace minisql