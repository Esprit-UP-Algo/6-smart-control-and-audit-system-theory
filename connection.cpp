#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("taha");//inserer nom de l'utilisateur
db.setPassword("taha");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void Connection::closeConnection(){db.close();}
