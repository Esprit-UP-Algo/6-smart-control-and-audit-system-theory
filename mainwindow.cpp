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
        msgBox.setText("supprimer avec succes.");


    else
        msgBox.setText("non supprimer");
        msgBox.exec();
}



void MainWindow::on_MODIFIER_clicked()
{
    int id=ui->le_id_sup->text().toInt();
    int n=ui->LE_NUM->text().toInt();
    Contrat c;
    bool test =c.modifier(id,n);
}
