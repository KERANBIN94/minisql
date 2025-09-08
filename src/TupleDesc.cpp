#include "minisql/TupleDesc.h"
#include "minisql/Type.h"

namespace minisql
{

    TupleDesc::TupleDesc(const std::vector<Type *> &typeAr, const std::vector<std::string> &fieldAr)
    {
        if (typeAr.size() != fieldAr.size())
        {
            throw std::invalid_argument("typeAr and fieldAr must have the same size.");
        }
        for (size_t i = 0; i < typeAr.size(); ++i)
        {
            items.emplace_back(typeAr[i], fieldAr[i]);
        }
    }

    int TupleDesc::numFields() const
    {
        return items.size();
    }

    std::string TupleDesc::getFieldName(int i) const
    {
        if (i < 0 || i >= items.size())
        {
            throw std::out_of_range("Index out of range.");
        }
        return items[i].fieldName;
    }

    Type *TupleDesc::getFieldType(int i) const
    {
        if (i < 0 || i >= items.size())
        {
            throw std::out_of_range("Index out of range.");
        }
        return items[i].fieldType;
    }

    int TupleDesc::fieldNameToIndex(const std::string &name) const
    {
        for (size_t i = 0; i < items.size(); ++i)
        {
            if (items[i].fieldName == name)
            {
                return i;
            }
        }
        throw std::invalid_argument("Field name not found.");
    }

    int TupleDesc::getSize() const
    {
        int size = 0;
        for (const auto &item : items)
        {
            size += item.fieldType->getSize();
        }
        return size;
    }

    bool TupleDesc::operator==(const TupleDesc &other) const
    {
        if (items.size() != other.items.size())
        {
            return false;
        }
        for (size_t i = 0; i < items.size(); ++i)
        {
            if (items[i].fieldType->typeId != other.items[i].fieldType->typeId)
            {
                return false;
            }
        }
        return true;
    }

    std::string TupleDesc::toString() const
    {
        std::string s;
        for (size_t i = 0; i < items.size(); ++i)
        {
            s += items[i].fieldType->toString() + "(" + items[i].fieldName + ")";
            if (i < items.size() - 1)
            {
                s += ", ";
            }
        }
        return s;
    }

} // namespace minisql
