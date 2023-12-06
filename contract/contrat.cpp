#include "contrat.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include "QMessageBox"
#include <QPdfWriter>
#include <QPainter>
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
    query.prepare("INSERT INTO CONTRAT(CODEC,NUM,PRIXC,TD,TF,DOMAIN,NOMC,LOC,EMAIL)"
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
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CODEC, NUM, PRIXC, TD, TF, DOMAIN, NOMC, LOC, EMAIL FROM CONTRAT ORDER BY CODEC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CODEC"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NUM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIXC"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TD"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TF"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DOMAIN"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("NOMC"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("LOC"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("PASSWORD"));

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
bool Contrat::modifier(int id, int newNum, const QString &newLoc, const QString &pass)
{
    QSqlQuery query;

    query.prepare("SELECT EMAIL FROM CONTRAT WHERE CODEC = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        QString dbPassword = query.value("EMAIL").toString();

        if (dbPassword != pass) {
            qDebug() << "Incorrect password.";
            return false;
        }
    } else {
        qDebug() << "Error checking password: make sure taht your passwor" ;
        return false;
    }

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
bool Contrat ::chercher()
{

}
bool Contrat::calculateTotalPrix(const QString &selectedPlace, double &totalPrix, double &pix)
{
    totalPrix = 0.0;
    pix = 0.0;

    QSqlQuery sumQuery;
    sumQuery.prepare("SELECT PRIXC FROM CONTRAT WHERE DOMAIN = :place");
    sumQuery.bindValue(":place", selectedPlace);
    bool test = false;

    if (sumQuery.exec()) {
        if (sumQuery.next()) {
            test = true;
            do {
                double prixValue = sumQuery.value("PRIXC").toDouble();
                totalPrix += prixValue;
            } while (sumQuery.next());
        }
    }

    QSqlQuery totalSumQuery;
    totalSumQuery.prepare("SELECT PRIXC FROM CONTRAT");
    if (totalSumQuery.exec() ) {
        if(totalSumQuery.next())
            do{
         double prixvalue = totalSumQuery.value("PRIXC").toDouble();
        pix +=prixvalue;
    }while(totalSumQuery.next());
}
    return test;
}



void Contrat::exportCodecListToPDF(const QString &filePath)
{
    QPdfWriter pdfWriter(filePath);
    QPainter painter(&pdfWriter);

    painter.setFont(QFont("Arial", 12));

    QSqlQuery query("SELECT CODEC FROM CONTRAT");

    int yOffset = 100;

    while (query.next()) {
        QString rawCodec = query.value("CODEC").toString();

        painter.drawText(100, yOffset, rawCodec);
        yOffset += 200;
    }

    QMessageBox::information(nullptr, "PDF Created", "Codec list exported to PDF successfully.", QMessageBox::Ok);
}





