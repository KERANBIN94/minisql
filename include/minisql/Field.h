//#pragma once
//
//#include "minisql/Type.h"
//#include <string>
//
//namespace minisql {
//
///**
// * Interface for values of fields in tuples.
// */
//class Field {
//public:
//    /**
//     * @return the type of this field.
//     */
//    virtual Type* getType() const = 0;
//
//    /**
//     * @return a string representation of this field.
//     */
//    virtual std::string toString() const = 0;
//};
//
//class IntField : public Field {
//private:
//    int value;
//public:
//    IntField(int v);
//    int getValue() const;
//    Type* getType() const override;
//    std::string toString() const override;
//};
//
//class StringField : public Field {
//private:
//    std::string value;
//public:
//    StringField(const std::string& v);
//    const std::string& getValue() const;
//    Type* getType() const override;
//    std::string toString() const override;
//};
//
//} // namespace minisql