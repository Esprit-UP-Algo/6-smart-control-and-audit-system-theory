#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonAjoutMission_clicked()
{
    QString code_mission = ui->Line_code_mission->text();
    QString date_mission = ui->linedateMission->text();
    QString statut_mission = ui->lineStatutMission->text();

    Mission a(code_mission,date_mission,statut_mission);
    bool test = a.ajouterMission();
    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("Success"),
                    QObject::tr("ajouté avec success.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                    QObject::tr("ajout echoué !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButtonSupprimerMission_clicked()
{
int id=ui->lineEditsupp->text().toInt();
bool test=Atmp.supprimerMission(int code_mission);
if(test)
{
    QMessageBox::information(nullptr, QObject::tr("Success"),
                QObject::tr("supprimé avec success.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
else
{
    QMessageBox::critical(nullptr, QObject::tr("Error"),
                QObject::tr("suppression echoué !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
}


void MainWindow::on_pushButtonModifierMission_clicked()
{
    QString code_mission = ui->Line_code_mission->text();
    QString date_mission = ui->linedateMission->text();
    QString statut_mission = ui->lineStatutMission->text();
    Mission a(code_mission,date_mission,statut_mission);
    bool test = a.modifierMission();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Success"),
                    QObject::tr("modifié avec success.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                    QObject::tr("modification echoué !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

