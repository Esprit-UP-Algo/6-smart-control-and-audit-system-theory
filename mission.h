#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QtSql/QSqlQueryModel>
class mission
{
public:
    mission();
    mission(int,QString,QString);

    int GetCode_mission() { return code_mission; }
    void SetCode_mission(int val) { code_mission = val; }
    QString GetDate_mission() { return date_mission; }
    void SetDate_mission(QString val) { date_mission = val; }

    QString GetStatut_mission() { return statut_mission; }
    void SetStatut_mission(QString val) { statut_mission = val; }

    int code_mission;
    QString date_mission;
    QString statut_mission;

    //crud
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int );

 QSqlQueryModel * trier(int test);
private:


};


#endif // MISSION_H
