#ifndef RESULTASYNC_H
#define RESULTASYNC_H

#include <QObject>
#include <QDebug>
#include "structs.h"

/**
 * @details Класс хранения результата выполнения запроса.
 * Данный класс является наследником QObject и необходим для
 * реализации сигналов слотов в главном классе ResultAsync,
 * являющимся наследником данного класса.
 */
class ResultAsyncObject : public QObject
{
    Q_OBJECT
public:
    ResultAsyncObject();

signals:
    void ready();
    void ready(const QList<Event>& events);
    void ready(const Event& event);
public slots:
    virtual void getData(const Result&,ResultAsyncObject*){}
    virtual void getData(const Result&){}
};

/**
 * @details Шаблонный класс хранения результата выполнения запроса.
 * Является наследником ResultAsyncObject представляющий сигнально-слотовые
 * интерфейсы для передачи результата и реализующий виртуальный метод
 * получения данных getData для всех видов передаваемого черз сигналы слоты
 * контента. Предназначен для гибкого хранения и передачи результата
 * выполнения запроса в вызвавший поток.
 */
template <class T>
class ResultAsync : public ResultAsyncObject
{
public:
    ResultAsync() : ResultAsyncObject(){}

    int id() const {return m_id;}
    void setID(int id) {m_id = id;}
private:
    int m_id;
    void getData(const Result&,ResultAsyncObject*){}
    void getData(const Result&){}
};


#endif // RESULTASYNC_H
