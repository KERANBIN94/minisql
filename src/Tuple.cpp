#include "minisql/Tuple.h"
#include "minisql/Field.h"
#include "minisql/TupleDesc.h"

namespace minisql
{

    Tuple::Tuple(TupleDesc *td) : td(td), rid(nullptr)
    {
        fields.resize(td->numFields());
    }

    TupleDesc *Tuple::getTupleDesc() const
    {
        return td;
    }

    RecordId *Tuple::getRecordId() const
    {
        return rid;
    }

    void Tuple::setRecordId(RecordId *rid)
    {
        this->rid = rid;
    }

    void Tuple::setField(int i, Field *f)
    {
        if (i < 0 || i >= fields.size())
        {
            throw std::out_of_range("Index out of range.");
        }
        fields[i] = f;
    }

    Field *Tuple::getField(int i) const
    {
        if (i < 0 || i >= fields.size())
        {
            throw std::out_of_range("Index out of range.");
        }
        return fields[i];
    }

    std::string Tuple::toString() const
    {
        std::string s;
        for (size_t i = 0; i < fields.size(); ++i)
        {
            if (fields[i] != nullptr)
            {
                s += fields[i]->toString();
            }
            if (i < fields.size() - 1)
            {
                s += "\t";
            }
        }
        return s;
    }

} // namespace minisql
