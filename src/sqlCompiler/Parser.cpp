#include "minisql/sqlCompiler/Parser.h"
#include <iostream>

namespace minisql {

    Parser::Parser(const std::vector<Token>& tokens) : tokens_(tokens) {}

    std::unique_ptr<ASTNode> Parser::parse() {
        try {
            return parseStatement();
        }
        catch (const SyntaxError& e) {
            throw;
        }
        catch (const std::exception& e) {
            throw SyntaxError("Unexpected parsing error", line_, column_);
        }
    }

    // 辅助方法实现
    const Token& Parser::peek() const {
        if (current_ >= tokens_.size()) return tokens_.back();  // 直接检查索引，不调用 isAtEnd()
        return tokens_[current_];
    }

    const Token& Parser::advance() {
        if (!isAtEnd()) {
            line_ = tokens_[current_].line;    // 直接访问，不调用 peek()
            column_ = tokens_[current_].column;
            current_++;
            return tokens_[current_ - 1];
        }
        return tokens_.back();  // 返回最后一个token（应该是END）
    }

    const Token& Parser::previous() const {
        return tokens_[current_ - 1];
    }

    bool Parser::isAtEnd() const {
        return current_ >= tokens_.size() || tokens_[current_].type == TokenType::END;
    }

    bool Parser::check(TokenType type) const {
        if (isAtEnd()) return false;
        return peek().type == type;
    }

    bool Parser::match(TokenType type) {
        if (check(type)) {
            advance();
            return true;
        }
        return false;
    }

    const Token& Parser::consume(TokenType type, const std::string& errorMessage) {
        if (check(type)) return advance();
        throw SyntaxError(errorMessage, peek());
    }

    void Parser::synchronize() {
        advance();
        while (!isAtEnd()) {
            if (previous().type == TokenType::DELIMITER &&
                previous().lexeme == ";") {
                return;
            }

            if (peek().type == TokenType::KEYWORD) {
                return;
            }

            advance();
        }
    }

    // 解析方法实现
    std::unique_ptr<ASTNode> Parser::parseStatement() {
        if (match(TokenType::KEYWORD)) {
            const std::string& keyword = previous().lexeme;

            if (keyword == "CREATE") {
                consume(TokenType::KEYWORD, "Expected TABLE after CREATE");
                if (previous().lexeme == "TABLE") {
                    return parseCreateTable();
                }
            }
            else if (keyword == "INSERT") {
                return parseInsert();
            }
            else if (keyword == "SELECT") {
                return parseSelect();
            }
            else if (keyword == "DELETE") {
                return parseDelete();
            }

            throw SyntaxError("Unknown statement type: " + keyword, previous());
        }

        throw SyntaxError("Expected statement keyword", peek());
    }

    std::unique_ptr<ASTNode> Parser::parseCreateTable() {
        auto tableNameToken = consume(TokenType::IDENTIFIER, "Expected table name");
        auto createTableNode = std::make_unique<CreateTableNode>(
            tableNameToken.lexeme, tableNameToken.line, tableNameToken.column);

        consume(TokenType::DELIMITER, "Expected '(' after table name");
        if (previous().lexeme != "(") {
            throw SyntaxError("Expected '(' after table name", previous());
        }

        // 解析列定义
        while (!check(TokenType::DELIMITER) || peek().lexeme != ")") {
            createTableNode->addChild(parseColumnDefinition());

            if (match(TokenType::DELIMITER) && previous().lexeme == ",") {
                continue;
            }
        }

        consume(TokenType::DELIMITER, "Expected ')' after column definitions");
        if (previous().lexeme != ")") {
            throw SyntaxError("Expected ')' after column definitions", previous());
        }

        if (match(TokenType::DELIMITER) && previous().lexeme == ";") {
            return createTableNode;
        }

        return createTableNode;
    }

    std::unique_ptr<ASTNode> Parser::parseInsert() {
        consume(TokenType::KEYWORD, "Expected INTO after INSERT");
        if (previous().lexeme != "INTO") {
            throw SyntaxError("Expected INTO after INSERT", previous());
        }

        auto tableNameToken = consume(TokenType::IDENTIFIER, "Expected table name");
        auto insertNode = std::make_unique<InsertNode>(
            tableNameToken.lexeme, tableNameToken.line, tableNameToken.column);

        if (match(TokenType::DELIMITER) && previous().lexeme == "(") {
            // 解析列列表
            auto columnList = parseColumnList();
            for (auto& column : columnList) {
                insertNode->addChild(std::move(column));
            }
        }

        consume(TokenType::KEYWORD, "Expected VALUES after INSERT");
        if (previous().lexeme != "VALUES") {
            throw SyntaxError("Expected VALUES after INSERT", previous());
        }

        consume(TokenType::DELIMITER, "Expected '(' after VALUES");
        if (previous().lexeme != "(") {
            throw SyntaxError("Expected '(' after VALUES", previous());
        }

        // 解析值列表
        auto valueList = parseValueList();
        for (auto& value : valueList) {
            insertNode->addChild(std::move(value));
        }

        if (match(TokenType::DELIMITER) && previous().lexeme == ";") {
            return insertNode;
        }

        return insertNode;
    }

    std::unique_ptr<ASTNode> Parser::parseSelect() {
        auto selectNode = std::make_unique<SelectNode>(peek().line, peek().column);

        // 解析选择列表（目前只支持*）
        if (match(TokenType::DELIMITER) && previous().lexeme == "*") {
            // 处理*选择所有列
        }
        else {
            // 可以扩展为解析具体的列列表
            throw SyntaxError("Only * is supported in SELECT for now", previous());
        }

        consume(TokenType::KEYWORD, "Expected FROM after SELECT");
        if (previous().lexeme != "FROM") {
            throw SyntaxError("Expected FROM after SELECT", previous());
        }

        auto tableNameToken = consume(TokenType::IDENTIFIER, "Expected table name");
        selectNode->addChild(std::make_unique<IdentifierNode>(
            tableNameToken.lexeme, tableNameToken.line, tableNameToken.column));

        if (check(TokenType::KEYWORD) && peek().lexeme == "WHERE") {
            selectNode->addChild(parseWhereClause());
        }

        if (match(TokenType::DELIMITER) && previous().lexeme == ";") {
            return selectNode;
        }

        return selectNode;
    }

    std::unique_ptr<ASTNode> Parser::parseDelete() {
        consume(TokenType::KEYWORD, "Expected FROM after DELETE");
        if (previous().lexeme != "FROM") {
            throw SyntaxError("Expected FROM after DELETE", previous());
        }

        auto tableNameToken = consume(TokenType::IDENTIFIER, "Expected table name");
        auto deleteNode = std::make_unique<DeleteNode>(
            tableNameToken.lexeme, tableNameToken.line, tableNameToken.column);

        if (check(TokenType::KEYWORD) && peek().lexeme == "WHERE") {
            deleteNode->addChild(parseWhereClause());
        }

        if (match(TokenType::DELIMITER) && previous().lexeme == ";") {
            return deleteNode;
        }

        return deleteNode;
    }

    // 其他解析方法的实现（简化版）
    std::unique_ptr<ASTNode> Parser::parseColumnDefinition() {
        auto nameToken = consume(TokenType::IDENTIFIER, "Expected column name");
        auto typeToken = consume(TokenType::IDENTIFIER, "Expected data type");

        return std::make_unique<ColumnDefNode>(
            nameToken.lexeme, typeToken.lexeme, nameToken.line, nameToken.column);
    }

    std::vector<std::unique_ptr<ASTNode>> Parser::parseColumnList() {
        std::vector<std::unique_ptr<ASTNode>> columns;

        do {
            auto columnToken = consume(TokenType::IDENTIFIER, "Expected column name");
            columns.push_back(std::make_unique<IdentifierNode>(
                columnToken.lexeme, columnToken.line, columnToken.column));
        } while (match(TokenType::DELIMITER) && previous().lexeme == ",");

        consume(TokenType::DELIMITER, "Expected ')' after column list");
        if (previous().lexeme != ")") {
            throw SyntaxError("Expected ')' after column list", previous());
        }

        return columns;
    }

    std::vector<std::unique_ptr<ASTNode>> Parser::parseValueList() {
        std::vector<std::unique_ptr<ASTNode>> values;

        do {
            if (check(TokenType::CONST_INT) || check(TokenType::CONST_STR)) {
                values.push_back(parseLiteral());
            }
            else {
                throw SyntaxError("Expected value in VALUES list", peek());
            }
        } while (match(TokenType::DELIMITER) && previous().lexeme == ",");

        consume(TokenType::DELIMITER, "Expected ')' after value list");
        if (previous().lexeme != ")") {
            throw SyntaxError("Expected ')' after value list", previous());
        }

        return values;
    }

    std::unique_ptr<ASTNode> Parser::parseWhereClause() {
        consume(TokenType::KEYWORD, "Expected WHERE");
        return parseExpression();
    }

    std::unique_ptr<ASTNode> Parser::parseExpression() {
        // 简化实现：只处理简单的比较表达式
        auto left = parseIdentifier();

        if (!match(TokenType::OPERATOR)) {
            throw SyntaxError("Expected operator in expression", peek());
        }
        auto op = previous();

        auto right = parseLiteral();

        auto exprNode = std::make_unique<ASTNode>(
            ASTNodeType::EXPRESSION, op.line, op.column);
        exprNode->addChild(std::move(left));
        exprNode->addChild(std::make_unique<IdentifierNode>(
            op.lexeme, op.line, op.column));
        exprNode->addChild(std::move(right));

        return exprNode;
    }

    std::unique_ptr<ASTNode> Parser::parseIdentifier() {
        auto token = consume(TokenType::IDENTIFIER, "Expected identifier");
        return std::make_unique<IdentifierNode>(
            token.lexeme, token.line, token.column);
    }

    std::unique_ptr<ASTNode> Parser::parseLiteral() {
        if (check(TokenType::CONST_INT) || check(TokenType::CONST_STR)) {
            auto token = advance();
            return std::make_unique<LiteralNode>(
                token.lexeme, token.type, token.line, token.column);
        }
        throw SyntaxError("Expected literal value", peek());
    }

} // namespace minisql