#include "resultasync.h"
#include "tdb.h"

ResultAsyncObject::ResultAsyncObject()
{

}


//===========================================================================


/*Специализация*/
template <>  //Пустые скобки означает специализацию
void ResultAsync<QList<Event> >::getData(const Result& result, ResultAsyncObject* res)
{
    if(res != this)
    {
        return;
    }
    //Тип для корректировки, класс<Тип для корректировки> метод класса
    QList<Event> events;
    for(int i=0;i<result.records.size();i++)
    {
        Event event;
        event.id = result.records[i].values[0].toInt();
        event.msg = result.records[i].values[1].toString();
        event.time = result.records[i].values[2].toDateTime();
        events.push_back(event);
    }
    emit ready(events);
    deleteLater();
}

/*Специализация*/
template <>  //Пустые скобки означает специализацию
void ResultAsync<Event>::getData(const Result& result, ResultAsyncObject* res)
{
    if(res != this)
    {
        return;
    }
    if(result.records.size()>0)
    {
        //Тип для корректировки, класс<Тип для корректировки> метод класса
        Event event;

        event.id = result.records[0].values[0].toInt();
        event.msg = result.records[0].values[1].toString();
        event.time = result.records[0].values[2].toDateTime();

        emit ready(event);
        deleteLater();
    }
}








/*Специализация*/
template <>  //Пустые скобки означает специализацию
void ResultAsync<QList<Event> >::getData(const Result& result)
{

    //Тип для корректировки, класс<Тип для корректировки> метод класса
    QList<Event> events;
    for(int i=0;i<result.records.size();i++)
    {
        Event event;
        event.id = result.records[i].values[0].toInt();
        event.msg = result.records[i].values[1].toString();
        event.time = result.records[i].values[2].toDateTime();
        events.push_back(event);
    }
    emit ready(events);
    deleteLater();
}

/*Специализация*/
template <>  //Пустые скобки означает специализацию
void ResultAsync<Event>::getData(const Result& result)
{
    if(result.records.size()>0)
    {
        //Тип для корректировки, класс<Тип для корректировки> метод класса
        Event event;

        event.id = result.records[0].values[0].toInt();
        event.msg = result.records[0].values[1].toString();
        event.time = result.records[0].values[2].toDateTime();

        emit ready(event);
        deleteLater();
    }
}
