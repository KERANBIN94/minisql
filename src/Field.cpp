//#include "minisql/Field.h"
//
//namespace minisql
//{
//
//    // IntField
//    IntField::IntField(int v) : value(v) {}
//
//    int IntField::getValue() const
//    {
//        return value;
//    }
//
//    Type *IntField::getType() const
//    {
//        return new IntType();
//    }
//
//    std::string IntField::toString() const
//    {
//        return std::to_string(value);
//    }
//
//    // StringField
//    StringField::StringField(const std::string &v) : value(v) {}
//
//    const std::string &StringField::getValue() const
//    {
//        return value;
//    }
//
//    Type *StringField::getType() const
//    {
//        return new StringType(value.length());
//    }
//
//    std::string StringField::toString() const
//    {
//        return value;
//    }
//
//} // namespace minisql
