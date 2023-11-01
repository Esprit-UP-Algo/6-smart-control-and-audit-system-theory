#ifndef MISSION_H
#define MISSION_H
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QString>
#include <QDate>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

#include <QVariant>


class Mission
{
public:

    Mission();
    Mission(QString, QString, QString);

    void setCode(QString code_mission)
    {
        this->code_mission = code_mission;
    }
    void setdate(QString date_mission)
    {
        this->date_mission = date_mission;
    }
    void setTel(QString statut_mission)
    {
        this->statut_mission = statut_mission;
    }

    QString getCode()
    {
        return  this->code_mission;
    }
    QString getDate()
    {
        return  this->date_mission;
    }
    QString getStatut()
    {
        return  this->statut_mission;
    }

    bool ajouterMission();
    bool supprimerMission(int );
    bool modifierMission();
    QSqlQueryModel * afficherMission();
private :
    QString code_mission ;
    QString date_mission ;
    QString statut_mission ;
};



#endif // MISSION_H
