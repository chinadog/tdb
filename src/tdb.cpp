#include "tdb.h"
#include <TLogger/TLogger>
#include "resultasync.h"

TDB::TDB(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<Result>("Result");
//    sqlWorker.start();
}

TDB::~TDB()
{
    qDebug() << "TDB destructor";
    sqlWorker.setStop(true);
    sqlWorker.wait(100);
}

QList<Event> TDB::lastMessage(int limit)
{
    Result result = sqlWorker.execQuery("SELECT id, message, receivedat FROM systemevents "
                                        "ORDER BY id ASC LIMIT "+QString::number(limit));
    QList<Event> events;
    for(int i=0;i<result.records.size();i++)
    {
        Event event;
        event.id = result.records[i].values[0].toInt();
        event.msg = result.records[i].values[1].toString();
        event.time = result.records[i].values[2].toDateTime();
        events << event;
    }
    return events;
}

ResultAsync<QList<Event> >* TDB::lastMessageAsync(int limit)
{
    ResultAsync<QList<Event> >* res = new ResultAsync<QList<Event> >;
    sqlWorker.addQuery("SELECT id, message, receivedat FROM systemevents "
                       "ORDER BY id DESC LIMIT "+QString::number(limit), res);
//    connect(&sqlWorker,SIGNAL(ready(Result,ResultAsyncObject*)),
//            res,SLOT(getData(Result,ResultAsyncObject*)));
    return res;
}

QList<Event> TDB::allMessages()
{
    QList<Event> result;
    return result;
}

Event TDB::message(int id)
{
    QString query = QString("SELECT id, message, receivedat FROM systemevents "
                            "WHERE id = %1 LIMIT 1").arg(id);
    Result result = sqlWorker.execQuery(query);
    Event event;
    if(result.records.size()>0)
    {
        event.id = result.records[0].values[0].toInt();
        event.msg = result.records[0].values[1].toString();
        event.time = result.records[0].values[2].toDateTime();
    }
    return event;
}

ResultAsync<Event> *TDB::messageAsync(int id)
{
    ResultAsync<Event>* res = new ResultAsync<Event>;
    QString query = QString("SELECT id, message, receivedat FROM systemevents "
                            "WHERE id = %1 LIMIT 1").arg(id);
    sqlWorker.addQuery(query, res);
//    connect(&sqlWorker,SIGNAL(ready(Result,ResultAsyncObject*)),
//            res,SLOT(getData(Result,ResultAsyncObject*)));
    return res;
}


void TDB::setConnectionName(const QString &connectionName,
                            const QString &dbName, const QString &hostName,
                            const QString &userName, const QString &password, int port)
{
    sqlWorker.setConnectionName(connectionName, dbName, hostName, userName,
                                password, port);

}

void TDB::subscribeToNotificationEvents()
{
    // подписываемся на уведомления event_request и dbci_config_request
    sqlWorker.subscribeToNotificationEvents();
    connect(&sqlWorker,SIGNAL(eventUpdated(int)),this,SLOT(updateEvent(int)));
}

void TDB::updateEvent(int id)
{
    qDebug() << "UPDATE EVENT = " << id;
    emit eventUpdated(id);
}

