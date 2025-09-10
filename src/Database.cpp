#include "minisql/Database.h"
#include "minisql/sqlCompiler/Lexer.h"
#include "minisql/sqlCompiler/Token.h"
#include "minisql/sqlCompiler/LexicalError.h"
#include "minisql/sqlCompiler/Parser.h"
#include "minisql/sqlCompiler/SyntaxError.h"
#include <iostream>
#include <string>

namespace minisql {

    void startDatabase() {
        // �������� - ���������ַ���SQL
        const std::string testSQL = "SELECT * FROM student WHERE age > 18;"; // @ �ǷǷ��ַ���������ȷ������>
        std::cout << "Testing SQL: " << testSQL << std::endl;

        try {
            // �ʷ�����
            Lexer lexer(testSQL);
            auto tokens = lexer.tokenize();

            std::cout << "Lexical analysis completed successfully!" << std::endl;
            std::cout << "Generated " << tokens.size() << " tokens." << std::endl;

            // �﷨����
            Parser parser(tokens);
            auto ast = parser.parse();

            std::cout << "Syntax analysis completed successfully!" << std::endl;

        }
        catch (const LexicalError& e) {
            std::cerr << "Lexical Error: " << e.what() << std::endl;
        }
        catch (const SyntaxError& e) {
            std::cerr << "Syntax Error: " << e.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Unexpected Error: " << e.what() << std::endl;
        }
    }

} // namespace minisql

int main() {
    minisql::startDatabase();
    return 0;
}


//#include "minisql/Database.h"
//
//namespace minisql
//{
//
//    Database *Database::instance = nullptr;
//
//    Database::Database()
//    {
//        catalog = new Catalog();
//        bufferPool = new BufferPool(100); // Default 100 pages
//    }
//
//    Database *Database::getInstance()
//    {
//        if (instance == nullptr)
//        {
//            instance = new Database();
//        }
//        return instance;
//    }
//
//    Catalog *Database::getCatalog()
//    {
//        return catalog;
//    }
//
//    BufferPool *Database::getBufferPool()
//    {
//        return bufferPool;
//    }
//
//} // namespace minisql
