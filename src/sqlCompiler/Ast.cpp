#include "minisql/sqlCompiler/Ast.h"

namespace minisql {

    // ASTNode 实现
    ASTNode::ASTNode(ASTNodeType type, int line, int column)
        : type_(type), line_(line), column_(column) {}

    ASTNodeType ASTNode::getType() const { return type_; }
    int ASTNode::getLine() const { return line_; }
    int ASTNode::getColumn() const { return column_; }

    void ASTNode::addChild(std::unique_ptr<ASTNode> child) {
        children_.push_back(std::move(child));
    }

    const std::vector<std::unique_ptr<ASTNode>>& ASTNode::getChildren() const {
        return children_;
    }

    // CreateTableNode 实现
    CreateTableNode::CreateTableNode(const std::string& tableName, int line, int column)
        : ASTNode(ASTNodeType::CREATE_TABLE, line, column), tableName_(tableName) {}

    const std::string& CreateTableNode::getTableName() const { return tableName_; }

    // InsertNode 实现
    InsertNode::InsertNode(const std::string& tableName, int line, int column)
        : ASTNode(ASTNodeType::INSERT, line, column), tableName_(tableName) {}

    const std::string& InsertNode::getTableName() const { return tableName_; }

    // SelectNode 实现
    SelectNode::SelectNode(int line, int column)
        : ASTNode(ASTNodeType::SELECT, line, column) {}

    // DeleteNode 实现
    DeleteNode::DeleteNode(const std::string& tableName, int line, int column)
        : ASTNode(ASTNodeType::DELETE, line, column), tableName_(tableName) {}

    const std::string& DeleteNode::getTableName() const { return tableName_; }

    // ColumnDefNode 实现
    ColumnDefNode::ColumnDefNode(const std::string& columnName, const std::string& dataType,
        int line, int column)
        : ASTNode(ASTNodeType::COLUMN_DEF, line, column),
        columnName_(columnName), dataType_(dataType) {}

    const std::string& ColumnDefNode::getColumnName() const { return columnName_; }
    const std::string& ColumnDefNode::getDataType() const { return dataType_; }

    // IdentifierNode 实现
    IdentifierNode::IdentifierNode(const std::string& name, int line, int column)
        : ASTNode(ASTNodeType::IDENTIFIER, line, column), name_(name) {}

    const std::string& IdentifierNode::getName() const { return name_; }

    // LiteralNode 实现
    LiteralNode::LiteralNode(const std::string& value, TokenType type, int line, int column)
        : ASTNode(ASTNodeType::LITERAL, line, column), value_(value), type_(type) {}

    const std::string& LiteralNode::getValue() const { return value_; }
    TokenType LiteralNode::getLiteralType() const { return type_; }

} // namespace minisql