#include "mission.h"

Mission::Mission()
{

}
Mission::Mission(QString code_mission, QString date_mission , QString statut_mission)
{
    this->code_mission = code_mission ;
    this->date_mission= date_mission ;
    this->statut_mission = statut_mission ;

}

bool Mission::ajouterMission()
{//to do
    QSqlQuery query ;
    query.prepare("insert into auditeur(code_mission,date_mission,statut_mission)""values(:code,date,mission)");

    query.bindValue(":code",this->code_mission);
    query.bindValue(":date",this->date_mission);
    query.bindValue(":statut",this->statut_mission);


    return query.exec();
}

bool Mission::supprimerMission(int code_mission)
{//to do
    QSqlQuery query ;
    query.prepare("delete from mission where code = :code ");
    query.bindValue(":code",code_mission);

  return query.exec();

}

QSqlQueryModel * Mission::afficherMission()
{//to do
QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("select * from auditeur");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("Code"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("statut"));


   return model;
}
bool Mission::modifierMission()
{
    QSqlQuery query ;
    query.prepare("Update auditeur set code=code_mission,date=:date_mission,statut=:statut_mission");
    query.bindValue(":code",code_mission);
query.bindValue(":date",date_mission);
query.bindValue(":statut",statut_mission);
    return query.exec();
}
