/* ---------------------------------------------------------------------------
 * Copyright © 2017 The trifecta Company Ltd.
 * Contact: http://www.trifecta.ru/licensing/
 * Author: BM
 *
 * This file is part of the Trifecta.
 *
 * Trifecta is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Trifecta is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 * ---------------------------------------------------------------------------
 */

#ifndef TDB_H
#define TDB_H

#include <QObject>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql>
#include "tdb_global.h"
#include "structs.h"
#include <QVariant>
#include "sqlworker.h"
#include "resultasync.h"

/**
 * @brief Класс представляющий интерфейс к рабочему потоку
 * исполнения запросов. Позволяет выполнять запросы как
 * асинхронно, так и синхронно. Имеет готовые методы для
 * запросов.
 */
class TDBSHARED_EXPORT TDB : public QObject
{
    Q_OBJECT
public:
    // Конструкторы
    TDB(QObject* parent = 0);
    ~TDB();

    // Методы
    QList<Event> lastMessage(int limit = 1);
    ResultAsync<QList<Event> >* lastMessageAsync(int limit = 1);
    QList<Event> allMessages();
    Event message(int id);
    ResultAsync<Event>* messageAsync(int id);
    void setConnectionName(const QString &connectionName,
                           const QString &dbName,
                           const QString &hostName,
                           const QString &userName,
                           const QString &password,
                           int port
                           );
    void subscribeToNotificationEvents();
signals:
    void eventUpdated(int);
private:
    SqlWorker sqlWorker;
private slots:
    void updateEvent(int);
};

#endif // TDB_H
