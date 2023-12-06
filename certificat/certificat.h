#ifndef CERTIFICAT_H
#define CERTIFICAT_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include<QFileDialog>
#include<QTextDocument>
#include <QPainter>
#include "ui_mainwindowcertif.h"
class Certificat
{int idcertificat,resultau,durecertif,cin;
    QString objaudit;

    //Q_OBJECT
public:
    Certificat(){}
    Certificat(int,int,int,QString);
    QString getObjaudit(){return objaudit;}
    int getIdcertificat(){return idcertificat;};
    int getResultau(){return idcertificat;};
    int getDurecertif(){return idcertificat;};
    int getCin(){return idcertificat;};
    void setIdcertificat(int idcertificat){this->idcertificat=idcertificat;}
    void setResultau(int resultau){this->resultau=resultau;}
    void setDurecertificat(int durecertif){this->durecertif= durecertif;}
    void setObjaudit(QString objaudit){this->objaudit=objaudit;}
    void setCin(int cin){this->cin=cin;}
    bool ajouter();
   QSqlQueryModel  * afficher();
    bool supprimer(int);
    bool modifier();
      QSqlQueryModel * tri();
      int getOccurrences(const QString& objectif);
      void someFunction();




           QSqlQueryModel * recherche(int);
          QStringList getObjectifCertificatStatistics();
};

#endif // CERTIFICAT_H
