#include "structs.h"

Record::Record()
{

}

void Record::addValues(const QVariant &value)
{
    values.append(value);
}

Result::Result()
{

}

void Result::addRecord(const Record &record)
{
    records.append(record);
}
