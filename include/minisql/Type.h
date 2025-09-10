//#pragma once
//
//#include <string>
//
//namespace minisql {
//
//class Type {
//public:
//    enum TypeId {
//        INT_TYPE,
//        STRING_TYPE
//    };
//
//    TypeId typeId;
//
//    Type(TypeId id) : typeId(id) {}
//
//    virtual int getSize() const = 0;
//    virtual std::string toString() const = 0;
//};
//
//class IntType : public Type {
//public:
//    IntType() : Type(INT_TYPE) {}
//    int getSize() const override { return 4; }
//    std::string toString() const override { return "INT"; }
//};
//
//class StringType : public Type {
//private:
//    int len;
//public:
//    StringType(int len) : Type(STRING_TYPE), len(len) {}
//    int getSize() const override { return len; }
//    std::string toString() const override { return "STRING(" + std::to_string(len) + ")"; }
//};
//
//} // namespace minisql
