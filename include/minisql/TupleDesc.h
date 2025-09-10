//#pragma once
//
//#include <string>
//#include <vector>
//#include <stdexcept>
//
//namespace minisql {
//
//// Forward declaration
//class Type;
//
///**
// * TDItem represents a single field in a tuple description.
// * It has a type and a name.
// */
//class TDItem {
//public:
//    /**
//     * The type of the field.
//     */
//    Type* fieldType;
//
//    /**
//     * The name of the field.
//     */
//    std::string fieldName;
//
//    TDItem(Type* type, const std::string& name)
//        : fieldType(type), fieldName(name) {}
//};
//
///**
// * TupleDesc describes the schema of a tuple.
// */
//class TupleDesc {
//public:
//    /**
//     * Create a new TupleDesc with typeAr and fieldAr arrays.
//     * @param typeAr array specifying the number of bytes given to each field.
//     * @param fieldAr array specifying the names of the fields.
//     */
//    TupleDesc(const std::vector<Type*>& typeAr, const std::vector<std::string>& fieldAr);
//
//    /**
//     * @return the number of fields in this TupleDesc.
//     */
//    int numFields() const;
//
//    /**
//     * Gets the (possibly null) field name of the ith field of this TupleDesc.
//     * @param i index of the field name to return. It must be a valid index.
//     * @return the name of the ith field.
//     * @throws std::out_of_range if i is not a valid index.
//     */
//    std::string getFieldName(int i) const;
//
//    /**
//     * Gets the type of the ith field of this TupleDesc.
//     * @param i index of the field type to return. It must be a valid index.
//     * @return the type of the ith field.
//     * @throws std::out_of_range if i is not a valid index.
//     */
//    Type* getFieldType(int i) const;
//
//    /**
//     * Find the index of the field with a given name.
//     * @param name name of the field to search for.
//     * @return the index of the field if found.
//     * @throws std::invalid_argument if no such field exists.
//     */
//    int fieldNameToIndex(const std::string& name) const;
//
//    /**
//     * @return The size (in bytes) of tuples corresponding to this TupleDesc.
//     * Note that tuples from a given TupleDesc are of a fixed size.
//     */
//    int getSize() const;
//
//    /**
//     * Compares the specified object with this TupleDesc for equality.
//     * Two TupleDescs are considered equal if they have the same number of items
//     * and if the i-th type in this TupleDesc is equal to the i-th type in o
//     * for every i.
//     * @param other The object to compare to.
//     * @return true if the objects are equal, false otherwise.
//     */
//    bool operator==(const TupleDesc& other) const;
//
//    /**
//     * @return a string describing this TupleDesc.
//     */
//    std::string toString() const;
//
//private:
//    std::vector<TDItem> items;
//};
//
//} // namespace minisql
