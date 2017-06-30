#include "sqlworker.h"
#include <TLogger/TLogger>

// TODO: SqlWorker должен возвращать уникальный id

SqlWorker::SqlWorker(QObject *parent) :
    QThread(parent),
    m_stop(false)
{

}

SqlWorker::~SqlWorker()
{
    if(m_db.isOpen())
    {
        m_db.close();
        QSqlDatabase::database("Connect2").close();
        TINFO() << "Database closed";
    }
}

void SqlWorker::run()
{
//    while(m_stop == false)
//    {
//        msleep(10);
        while(m_queries.size() > 0)
        {
            Result result = execQuery(m_queries.first().m_query);
//            emit ready(result, m_queries.first().m_result);
            QMetaObject::invokeMethod(m_queries.first().m_result,"getData",
                                      Q_ARG(Result, result));
            m_queries.removeFirst();
        }
//    }
}

void SqlWorker::slotNotification(const QString &/*notif*/, QSqlDriver::NotificationSource /*source*/,
                                 const QVariant &payload)
{
    int id = payload.toString().remove(0,2).toInt();
    emit eventUpdated(id);

}

Result SqlWorker::execQuery(const QString &queryString)
{
    Result result;
    QSqlQuery query(m_db);

    if (!query.exec(queryString))
    {
        qWarning() << "SQL error:" << query.lastError().text();
    }

    while(query.next())
    {
        Record record;
        for(int i=0;i<query.record().count();i++)
        {
            record.addValues(query.value(i));
        }
        result.addRecord( record );
    }
    return result;
}

void SqlWorker::subscribeToNotificationEvents()
{
    QSqlDatabase db = QSqlDatabase::cloneDatabase(m_db, "Connect2");
    db.open();
    if(db.isOpen())
    {
        QSqlDatabase::database("Connect2").driver()->subscribeToNotification("event");
    }
    TINFO() << "Subscribe to events";
    // ждем сигнала обновления данных
    connect(QSqlDatabase::database("Connect2").driver(),
           SIGNAL(notification(const QString&,QSqlDriver::NotificationSource,const QVariant & )), this,
           SLOT(slotNotification(const QString&,QSqlDriver::NotificationSource,const QVariant &)));
}

bool SqlWorker::stop() const
{
    return m_stop;
}

void SqlWorker::setStop(bool stop)
{
    m_stop = stop;
}

int SqlWorker::addQuery(const QString &query, ResultAsyncObject* res)
{
    m_queries.append(Stack(query, res));
    if(isRunning() == false)
    {
        start();
    }
    return 1;
}

void SqlWorker::setConnectionName(const QString &/*connectionName*/,
                                  const QString &dbName, const QString &hostName,
                                  const QString &userName, const QString &password, int port)
{
    if( !m_db.isValid() )
    {
        m_db = QSqlDatabase::addDatabase("QPSQL");

        m_db.setDatabaseName(dbName);
        m_db.setHostName(hostName);
        m_db.setUserName(userName);
        m_db.setPassword(password);
        m_db.setPort(port);


        if (!m_db.open())
        {
            qDebug() << "Database error: " << m_db.lastError();
        }
        else
        {
            qDebug() << "Database opened";
        }
    }
}
