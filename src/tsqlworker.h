#ifndef TSQLWORKER_H
#define TSQLWORKER_H

#include <QObject>

class TSQLWorker : public QObject
{
    Q_OBJECT
public:
    explicit TSQLWorker(QObject *parent = 0);

signals:

public slots:
};

#endif // TSQLWORKER_H