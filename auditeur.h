#ifndef AUDITEUR_H
#define AUDITEUR_H
#include <QString>
#include <QDate>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlQueryModel>

class Auditeur
{
public:
    //constructeur
    Auditeur();
    Auditeur(QString , QString , QDate , QString , QString,QString);
     // Méthodes pour définir les attributs
    void setCin(QString cin)
    {
        this->cin = cin;
    }
    void setSexe (QString sexe)
    {
        this->sexe = sexe;
    }
    void setNom(QString nom)
    {
        this->nom = nom;
    }
    void setTel(QString tel)
    {
        this->tel = tel;
    }
    void setMail(QString mail)
    {
        this->mail = mail;
    }
    void setDateNaissance(QDate date)
    {
        this->date = date;
    }
//Méthodes pour récupérer les attributs
    QString getCin()
    {
        return  this->cin;
    }
    QString getSexe()
    {
        return  this->sexe;
    }
    QString getTel()
    {
        return  this->tel;
    }
    QString getNom()
    {
        return  this->nom;
    }
    QString getMail()
    {
        return  this->mail;
    }
    QDate getDateNaissance()
    {
        return  this->date;
    }
  // Méthodes pour interagir avec la base de données
    bool ajouterAuditeur();
    bool supprimerAuditeur(QString cin);
    bool modifierAuditeur();
    
    
    QSqlQueryModel * afficherAuditeur();
    QSqlQueryModel * afficherAuditeurArchives();
    QSqlQueryModel * Recherche(QString);
    QSqlQueryModel * TrierAuditeurs(QString , QString);
    int nombreDeshommes();
    int nombreDesFemmes();
    bool archiver();
    bool desarchiver();
private :// Attributs pour stocker les informations de l'auditeur
    QString cin ;
    QString nom ;
    QDate date;
    QString tel ;
    QString mail ;
    QString sexe ;
};

#endif // AUDITEUR_H
