#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    ui->tableViewAuditeur->setModel(Atmp.afficherAuditeur());
    ui->tableViewArchive->setModel(Atmp.afficherAuditeurArchives());
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
    QString sexe = ui->comboBoxSexeAudit->currentText();


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

Auditeur a(cin, nom, date, tel, mail,sexe);
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

    int reponse = QMessageBox::question(this, "Suppression", "Vous Voulez supprimer l'auditeur dont le cin est : " + Atmp.getCin() + "?" , QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        bool test=Atmp.supprimerAuditeur(Atmp.getCin());
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
}



void MainWindow::on_pushButtonModifierAuditeur_clicked()
{
    QString cin = ui->Line_cin_auditeur->text();
    QString nom = ui->lineNomAuditeur->text();
    QString mail = ui->lineMailAuditeur->text();
    QString tel = ui->lineTelAuditeur->text();
    QDate date = ui->dateEditAuditeur->date();
    QString sexe = ui->comboBoxSexeAudit->currentText();
    Auditeur a(cin,nom,date,tel,mail,sexe);
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
      Atmp.setCin(ui->tableViewAuditeur->model()->data(ui->tableViewAuditeur->model()->index(index.row(), 0)).toString());
      ui->Line_cin_auditeur->setText(ui->tableViewAuditeur->model()->data(ui->tableViewAuditeur->model()->index(index.row(),0)).toString());
      ui->dateEditAuditeur->setDate(ui->tableViewAuditeur->model()->data(ui->tableViewAuditeur->model()->index(index.row(),1)).toDate());
      ui->lineNomAuditeur->setText(ui->tableViewAuditeur->model()->data(ui->tableViewAuditeur->model()->index(index.row(),2)).toString());
      ui->lineMailAuditeur->setText(ui->tableViewAuditeur->model()->data(ui->tableViewAuditeur->model()->index(index.row(),3)).toString());
      ui->lineTelAuditeur->setText(ui->tableViewAuditeur->model()->data(ui->tableViewAuditeur->model()->index(index.row(),4)).toString());;  
      ui->comboBoxSexeAudit->setCurrentText(ui->tableViewAuditeur->model()->data(ui->tableViewAuditeur->model()->index(index.row(),5)).toString());
}

void MainWindow::on_lineEditRechercheAudit_textChanged(const QString &arg1)
{
     ui->tableViewAuditeur->setModel(Atmp.Recherche(arg1));
}

void MainWindow::on_pushButtonTrierAudit_clicked()
{
    QString champ = "cin" ;
    QString order = "asc";

   if (ui->comboBoxColumnTri->currentText().compare("Nom") == 0)
    {
        champ = "nom";
    }
    else if (ui->comboBoxColumnTri->currentText().compare("Mail") == 0)
    {
        champ = "mail";
    }
    if (ui->comboBoxOrderTri->currentText().compare("Descendant") == 0 )
    {
        order = "desc";
    }

    ui->tableViewAuditeur->setModel(Atmp.TrierAuditeurs(order,champ));
}

void MainWindow::on_pushButtonPDFauditeur_clicked()
{
    QPdfWriter pdf("audits.pdf");
               QPainter painter(&pdf);
               int i = 4000;
               painter.setPen(Qt::cyan);
               painter.setFont(QFont("Arial", 30));
               painter.drawText(2800,1200,"Liste des auditeurs");
               painter.setPen(Qt::black);
               painter.setFont(QFont("Arial", 50));
               painter.drawRect(1500,200,7300,2600);
               painter.drawRect(0,3000,9600,500);
               painter.setFont(QFont("Arial", 9));
               painter.drawText(1300,3300,"Cin");
               painter.drawText(2600,3300,"Date inscription");
               painter.drawText(3900,3300,"Nom");
               painter.drawText(5200,3300,"Email");
               painter.drawText(6500,3300,"Numero");
               painter.drawText(7800,3300,"Sexe");

               QSqlQuery query;
               query.prepare("select * from auditeur");
               query.exec();
               while (query.next())
               {
                   painter.drawText(1300,i,query.value(0).toString());
                   painter.drawText(2600,i,query.value(1).toDate().toString(Qt::DateFormat()));
                   painter.drawText(3900,i,query.value(2).toString());
                   painter.drawText(5200,i,query.value(3).toString());
                   painter.drawText(6500,i,query.value(4).toString());
                   painter.drawText(7800,i,query.value(5).toString());
                   i = i +500;
               }

               int reponse = QMessageBox::question(this, "Génerer PDF", "Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
               if (reponse == QMessageBox::Yes)
               {
                   QDesktopServices::openUrl(QUrl::fromLocalFile("audits.pdf"));

                   painter.end();
               }
               if (reponse == QMessageBox::No)
               {
                   painter.end();
               }
}

void MainWindow::on_pushButtonStatAudit_clicked()
{
    // Create a bar set

     int Hommes = Atmp.nombreDeshommes();
     int Femmes = Atmp.nombreDesFemmes();
       QBarSet *barSet = new QBarSet("Nombre Hommes");
       QBarSet *barSet1 = new QBarSet("Nombre Femmes ");
       *barSet << Hommes ;
       *barSet1 << Femmes ;

        barSet->setColor(Qt::cyan);
        barSet1->setColor(Qt::red);

       // Create a bar series and add the bar set to it
       QBarSeries *barSeries = new QBarSeries();
       barSeries->append(barSet);
       barSeries->append(barSet1);

       // Create a chart and add the bar series to it
       QChart *chart = new QChart();
       chart->addSeries(barSeries);

       // Create a category axis and set labels for each category
       chart->createDefaultAxes();
       chart->axisX()->hide();

       // Create a chart view and set the chart
       QChartView *chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->resize(1000, 800);
       chartView->show();
}



void MainWindow::on_pushButtonArchiveraudit_clicked()
{
    int reponse = QMessageBox::question(this, "archivage", "Vous Voulez archiver l'auditeur dont le cin est : " + Atmp.getCin() + "?" , QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        bool test=Atmp.archiver();
        if(test)
     {
     ui->tableViewAuditeur->setModel(Atmp.afficherAuditeur());
      ui->tableViewArchive->setModel(Atmp.afficherAuditeurArchives());
    QMessageBox::information(nullptr, QObject::tr("Success"),
                QObject::tr("archivé avec success.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
else
{
    QMessageBox::critical(nullptr, QObject::tr("Error"),
                QObject::tr(" echec !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
    }
}

void MainWindow::on_tableViewArchive_clicked(const QModelIndex &index)
{
    Atmp.setCin(ui->tableViewArchive->model()->data(ui->tableViewArchive->model()->index(index.row(), 0)).toString());
}

void MainWindow::on_pushButtonDesarchiver_clicked()
{
    int reponse = QMessageBox::question(this, "desarchivage", "Vous Voulez desarchiver l'auditeur dont le cin est : " + Atmp.getCin() + "?" , QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        bool test=Atmp.desarchiver();
        if(test)
     {
     ui->tableViewAuditeur->setModel(Atmp.afficherAuditeur());
      ui->tableViewArchive->setModel(Atmp.afficherAuditeurArchives());
    QMessageBox::information(nullptr, QObject::tr("Success"),
                QObject::tr("desachivé avec success.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
else
{
    QMessageBox::critical(nullptr, QObject::tr("Error"),
                QObject::tr("echec !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
    }
}

void MainWindow::on_tableViewAuditeur_doubleClicked(const QModelIndex &index)
{
    ui->lineEditNumeroTelSms->setText(ui->tableViewAuditeur->model()->data(ui->tableViewAuditeur->model()->index(index.row(), 4)).toString());
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButtonEnvoyerSms_clicked()
{


       std::string apiKey = "5e61f688";
       std::string apiSecret = "NoU7mBRQpP0KpuVZ";
       std::string fromNumber = "Vonage";
       std::string toNumber = ui->lineEditNumeroTelSms->text().toStdString();
       QString message = ui->plainTextEditContenuSMS->toPlainText();

       SMS sms(apiKey, apiSecret, fromNumber);
       if (sms.sendSMS(toNumber, message)) {
           QMessageBox::information(nullptr, QObject::tr("Success"),
                       QObject::tr("sms envoyé avec success.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
       }
       else {
           QMessageBox::critical(nullptr, QObject::tr("Error"),
                       QObject::tr("echec !.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
       }
}
