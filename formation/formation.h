//DONE
#ifndef FORMATION_H
#define FORMATION_H
#include<QString>
#include<QDate>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QTableWidget>


class formation
{
public:

    void setcode(const int n);
    void setnom(const QString n);
    void setprenom(const QString n);
    void settype(const QString n);
    void setprix(const int n);
    void setdatef(const QDate n);

     int getcode();
     QString getnom();
     QString getprenom();
     QString gettype();
     int getprix();
     QDate getdatef();


     formation(){}
     formation(int,QString,QString,QString,int,QDate);
      bool ajouter();
      QSqlQueryModel * afficher();
      bool supprimer(QString);
      bool modifier();
      bool recherche(QString code);


      QSqlQueryModel * afficherTriNom();
      QSqlQueryModel * afficherTriprix();
      QSqlQueryModel * afficherTriprixD();
      QSqlQueryModel * afficherTriNomD();
      QSqlQueryModel * afficherTriCode();
      QSqlQueryModel * afficherTriCodeD();
private:
int  code;
QString prenom;
QString nom;
QString type;
int prix;
QDate datef;
};



#endif // FORMATION_H
