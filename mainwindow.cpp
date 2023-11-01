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
void MainWindow::on_pushButton_ajouter_clicked()
{
    int code_mission=ui->Line_code_mission->text().toInt();
    QString date_mission=ui->linedateMission->text();
    QString statut_mission=ui->lineStatutMission->text();
    Mission M(code_mission,date_mission,statut_mission);
    bool test=E.ajouter();
    if (test)
    {
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click Cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not Ok"),
                              QObject::tr("Ajout non affectué.\n"
                                          "Click Cancel to exit."),QMessageBox::Cancel);
}
void MainWindow::on_pushButton_supprimer_clicked()
{
    int code_mission=ui->lineEdit_IDS->text().toInt();
    bool test=MS.supprimer(code_mission);
    if(test)
    {
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("Suppression effectuée.\n"
                                             "Click Cancelto exit."),QMessageBox::Cancel);
    }
}

    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(MS.afficher());
}
void MainWindow::on_pushButton_ajouter_clicked()
{
    int code_mission=ui->lineEdit_code->text().toInt();
    QString date=ui->lineEdit_date->text();
    QString statut=ui->lineEdit_statut->text();
    Mission M(code_mission,date_mission,statut_mission);
    bool test=M.ajouter();
    if (test)
    {
        ui->tableView->setModel(MS.afficher());
        QMessageBox::information(nullptr)
}
