#ifndef SQLWORKER_H
#define SQLWORKER_H

#include <QThread>
#include <QVector>
#include "structs.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql>
#include <QMutex>
#include "resultasync.h"

class Stack
{
public:
    Stack(const QString& query = QString::null, ResultAsyncObject* res = 0) :
        m_query(query),
        m_result(res)
        {}
    QString m_query;
    ResultAsyncObject* m_result;
};

/**
 * @details Класс исполнения асинхронных/синхронных запросов.
 * Предназначен для выполнения запросов к БД в отличном от
 * вызываемого объекта потоке.
 */
class SqlWorker : public QThread
{
    Q_OBJECT
public:
    explicit SqlWorker(QObject *parent = 0);
    ~SqlWorker();
    bool stop() const;
    void setStop(bool stop);

    int addQuery(const QString& query, ResultAsyncObject* res = 0);
    void setConnectionName(const QString &connectionName,
                           const QString &dbName,
                           const QString &hostName,
                           const QString &userName,
                           const QString &password,
                           int port
                           );
    Result execQuery(const QString& query);
    void subscribeToNotificationEvents();
private:
    void run() override;

    bool m_stop;
    QSqlDatabase m_db;
    QVector<Stack> m_queries;
signals:
    void ready(const Result& result, ResultAsyncObject* res);
    void eventUpdated(int id);
public slots:
    void slotNotification(const QString &notif,QSqlDriver::NotificationSource source,
                           const QVariant &payload);
};

#endif // SQLWORKER_H
