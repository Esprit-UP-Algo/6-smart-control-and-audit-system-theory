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
/*
QSqlQueryModel* Contrat::Afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM CONTRAT ORDER BY CODEC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CODEC"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NUM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRIX"));


    return model;
}*/
QSqlQueryModel* Contrat::Afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CONTRAT ORDER BY CODEC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CODEC"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NUM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));

    // Loop through the model to format the number without scientific notation
    for (int row = 0; row < model->rowCount(); ++row)
    {
        QModelIndex index = model->index(row, 2); // Assuming the large number is in the third column (index 2)
        QVariant data = model->data(index);
        if (data.canConvert<int>())
        {
            int number = data.toInt();
            QString formattedNumber = QString::number(number);
            model->setData(index, formattedNumber);
        }
    }

    return model;
}


bool Contrat::supprimer(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("DELETE FROM CONTRAT WHERE CODEC = :id");
    query.bindValue(":id", id);
    if (query.exec()) {
        if (query.numRowsAffected() > 0)
            return true;
    }

    return false;
}
bool Contrat::modifier(int id, int newNum, const QString &newLoc)
{
    QSqlQuery query;

    query.prepare("UPDATE CONTRAT "
                  "SET NUM = :newNum, "
                  "    LOC = :newLoc "
                  "WHERE CODEC = :id");

    query.bindValue(":newNum", newNum);
    query.bindValue(":newLoc", newLoc);

    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}









