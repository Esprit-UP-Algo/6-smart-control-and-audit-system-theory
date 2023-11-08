#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contrat.h"
#include "QMessageBox"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tab_contrat->setModel(tempe.Afficher());
    ui->lineEdit_code->setValidator(new QRegExpValidator(QRegExp("\\d+"),this));
    ui->lineEdit_num->setValidator(new QRegExpValidator(QRegExp("\\d{9}"), this));
    ui->lineEdit_prix->setValidator(new QRegExpValidator(QRegExp("\\d+"),this));

    ui->lineEdit_td->setValidator(new QRegExpValidator(QRegExp("\\d{2}/\\d{2}/\\d{4}"), this));
    ui->lineEdit_tf->setValidator(new QRegExpValidator(QRegExp("\\d{2}/\\d{2}/\\d{4}"), this));
    ui->lineEdit_codemod->setValidator(new QRegExpValidator(QRegExp("\\d+"),this));
    ui->lineEdit_newnum->setValidator(new QRegExpValidator(QRegExp("\\d{9}"),this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->lineEdit_code->text().toInt();
    int num=ui->lineEdit_num->text().toInt();
    int prix=ui->lineEdit_prix->text().toInt();
    QString td=ui->lineEdit_td->text();
    QString tf=ui->lineEdit_tf->text();
    QString d=ui->lineEdit_d->text();
    QString nom=ui->lineEdit_nom->text();
    QString loc=ui->lineEdit_loc->text();
    QString email=ui->lineEdit_email->text();
    Contrat C(id,num,prix,td,tf,d,nom,loc,email);
    bool t=C.ajouter();
    QMessageBox msgBox;
    if (t){
          msgBox.setText("Ajout avec succes.");

          ui->tab_contrat->setModel(tempe.Afficher());

      }
      else

          msgBox.setText("Echec d'ajout");
          msgBox.exec();
}

void MainWindow::on_supp_clicked()
{
    Contrat c;
    c.SetcodeC(ui->le_id_sup->text().toInt());
    bool test=c.supprimer(c.GetcodeC());
    QMessageBox msgBox;

    if(test)
    {   msgBox.setText("supprimer avec succes.");
         ui->tab_contrat->setModel(tempe.Afficher());
        }


    else
        msgBox.setText("non supprimer");
    msgBox.exec();
}



void MainWindow::on_MODIFIER_clicked()
{
    int id=ui->lineEdit_codemod->text().toInt();
    int num=ui->lineEdit_newnum->text().toInt();
    QString loc=ui->lineEdit_newloc->text();
    Contrat c;
    QMessageBox msgBox;

    bool test =c.modifier(id,num,loc);
    if(test)
    {
            msgBox.setText("modifier avec succes.");
            ui->tab_contrat->setModel(tempe.Afficher());

        }
        else

            msgBox.setText("Echec de modification");
            msgBox.exec();
}
