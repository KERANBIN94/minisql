//#pragma once
//
//#include <vector>
//#include <string>
//
//namespace minisql {
//
//// Forward declaration
//class Field;
//class TupleDesc;
//class RecordId;
//
///**
// * Tuple maintains information about the contents of a tuple.
// * Tuples have a specified schema specified by a TupleDesc object and contain
// * Field objects with the data for each field.
// */
//class Tuple {
//public:
//    /**
//     * Create a new tuple with the specified schema (type).
//     * @param td the schema of this tuple. It must be a valid TupleDesc instance.
//     */
//    Tuple(TupleDesc* td);
//
//    /**
//     * @return The TupleDesc representing the schema of this tuple.
//     */
//    TupleDesc* getTupleDesc() const;
//
//    /**
//     * @return The RecordId representing the location of this tuple on disk. May be null.
//     */
//    RecordId* getRecordId() const;
//
//    /**
//     * Set the RecordId information for this tuple.
//     * @param rid the new RecordId for this tuple.
//     */
//    void setRecordId(RecordId* rid);
//
//    /**
//     * Change the value of the ith field of this tuple.
//     * @param i index of the field to change. It must be a valid index.
//     * @param f new value for the field.
//     */
//    void setField(int i, Field* f);
//
//    /**
//     * @return the value of the ith field, or null if it has not been set.
//     * @param i index of the field to return. It must be a valid index.
//     */
//    Field* getField(int i) const;
//
//    /**
//     * @return a string representation of this tuple.
//     */
//    std::string toString() const;
//
//private:
//    TupleDesc* td;
//    RecordId* rid;
//    std::vector<Field*> fields;
//};
//
//} // namespace minisql