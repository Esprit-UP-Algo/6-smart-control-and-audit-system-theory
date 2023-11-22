#include "certificat.h"
#include<QtPrintSupport/QPrinter>
#include<QFileDialog>
#include<QTextDocument>

Certificat::Certificat(int idcertificat,int resultau,int durecertif,QString objaudit)
{
this->idcertificat=idcertificat;
    this->resultau=resultau;
    this->durecertif=durecertif;
    this->objaudit=objaudit;
}
bool Certificat::ajouter()
{ QSqlQuery query;
    QString res = QString::number(idcertificat);
    QString  one = QString::number(resultau);
    QString se = QString::number(durecertif);
    query.prepare("insert into certificat (idcertificat, resultatdaudit, durecertificat, objectifcertificat)""values (:idcertificat, :resultau, :durecertif, :objaudit)");
    query.bindValue(":idcertificat",res);
     query.bindValue(":resultau",one);
      query.bindValue(":durecertif",se);
       query.bindValue(":objaudit",objaudit);
       return  query.exec();

}
QSqlQueryModel * Certificat::afficher()
{
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("SELECT  * FROM CERTIFICAT");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("idcertificat"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("DURECERTIFICAT"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("OBJECTIFCERTIFICAT"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("RESULTATDAUDIT"));
   return  model;

}
bool Certificat::supprimer(int idcertificat)
{
    QSqlQuery query;
    QString res = QString::number(idcertificat);
   query.prepare("delete from certificat where idcertificat= :idcertificat");
           query.bindValue(":idcertificat",res);
   return query.exec();
}
bool Certificat::modifier()
{
    QSqlQuery query;
    QString res = QString::number(idcertificat);
    QString  one = QString::number(resultau);
    QString se = QString::number(durecertif);
    query.prepare("UPDATE certificat SET resultat = :resultatdaudit, durecertificat durecertif= :durecertificat , objectifcertificat objaudit= :objectifcertificat WHERE idcertificat = :idcertificat");
    query.bindValue(":idcertificat",res);
     query.bindValue(":resultau",one);
      query.bindValue(":durecertif",se);
       query.bindValue(":objaudit",objaudit);

   return query.exec();

}

QSqlQueryModel *  Certificat::tri()
{
    QSqlQueryModel * model= new QSqlQueryModel();

   model->setQuery("select * from certificat order by resultatdaudit");

   model->setHeaderData(0,Qt::Horizontal,QObject::tr("idcertificat"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("OBJECTIFCERTIFICAT"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("DURECERTIFICAT"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("RESULTATDAUDIT"));


    return model;
}


QSqlQueryModel* Certificat::recherche(int idcertificat)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM CERTIFICAT WHERE idcertificat = :idcertificat");
    query.bindValue(":idcertificat", idcertificat);
    query.exec();
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idcertificat"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("OBJECTIFCERTIFICAT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DURECERTIFICAT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("RESULTATDAUDIT"));

    return model;
}
QStringList Certificat::getObjectifCertificatStatistics()
{
    QStringList statistics;

    QSqlQuery query;
    query.prepare("SELECT DISTINCT objectifcertificat FROM CERTIFICAT");

    if (query.exec())
    {
        int count = 0;
        while (query.next())
        {
            QString objectifCertificat = query.value(0).toString();
            statistics << objectifCertificat;
            count++;
        }

        statistics.prepend(QString::number(count));
    }

    return statistics;
}

int Certificat::getOccurrences(const QString& objectif) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM certificat WHERE objectifcertificat = ?");
    query.bindValue(0, objectif);
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}
