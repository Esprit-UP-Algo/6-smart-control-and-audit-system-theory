
#ifndef CONNECTION_H
#define CONNECTION_H


#include <QtSql/QSqlQuery>

#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
class Connection
{
public:
    Connection();
    bool createconnect();
};

#endif // CONNECTION_H
