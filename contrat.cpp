#include "contrat.h"

Contrat::Contrat()
{
    id=0;
    name="";
    start_time="";
    end_time="";
    price=0;
    field="";
    num=0;
    adresse="";
}
Contrat::Contrat(int id,QString name,QString start_time ,QString end_time,QString field,double  price,int num,QString adresse)
{
    this->id=id;
    this->name=name;
    this->start_time=start_time;
    this->end_time=end_time;
    this->field=field;
    this->price=price;
    this->num=num;
    this->adresse=adresse;
}
