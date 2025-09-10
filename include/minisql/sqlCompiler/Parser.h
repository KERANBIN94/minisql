#ifndef MINISQL_PARSER_H
#define MINISQL_PARSER_H

#include <vector>
#include <memory>
#include "minisql/sqlCompiler/Token.h"
#include "minisql/sqlCompiler/Ast.h"
#include "minisql/sqlCompiler/SyntaxError.h"

namespace minisql {

    class Parser {
    public:
        Parser(const std::vector<Token>& tokens);
        std::unique_ptr<ASTNode> parse();

    private:
        std::vector<Token> tokens_;
        size_t current_ = 0;
        int line_ = 1;
        int column_ = 1;

        // 辅助方法
        const Token& peek() const;
        const Token& advance();
        const Token& previous() const;
        bool isAtEnd() const;
        bool check(TokenType type) const;
        bool match(TokenType type);
        const Token& consume(TokenType type, const std::string& errorMessage);
        void synchronize();

        // 解析方法（递归下降）
        std::unique_ptr<ASTNode> parseStatement();
        std::unique_ptr<ASTNode> parseCreateTable();
        std::unique_ptr<ASTNode> parseInsert();
        std::unique_ptr<ASTNode> parseSelect();
        std::unique_ptr<ASTNode> parseDelete();

        std::unique_ptr<ASTNode> parseColumnDefinition();
        std::vector<std::unique_ptr<ASTNode>> parseColumnList();
        std::vector<std::unique_ptr<ASTNode>> parseValueList();
        std::unique_ptr<ASTNode> parseWhereClause();
        std::unique_ptr<ASTNode> parseExpression();

        std::unique_ptr<ASTNode> parseIdentifier();
        std::unique_ptr<ASTNode> parseLiteral();
    };

} // namespace minisql

#endif