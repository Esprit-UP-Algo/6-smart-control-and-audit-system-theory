#ifndef CONTRAT_H
#define CONTRAT_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQueryModel>

class Contrat
{
public:
    Contrat();
    Contrat(int,int,float,QString,QString,QString,QString,QString,QString);
    int GetcodeC() { return codeC; }
    void SetcodeC(int val) { codeC = val; }
    int Getnum() { return num; }
    void Setnum(int val) { num = val; }
    float Getprix() { return prix; }
    void Setprix(float val) { prix = val; }
    QString GetstartDate() { return td; }
    void SetstartDate(QString val) { td = val; }
    QString GetendDate() { return tf; }
    void SetendDate(QString val) { tf = val; }
    QString GetnomC() { return nom; }
    void SetnomC(QString val) { nom = val; }
    QString Getloc() { return loc; }
    void Setloc(QString val) { loc = val; }
    QString Getemail() { return email; }
    void Setemail(QString val) { email = val; }
    bool ajouter();
    QSqlQueryModel* Afficher();
    bool supprimer(int);
    bool modifier(int, int , const QString& );

private:
    int codeC,num;
    int prix;
    QString td,tf,d;
    QString nom,loc,email;

};

#endif // CONTRAT_H
