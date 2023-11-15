#include "mission.h"
#include <QtSql/QSqlQuery>
#include<QString>
#include<QObject>
#include <iostream>
using namespace std;
mission::mission(){

    code_mission=0;
    date_mission=" ";
    statut_mission=" ";

}
mission::mission(int code_mission,QString date_mission,QString statut_mission){

    this->code_mission=code_mission;
    this->date_mission=date_mission;
    this->statut_mission=statut_mission;
}
bool mission::ajouter(){
    QSqlQuery query;
    QString res =QString::number(code_mission);

query.prepare("insert into mission (code_mission , date_mission, statut_mission)" "values(:code_mission , :date_mission, :statut_mission)");
query.bindValue(":code_mission",code_mission);
query.bindValue(":date_mission",date_mission);
query.bindValue(":statut_mission",statut_mission);

return query.exec();

}

bool mission::modifier(int code_mission)
 {
 QSqlQuery query;
 query.prepare("UPDATE mission SET CODE_MISSION=:CODE_MISSION , DATE_MISSION=:DATE_MISSION , STATUT_MISSION= :STATUT_MISSION");
 query.bindValue(":code_mission",code_mission);
 query.bindValue(":date_mission",date_mission );
 query.bindValue(":statut_mission",statut_mission);
 query.exec();
return query.exec();
 }

bool mission::supprimer(int code_mission){
QSqlQuery query;
query.prepare("Delete from MISSION where code_mission=:code_mission");
query.bindValue(":code_mission",code_mission);
return query.exec();
}
QSqlQueryModel * mission::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from MISSION");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("code_mission"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("date_mission"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("statut_mission"));
return model;
}
QSqlQueryModel * mission::trier(int test)
{
    QSqlQueryModel *model=new QSqlQueryModel() ;
    QSqlQuery query ;

    if(test==1)
    {
        query.prepare("SELECT *  FROM MISSION ORDER BY CODE_MISSION ASC ") ;
    }
    else if(test==2)
    {
        query.prepare("SELECT *  FROM MISSION ORDER BY DATE_MISSION ASC ") ;
    }
    else if(test==3)
    {
        query.prepare("SELECT *  FROM MISSION ORDER BY STATUT_MISSION ASC ") ;
    }

    if (query.exec()&&query.next())
    {
        model->setQuery(query) ;
    }
    return model;

}
