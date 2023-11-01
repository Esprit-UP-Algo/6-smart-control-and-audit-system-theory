#include "contrat.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
Contrat::Contrat()
{
    codeC=0;
    num=0;
    prix=0;
    this->td="";
    this->tf="";
    this->d="";
    nom="no name";
    loc="";
    email="";
}

Contrat::Contrat(int code,int n,float p,QString td,QString tf,QString d,QString nom,QString lock,QString em)
{
    codeC=code;
    num=n;
    prix=p;
    this->td=td;
    this->tf=tf;
    this->d=d;
    this->nom=nom;
    loc=lock;
    email=em;
}
bool Contrat::ajouter()
{
    QString id_String =QString::number(codeC);
    QString num_String =QString::number(num);
    QString prix_String =QString::number(prix);
    QSqlQuery query;
    query.prepare("INSERT INTO CONTRAT(CODEC,NUM,PRIX,TD,TF,DOMAIN,NOMC,LOC,EMAIL)"
                  "VALUES (:codeC,:num,:prix,:td,:tf,:d,:nom,:loc,:email)");
    query.bindValue(":codeC",id_String);
    query.bindValue(":num",num_String);
    query.bindValue(":prix",prix_String);
    query.bindValue(":td",td);
    query.bindValue(":tf",tf);
    query.bindValue(":d",d);
    query.bindValue(":nom",nom);
    query.bindValue(":loc",loc);
    query.bindValue(":email",email);
    return  query.exec();
}

QSqlQueryModel* Contrat::Afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM CONTRAT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CODEC"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NUM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRIX"));


    return model;
}

bool Contrat::supprimer(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM CONTRAT WHERE CODEC= :id");
    query.bindValue(":codeC",id);
    return  query.exec();
}
bool Contrat::modifier(int id, int n)
{
    QSqlQuery query;

    query.prepare("UPDATE CONTRAT SET NUM = :n WHERE CODEC = :id");
    query.bindValue(":n", n);
    query.bindValue(":id", id);

    return query.exec();
}












