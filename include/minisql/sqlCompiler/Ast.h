#ifndef MINISQL_AST_H
#define MINISQL_AST_H

#include <vector>
#include <string>
#include <memory>
#include "minisql/sqlCompiler/Token.h"

namespace minisql {

    // AST节点类型枚举
    enum class ASTNodeType {
        PROGRAM,
        CREATE_TABLE,
        INSERT,
        SELECT,
        DELETE,
        COLUMN_DEF,
        COLUMN_LIST,
        VALUE_LIST,
        WHERE_CLAUSE,
        EXPRESSION,
        IDENTIFIER,
        LITERAL,
        OPERATOR
    };

    // AST节点基类
    class ASTNode {
    public:
        ASTNode(ASTNodeType type, int line = 0, int column = 0);
        virtual ~ASTNode() = default;

        ASTNodeType getType() const;
        int getLine() const;
        int getColumn() const;
        void addChild(std::unique_ptr<ASTNode> child);
        const std::vector<std::unique_ptr<ASTNode>>& getChildren() const;

    private:
        ASTNodeType type_;
        int line_;
        int column_;
        std::vector<std::unique_ptr<ASTNode>> children_;
    };

    // 具体AST节点类
    class CreateTableNode : public ASTNode {
    public:
        CreateTableNode(const std::string& tableName, int line, int column);
        const std::string& getTableName() const;

    private:
        std::string tableName_;
    };

    class InsertNode : public ASTNode {
    public:
        InsertNode(const std::string& tableName, int line, int column);
        const std::string& getTableName() const;

    private:
        std::string tableName_;
    };

    class SelectNode : public ASTNode {
    public:
        SelectNode(int line, int column);
    };

    class DeleteNode : public ASTNode {
    public:
        DeleteNode(const std::string& tableName, int line, int column);
        const std::string& getTableName() const;

    private:
        std::string tableName_;
    };

    class ColumnDefNode : public ASTNode {
    public:
        ColumnDefNode(const std::string& columnName, const std::string& dataType,
            int line, int column);
        const std::string& getColumnName() const;
        const std::string& getDataType() const;

    private:
        std::string columnName_;
        std::string dataType_;
    };

    class IdentifierNode : public ASTNode {
    public:
        IdentifierNode(const std::string& name, int line, int column);
        const std::string& getName() const;

    private:
        std::string name_;
    };

    class LiteralNode : public ASTNode {
    public:
        LiteralNode(const std::string& value, TokenType type, int line, int column);
        const std::string& getValue() const;
        TokenType getLiteralType() const;

    private:
        std::string value_;
        TokenType type_;
    };

} // namespace minisql

#endif