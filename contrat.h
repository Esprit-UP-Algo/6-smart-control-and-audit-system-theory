#ifndef CONTRAT_H
#define CONTRAT_H

#include <iostream>

#include <QString>
class Contrat
{
public:
    Contrat();
    Contrat(int,QString,QString,QString,QString,double,int,QString);
    int id,num;
    QString name,start_time,end_time,field,adresse;
    double  price;
};

#endif // CONTRAT_H
