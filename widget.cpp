#include "widget.h"
#include "ui_widget.h"

widget::widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::widget)
{
    ui->setupUi(this);



}

widget::~widget()
{
    delete ui;
}

void widget::on_pushButton_formation_clicked()
{
  formation = new gesfor(this);
  formation->show();
}

void widget::on_pushButton_contract_clicked()
{
    contract = new MainWindowContrat(this);
    contract->show();
}

void widget::on_pushButton_auditeur_clicked()
{
    auditeur = new MainWindow(this);
    auditeur->show();
}

void widget::on_pushButton_certificat_clicked()
{
    certificat = new MainWindowcertif(this);
    certificat->show();
}

void widget::on_pushButton_mission_clicked()
{
    mission = new MainWindowmission(this);
    mission->show();
}
