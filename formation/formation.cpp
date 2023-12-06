#include "formation.h"
#include <QtWidgets>
#include <QTableWidget>
#include <QSqlError>
#include "gesfor.h"

formation::formation(int code,QString prenom,QString nom,QString type,int prix,QDate datef)
{
        this->code=code;
        this->prenom=prenom;
        this->nom=nom;
        this->type=type;
        this->prix=prix;
        this->datef=datef;


}
void formation::setcode(const int n){code=n;};
void formation::setprenom(const QString n){prenom=n;};
void formation::setnom(const QString n){nom=n;};
void formation::settype(const QString n){type=n;};
void formation::setprix(const int n){prix=n;};
void formation::setdatef(const QDate n){datef=n;};


bool formation::ajouter(){
    QSqlQuery query;
    QString res = QString::number(code);
    query.prepare("INSERT INTO FORMATION (codef, prenomf, nomf, typef, prixf, datef) VALUES (:code, :prenom, :nom, :type, :prix, :date)");
    query.bindValue(":code", res);
    query.bindValue(":prenom", prenom);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":prix", prix);
    query.bindValue(":date", datef);

    return query.exec();
}


bool formation::supprimer(QString code){
    QSqlQuery query;
    query.prepare("DELETE FROM FORMATION WHERE codef = :codef");
    query.bindValue(":codef", code);
    return query.exec();
}
QSqlQueryModel * formation::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from FORMATION");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date"));



    return model;

}
bool formation::modifier() {
    QSqlQuery query;
    QString res = QString::number(code);
    query.prepare("UPDATE FORMATION SET prenomf = :prenomf, nomf = :nomf, typef = :typef, prixf = :prixf ,datef = :datef "
                  "WHERE codef = :codef");
    query.bindValue(":codef", res);
    query.bindValue(":prenomf", prenom);
    query.bindValue(":nomf", nom);
    query.bindValue(":typef", type);
    query.bindValue(":prixf", prix);
    query.bindValue(":datef", datef);

    return query.exec();
}



bool formation::recherche(QString code ){
QSqlQuery query;
query.prepare("SELECT * FROM formation WHERE codef= :codef");
query.bindValue(":codef",code);

query.exec();
    if (query.next()) {
        return true;
    } else {
        return false;
    }
}


QSqlQueryModel* formation::afficherTriNom()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM formation ORDER BY LOWER(nomf) ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date"));

    return model;
}
QSqlQueryModel* formation::afficherTriNomD()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM formation ORDER BY LOWER(nomf) DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Preom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date"));

    return model;
}
QSqlQueryModel* formation::afficherTriprix()
{
    QSqlQueryModel* model = new QSqlQueryModel();
     model->setQuery("SELECT * FROM formation ORDER BY prixf DESC");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Preom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date"));

     return model;
 }
QSqlQueryModel* formation::afficherTriprixD()
{
    QSqlQueryModel* model = new QSqlQueryModel();
     model->setQuery("SELECT * FROM formation ORDER BY prixf ASC");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date"));


     return model;
 }

QSqlQueryModel* formation::afficherTriCode()
{
    QSqlQueryModel* model = new QSqlQueryModel();
     model->setQuery("SELECT * FROM formation ORDER BY codef ASC");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date"));

     return model;
 }
QSqlQueryModel* formation::afficherTriCodeD()
{
    QSqlQueryModel* model = new QSqlQueryModel();
     model->setQuery("SELECT * FROM formation ORDER BY codef DESC");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date"));

     return model;
 }



