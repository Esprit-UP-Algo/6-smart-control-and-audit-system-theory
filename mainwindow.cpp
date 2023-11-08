#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableViewAuditeur->setModel(Atmp.afficherAuditeur());
    ui->dateEditAuditeur->setDate(QDate::currentDate());
    ui->Line_cin_auditeur->setValidator(new QRegExpValidator(QRegExp("\\d+"), this));

   ui->lineNomAuditeur->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));

    ui->lineMailAuditeur->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}"), this));

   ui->lineTelAuditeur->setValidator(new QRegExpValidator(QRegExp("\\d+"), this));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonAjoutAuditeur_clicked()
{
    QString cin = ui->Line_cin_auditeur->text();
    QString nom = ui->lineNomAuditeur->text();
    QString mail = ui->lineMailAuditeur->text();
    QString tel = ui->lineTelAuditeur->text();
    QDate date = ui->dateEditAuditeur->date();


    // Vérification de la longueur du numéro de téléphone
       if (tel.length() != 8)
       {
           QMessageBox::warning(this, "Erreur", "Le numéro de téléphone doit être composé de 8 chiffres.");
           return;
       }
    QRegularExpression emailRegex("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}");
       QRegularExpressionMatch match = emailRegex.match(mail);
       if (!match.hasMatch())
       {
           QMessageBox::warning(this, "Erreur", "Veuillez entrer une adresse e-mail valide.");
           return;
       }

    if (cin.length() != 8)
        {
            QMessageBox::warning(this, "Erreur", "Le CIN doit être composé de 8 chiffres.");
            return;
        }

Auditeur a(cin, nom, date, tel, mail);
  bool test = a.ajouterAuditeur();
    if(test)
    {
         ui->tableViewAuditeur->setModel(Atmp.afficherAuditeur());
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

void MainWindow::on_pushButtonSupprimerAuditeur_clicked()
{
int id=ui->lineEditsupp->text().toInt();
QString mail = ui->lineMailAuditeur->text();
QString tel = ui->lineTelAuditeur->text();
QRegularExpression emailRegex("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}");
   QRegularExpressionMatch match = emailRegex.match(mail);
   if (!match.hasMatch())
   {
       QMessageBox::warning(this, "Erreur", "Veuillez entrer une adresse e-mail valide.");
       return;
   }
   if (tel.length() != 8)
      {
          QMessageBox::warning(this, "Erreur", "Le numéro de téléphone doit être composé de 8 chiffres.");
          return;
      }
bool test=Atmp.supprimerAuditeur(id);
if(test)
{
     ui->tableViewAuditeur->setModel(Atmp.afficherAuditeur());
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



void MainWindow::on_pushButtonModifierAuditeur_clicked()
{
    QString cin = ui->Line_cin_auditeur->text();
    QString nom = ui->lineNomAuditeur->text();
    QString mail = ui->lineMailAuditeur->text();
    QString tel = ui->lineTelAuditeur->text();
    QDate date = ui->dateEditAuditeur->date();
    Auditeur a(cin,nom,date,tel,mail);
    bool test = a.modifierAuditeur();
    if(test)
    {
         ui->tableViewAuditeur->setModel(Atmp.afficherAuditeur());
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


void MainWindow::on_tableViewAuditeur_clicked(const QModelIndex &index)
{
    QString cinString = ui->tableViewAuditeur->model()->data(ui->tableViewAuditeur->model()->index(index.row(), 0)).toString();

       // Convert the CIN to an integer
       bool conversionOK;
       int cin = cinString.toInt(&conversionOK);

       if (conversionOK) {
           // Successfully converted to an integer, now set it to the text field
           ui->Line_cin_auditeur->setText(QString::number(cin));
       } else {
           // Handle the case where the CIN couldn't be converted to an integer
           ui->Line_cin_auditeur->setText("Invalid CIN");
       }

      ui->Line_cin_auditeur->setText(ui->tableViewAuditeur->model()->data(ui->tableViewAuditeur->model()->index(index.row(),0)).toString());
      ui->dateEditAuditeur->setDate(ui->tableViewAuditeur->model()->data(ui->tableViewAuditeur->model()->index(index.row(),1)).toDate());
      ui->lineNomAuditeur->setText(ui->tableViewAuditeur->model()->data(ui->tableViewAuditeur->model()->index(index.row(),2)).toString());
      ui->lineMailAuditeur->setText(ui->tableViewAuditeur->model()->data(ui->tableViewAuditeur->model()->index(index.row(),3)).toString());
      ui->lineTelAuditeur->setText(ui->tableViewAuditeur->model()->data(ui->tableViewAuditeur->model()->index(index.row(),4)).toString());;  
}
