#include "auditeur.h"

Auditeur::Auditeur()
{

}
Auditeur::Auditeur(QString cin, QString nom , QDate dn, QString tel, QString mail)
{
    this->nom = nom ;
    this->cin = cin ;
    this->date = dn ;
    this->tel = tel ;
    this->mail = mail ;
}

bool Auditeur::ajouterAuditeur()
{//to do
    QSqlQuery query ;
    query.prepare("insert into auditeur(cin,date_dinscription,nom,mail,numero_de_telephone)" "values(:cin,:date,:nom,:mail,:tel)");

    query.bindValue(":cin",cin);
    query.bindValue(":date",date);
    query.bindValue(":nom",nom);
    query.bindValue(":mail",mail);
    query.bindValue(":tel", tel);


    return query.exec();
}

bool Auditeur::supprimerAuditeur(int id)
{//to do
    QSqlQuery query ;
    query.prepare("delete from auditeur where cin = :cin ");
    query.bindValue(":cin",id);

  return query.exec();

}

QSqlQueryModel * Auditeur::afficherAuditeur()
{//to do
QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("select * from auditeur");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date d'inscription"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("E-mail"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Numero de téléphone"));

   return model;
}
bool Auditeur::modifierAuditeur()
{
    QSqlQuery query ;
    query.prepare("Update auditeur set nom=:nom,mail=:mail,numero_de_telephone=:num,date_dinscription=:di where cin=:cin");
    query.bindValue(":cin",cin);
    query.bindValue(":di",this->date);
    query.bindValue(":nom",this->nom);
    query.bindValue(":mail",this->mail);
    query.bindValue(":num",this->tel);

    return query.exec();
}
