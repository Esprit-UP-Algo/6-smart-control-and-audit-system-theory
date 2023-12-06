#include "auditeur.h"

Auditeur::Auditeur()
{

}
Auditeur::Auditeur(QString cin, QString nom , QDate dn, QString tel, QString mail , QString sexe)
{
    this->nom = nom ;
    this->cin = cin ;
    this->date = dn ;
    this->tel = tel ;
    this->mail = mail ;
    this->sexe = sexe ;
}

bool Auditeur::ajouterAuditeur()
{//to do
    QSqlQuery query ;
    query.prepare("insert into auditeur(cin,date_dinscription,nom,mail,numero_de_telephone,sexe,estarchive)" "values(:cin,:date,:nom,:mail,:tel,:sexe,:est)");

    query.bindValue(":cin",cin);
    query.bindValue(":date",date);
    query.bindValue(":nom",nom);
    query.bindValue(":mail",mail);
    query.bindValue(":tel", tel);
    query.bindValue(":sexe", sexe);
     query.bindValue(":est", 0);


    return query.exec();
}

bool Auditeur::supprimerAuditeur(QString cin)
{//to do
    QSqlQuery query ;
    query.prepare("delete from auditeur where cin = :cin ");
    query.bindValue(":cin",cin);

  return query.exec();

}

QSqlQueryModel * Auditeur::afficherAuditeur()
{//to do
QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("select cin,date_dinscription,nom,mail,numero_de_telephone,sexe from auditeur where estarchive = '0'");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date d'inscription"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("E-mail"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Numero de téléphone"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Sexe"));

   return model;
}
QSqlQueryModel * Auditeur::afficherAuditeurArchives()
{//to do
QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("select cin,date_dinscription,nom,mail,numero_de_telephone,sexe from auditeur where estarchive = '1'");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date d'inscription"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("E-mail"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Numero de téléphone"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Sexe"));

   return model;
}
bool Auditeur::modifierAuditeur()
{
    QSqlQuery query ;
    query.prepare("Update auditeur set nom=:nom,mail=:mail,numero_de_telephone=:num,date_dinscription=:di,sexe =:s where cin=:cin");
    query.bindValue(":cin",cin);
    query.bindValue(":di",this->date);
    query.bindValue(":nom",this->nom);
    query.bindValue(":mail",this->mail);
    query.bindValue(":num",this->tel);
    query.bindValue(":s",this->sexe);

    return query.exec();

}

QSqlQueryModel * Auditeur::Recherche(QString ch)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select cin,date_dinscription,nom,mail,numero_de_telephone,sexe from auditeur where cin like '%" + ch +"%' OR mail like '%" + ch +"%' OR numero_de_telephone like '%" + ch +"%' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date d'inscription"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("E-mail"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Numero de téléphone"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Sexe"));


    return model ;
}
QSqlQueryModel * Auditeur::TrierAuditeurs(QString order, QString column)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("SELECT cin,date_dinscription,nom,mail,numero_de_telephone,sexe FROM auditeur ORDER BY " + column + " " + order);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date d'inscription"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("E-mail"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Numero de téléphone"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Sexe"));


    return model ;
}

int Auditeur::nombreDeshommes()
{
    int count = 0 ;
    QSqlQuery query ;
    query.prepare("select  count(*) from auditeur where sexe = :sexe ");
    QString sexeValue = "Homme";
       query.bindValue(":sexe", sexeValue);

       if (query.exec()) {
           // Fetch the result
           if (query.next()) {

               count = query.value(0).toInt();

           }
       }
       return count ;
}
int Auditeur::nombreDesFemmes()
{
    int count = 0 ;
    QSqlQuery query ;
    query.prepare("select  count(*) from auditeur where sexe = :sexe ");
    QString sexeValue = "Femme";
       query.bindValue(":sexe", sexeValue);

       if (query.exec()) {
           // Fetch the result
           if (query.next()) {

               count = query.value(0).toInt();

           }
       }
       return count ;
}
bool Auditeur::archiver()
{
    QSqlQuery query ;
    query.prepare("Update auditeur set estarchive=:est where cin=:cin");
   query.bindValue(":est", 1);
    query.bindValue(":cin", cin);
    return query.exec();

}
bool Auditeur::desarchiver()
{
    QSqlQuery query ;
    query.prepare("Update auditeur set estarchive=:est where cin=:cin");
   query.bindValue(":est", 0);
    query.bindValue(":cin", cin);
    return query.exec();

}



