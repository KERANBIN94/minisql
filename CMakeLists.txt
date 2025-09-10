# CMakeList.txt: minisql 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("minisql")

# Add include directory
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 将源代码添加到此项目的可执行文件。
add_executable (minisql ${SOURCES} "include/minisql/sqlCompiler/LexicalError.h" "src/sqlCompiler/LexicalError.cpp" "include/minisql/sqlCompiler/Lexer.h" "src/sqlCompiler/Lexer.cpp" "include/minisql/sqlCompiler/Token.h" "include/minisql/sqlCompiler/SyntaxError.h" "src/sqlCompiler/SyntaxError.cpp" "include/minisql/sqlCompiler/Ast.h" "src/sqlCompiler/Ast.cpp" "include/minisql/sqlCompiler/Parser.h" "src/sqlCompiler/Parser.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET minisql PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。

add_executable (minisql_test tests/test.cpp ${SOURCES} "include/minisql/sqlCompiler/LexicalError.h" "src/sqlCompiler/LexicalError.cpp" "include/minisql/sqlCompiler/Lexer.h" "src/sqlCompiler/Lexer.cpp" "include/minisql/sqlCompiler/Token.h" "include/minisql/sqlCompiler/SyntaxError.h" "src/sqlCompiler/SyntaxError.cpp" "include/minisql/sqlCompiler/Ast.h" "src/sqlCompiler/Ast.cpp" "include/minisql/sqlCompiler/Parser.h" "src/sqlCompiler/Parser.cpp")
set_property(TARGET minisql_test PROPERTY CXX_STANDARD 20)