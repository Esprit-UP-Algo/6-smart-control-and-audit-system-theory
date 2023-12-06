
#include "gesfor.h"
#include "ui_gesfor.h"
#include <QtWidgets>
#include <QTableWidget>
#include <QRegExp>
#include <QDebug>
#include <QtSql>
#include <QSqlQuery>
#include <QPieSeries>

#include "smtp.h"
#include "formation.h"
#include "arduino.h"
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>  // Include QtCharts header for QPieSeries
#include <QtCharts/QPieSlice>
#include <QDate>
#include <QtDebug>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QChart>
#include <QPieSlice>
#include <QChartView>
QT_CHARTS_USE_NAMESPACE





gesfor::gesfor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gesfor)
{
    ui->setupUi(this);
    connect(ui->sendBtn_2, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn_2, SIGNAL(clicked()), this, SLOT(browse()));

    ui->tableView->setModel(sf.afficher());

    connect(ui->comboBox_type, SIGNAL(currentTextChanged(const QString &)), this, SLOT(on_comboBox_type_currentTextChanged(const QString &)));




    ui->lineEdit_code->setValidator(new QIntValidator(0, 9999, this));
    ui->lineEdit->setValidator(new QIntValidator(0, 9999, this));
    ui->lineEdit_recherche->setValidator(new QIntValidator(0, 9999, this));


    ui->lineEdit_nom->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]*"), this));
    ui->lineEdit_prenom->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]*"), this));
    ui->comboBox_type->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]*"), this));
    int ret=A.connect_arduino(); // lancer la connexion à arduino

    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(mettreAJourAffichage())); // permet de lancer
    //le slot update_label suite à la reception du signal readyRead (reception des données).

 }
 /*void gesfor::update_label()
 {
     QByteArray data;
     data = A.read_from_arduino();

     if (!data.isEmpty()) {
         QString nom = A.chercher(data);
         if (!nom.isEmpty()) {
             QMessageBox::information(this, tr("Welcome"), tr("Bienvenue %1").arg(nom));
             qDebug() << "valid";
               A.write_to_arduino("0");
         }else {

             QMessageBox::information(this, tr("verfication"), tr("code n existe pas"));
             qDebug() << "invalid";
         }
     } else {

     }
 }*/


gesfor::~gesfor()
{
    delete ui;
}
void gesfor::on_pushButton_ajoutrrf_clicked()
{
// Get input values from UI elements
int code = ui->lineEdit_code->text().toInt();
QString prenom = ui->lineEdit_prenom->text();
QString nom = ui->lineEdit_nom->text();
QString type = ui->comboBox_type->currentText();
float prix = ui->lineEdit_prix->text().toFloat();
QDate datef = ui->dateEdit->date();


// Ajouter la formation à la base de données ou à la liste sans vérifications
formation f(code, prenom, nom, type, prix, datef);
bool test = f.ajouter();

if (test) {
    ui->tableView->setModel(sf.afficher());
    QMessageBox::information(this, "Success", "Formation added successfully.");
} else {
    QMessageBox::warning(this, "Error", "Failed to add formation to the database.");
}
}
bool gesfor::validerSaisie(QString cineffacer) {
if (cineffacer.isEmpty()) {
    QMessageBox::warning(this, "Warning", "Le champ est vide. Veuillez saisir un code.");
    return false;
}

bool ok;
cineffacer.toInt(&ok);
if (!ok) {
    QMessageBox::warning(this, "Warning", "Le code doit être un nombre.");
    return false;
}

if (!cinExists(cineffacer)) {
    QMessageBox::warning(this, "Warning", "Code non trouvé dans la base de données.");
    return false;
}

return true;
}

bool gesfor::cinExists(QString cinInput) {
QSqlQuery query;
query.prepare("SELECT COUNT(*) FROM FORMATION WHERE codef = :codef");
query.bindValue(":codef", cinInput);
query.exec();
query.next();
return query.value(0).toInt() > 0;}


void gesfor::on_pushButton_supprimerf_clicked() {
    QString cineffacer = ui->lineEdit->text();

    if (validerSaisie(cineffacer)) {
        bool test = sf.supprimer(cineffacer);

        if (test) {
            ui->tableView->setModel(sf.afficher());
            QMessageBox::information(this, "Succès", "Suppression effectuée.");
        } else {
            QMessageBox::critical(this, "Erreur", "Suppression non effectuée.");
        }
    }
}


void gesfor::on_pushButton_modifierf_clicked() {
    int code= ui->lineEdit->text().toInt();
       rechercherFormationParCode(code);
        ui->lineEdit_code->setReadOnly(true);

}
void gesfor::rechercherFormationParCode(int code)
{QSqlQuery qry;
    qry.prepare("SELECT * FROM FORMATION WHERE codef = :codef");
    qry.bindValue(":codef", code);
    if (qry.exec() && qry.next()) {
        ui->lineEdit_code->setText(qry.value(0).toString());
        ui->lineEdit_prenom->setText(qry.value(1).toString());
        ui->lineEdit_nom->setText(qry.value(2).toString());
        ui->comboBox_type->setWhatsThis(qry.value(3).toString());
        ui->lineEdit_prix->setText(qry.value(4).toString());
        ui->dateEdit->setWhatsThis(qry.value(5).toString());
    } else {
        QMessageBox::warning(this, "Error", "No information found for this CODE");
    }


}

void gesfor::on_pushButton_confirmer_clicked()
  {

    // Désactivez la zone de saisie du code
    ui->lineEdit_code->setReadOnly(true);

    // Récupérez les valeurs des autres champs
    QString prenom = ui->lineEdit_prenom->text();
    QString nom = ui->lineEdit_nom->text();
    QString type = ui->comboBox_type->currentText();
    float prix = ui->lineEdit_prix->text().toFloat();
    QDate datef = ui->dateEdit->date();

    // Créez un objet Formation sans modifier le code
    int code = ui->lineEdit_code->text().toInt(); // Obtenez la valeur du code
    formation f(code, prenom, nom, type, prix, datef);

    // Appelez la méthode de modification
    bool test = f.modifier();

    if (test) {
        ui->tableView->setModel(sf.afficher());
        QMessageBox::information(this, "Success", "Formation updated successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to update formation in the database.");
    }
}




void gesfor::on_pushButton_r_clicked() {
    qDebug() << "Bouton de recherche cliqué.";

    QString code = ui->lineEdit_recherche->text();
    formation f;

    if (f.recherche(code)) {
        QSqlQuery query;

        query.prepare("SELECT  * FROM formation WHERE codef= :codef");
        query.bindValue(":codef", code);

        if (query.exec() && query.next()) {
            // Créez un modèle pour stocker les données
            QStandardItemModel *model = new QStandardItemModel();

            // Ajoutez des en-têtes au modèle
            model->setHorizontalHeaderLabels({"Code", "Nom", "Prénom", "Type", "Prix", "Date"});

            // Ajoutez les données à partir de la requête à votre modèle
            QList<QStandardItem *> rowItems;
            for (int column = 0; column < query.record().count(); ++column) {
                rowItems.append(new QStandardItem(query.value(column).toString()));
            }
            model->appendRow(rowItems);

            // Définissez le modèle sur votre QTableView
            ui->tableView->setModel(model);
        } else {
            QMessageBox::warning(this, "Avertissement", "La formation n'existe pas.");
        }
    } else {
        QMessageBox::warning(this, "Avertissement", "La formation n'existe pas.");
    }
}


void gesfor::on_pushButton_trif_clicked()
{
     QString tri = ui->comboBox_tri->currentText();
    QSqlQueryModel* model;

     if(tri == "prix elevée") // trier par Prix dans l'ordre croissant
         {
             formation f;
             model = f.afficherTriprix();
         }
  else   if(tri == "De A..Z") // trier par nom dans l'ordre croissant
         {
             formation f;
             model = f.afficherTriNom();
         }
    else if(tri == "prix bas") // trier par Prix dans l'ordre décroissant
         {
             formation f;
             model = f.afficherTriprixD();}
     else   if(tri == "De Z..A") // trier par Prix dans l'ordre décroissant
            {
                formation f;
                model = f.afficherTriNomD();}
     else   if(tri == "codeA") // trier par Code  dans l'ordre croissant
            {
                formation f;
                model = f.afficherTriCode();}
     else   if(tri == "codeD") // trier par Code  dans l'ordre croissant
            {
                formation f;
                model = f.afficherTriCodeD();}

      else{return;}
      ui->tableView->setModel(model);
}



void gesfor::on_pushButton_PDFF_clicked()
{qDebug() << "Bouton de recherche cliqué.";

    QString html = "<html><head><style>h1{color:#00bfff; font-size:50px;} p{color:#404040; font-size:250px;} strong{color:#FF0000;}</style></head><body>";
    html += "<img src='file:///C:/Users/21692/Downloads/kisspng-computer-icons-physician-login-medicine-user-avatar-5ac45a4d44fe99.2456489015228176132826.jpg' alt='Texte alternatif de l&#39;image' style='position: absolute; top: 0; left: 100;'>";
    html += "<h1>Liste des Formations</h1><br>";

    QSqlQuery query;
    query.prepare("SELECT * FROM formation");
    query.exec();

    while (query.next()) {
        QString prenom = query.value(1).toString();
        QString nom = query.value(2).toString();
        QString type = query.value(3).toString();
        double prix = query.value(4).toDouble();
        QString dateFormation = query.value(5).toDate().toString("yyyy-MM-dd");


        html += "<p><strong>Code :</strong> " + query.value(0).toString() + "</p><br>";
        html += "<p>-------------------------------------------------------------------------------------------------------------</p><br>";
        html += "<p><strong>prenom :</strong> " + query.value(1).toString() + "</p><br>";
        html += "<p>--------------------------------------------------------------------------------------------------------------</p><br>";
        html += "<p><strong>nom :</strong> " + query.value(2).toString() + "</p><br>";
        html += "<p>--------------------------------------------------------------------------------------------------------------</p><br>";
        html += "<p><strong>type :</strong> " + query.value(3).toString() + "</p><br>";
        html += "<p>--------------------------------------------------------------------------------------------------------------</p><br>";
        html += "<p><strong>prix :</strong> " + QString::number(prix) + " DT</p><br>";
        html += "<p><strong>Date de formation :</strong> " + dateFormation + "</p><br>";  // Ajout de la date
        html += "<p>--------------------------------------------------------------------------------------------------------------</p><br>";


        html += "<p>--------------------------------------------------------------------------------------------------------------</p><br>";
        html += "<p>--------------------------------------------------------------------------------------------------------------</p><br>";

    }

    html += "</body></html>";

    QPdfWriter writer("ListeFormations.pdf");
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageMargins(QMarginsF(20, 20, 20, 20));

    QPainter painter(&writer);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 100));
    QTextDocument document;
    document.setHtml(html);
    document.drawContents(&painter);

    painter.end();

    QDesktopServices::openUrl(QUrl::fromLocalFile("ListeFormations.pdf"));}






void gesfor::on_pushButton_stats_clicked()
{
    QSqlQuery q1, q2, q3, q4, q5;
    qreal tot = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0;
    q1.prepare("SELECT codef FROM formation");
    q1.exec();
    q2.prepare("SELECT codef FROM formation WHERE typef='type1'");
    q2.exec();
    q3.prepare("SELECT codef FROM formation WHERE typef='type2'");
    q3.exec();
    q4.prepare("SELECT codef FROM formation WHERE typef='type3'");
    q4.exec();

    while (q1.next()) { tot++; }
    while (q2.next()) { c1++; }
    while (q3.next()) { c2++; }
    while (q4.next()) { c3++; }
    while (q5.next()) { c4++; }

    c1 = (c1 * 100) / tot;
    c2 = (c2 * 100) / tot;
    c3 = (c3 * 100) / tot;
    c4 = (c4 * 100) / tot;

    QString etat1 = "type1 = " + QString::number(c1) + "%";
    QString etat2 = "type2 = " + QString::number(c2) + "%";
    QString etat3 = "type3 = " + QString::number(c3) + "%";

    // Création des pie series
    QPieSeries *series = new QPieSeries();
    series->append(etat1, c1);
    series->append(etat2, c2);
    series->append(etat3, c3);

    // Creation d'un chart
    QChart *chart = new QChart();
    chart->setTitle("Les résultats:");
    chart->addSeries(series);
    chart->legend()->show();
    chart->setBackgroundBrush(QColor(252, 236, 218, 0));

    // Affichage du chart
    QChartView *chartView = new QChartView(chart, ui->graphicsView);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(400, 400);
    chartView->show();
}





void  gesfor::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file_2->setText( fileListString );

}
void   gesfor::sendMail()
{
    Smtp* smtp = new Smtp("rebai.youssef@esprit.tn",ui->paswd_2->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("rebai.youssef@esprit.tn", ui->rcpt_2->text() , ui->subject_2->text(),ui->msg_2->toPlainText(), files );
    else
        smtp->sendMail("rebai.youssef@esprit.tn", ui->rcpt_2->text() , ui->subject_2->text(),ui->msg_2->toPlainText());
}
void   gesfor::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt_2->clear();
    ui->subject_2->clear();
    ui->file_2->clear();
    ui->msg_2->clear();
    ui->paswd_2->clear();
}

#include <QSqlQuery>
#include <QSqlRecord>
#include <QByteArray>

void gesfor::mettreAJourAffichage() {
    int type = ui->lineEdit_type->text().toInt();

        // Obtenez le nombre associé au type
        int nombre = obtenirNombreType(type);

        // Connectez-vous à Arduino et envoyez les données
        if (A.connect_arduino() == 0) {
            // Envoyez les données à Arduino (vous devrez implémenter cette fonction dans la classe Arduino)
            QString data = QString::number(type) + "," + QString::number(nombre);
                   QByteArray byteArray = data.toUtf8();

                   // Envoyez les données à Arduino en utilisant la fonction existante


            // Fermez la connexion à Arduino
            A.close_arduino();
        } else {
            qDebug() << "Échec de la connexion à Arduino";
        }
    }





int gesfor::obtenirNombreType(int type) {
    QSqlQuery query;
        query.prepare("SELECT codef FROM formation WHERE typef='type1'");
        query.bindValue(":typef", type);
        query.exec();

        int count = 0;

        if (query.next()) {
            count = query.value(0).toInt();
        }

        // Effectuez d'autres opérations nécessaires selon votre logique
        // ...

        return count;
}

void gesfor::on_pushButton_display_clicked()
{
        // Récupérez le texte saisi dans le QLineEdit
        QString typeText = ui->lineEdit_type->text();



        // Vérifiez si le texte n'est pas vide
        if (!typeText.isEmpty()) {
            // Affichez le texte dans une boîte de dialogue ou faites autre chose avec
            QMessageBox::information(this, tr("Type Entered"), tr("Type: %1").arg(typeText));

            // Vous pouvez ajouter une logique supplémentaire ici en fonction du type saisi
            // Par exemple, mettre à jour l'affichage en fonction du type
            mettreAJourAffichage();
        } else {
            // Si le texte est vide, affichez un avertissement ou prenez d'autres mesures nécessaires
            QMessageBox::warning(this, tr("Empty Type"), tr("Veuillez saisir un type."));
        }
    }

