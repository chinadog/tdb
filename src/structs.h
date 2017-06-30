#ifndef STRUCTS_H
#define STRUCTS_H

#include <QString>
#include <QDateTime>
#include <QVariant>
#include <QVector>

/**
 * @details Структура описывающая событие (лог) системы
 */
struct Event
{
    qint64 id;
    QString msg;
    QDateTime time;
};

/**
 * @brief Класс хранения записи результата запроса.
 */
class Record
{
public:
    Record();
    QVector<QVariant> values;
    void addValues(const QVariant& value);
};

/**
 * @brief Класс хранения вектора записей результата
 * запроса.
 */
class Result
{
public:
    Result();
    QVector<Record> records;
    void addRecord(const Record& record);
};

#endif // STRUCTS_H
