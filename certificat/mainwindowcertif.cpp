#include "mainwindowcertif.h"
#include "ui_mainwindowcertif.h"


#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTextDocument>
#include <QTextStream>
#include <QComboBox>
#include <QTabWidget>
#include"QDate"
#include <QDebug>
#include "certificat.h"
#include <QPdfWriter>
#include <list>
#include <QTableWidget>
#include <QtWidgets>
#include <QtCharts>
#include <QPixmap>
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtSql>
#include <QSqlQuery>

MainWindowcertif::MainWindowcertif(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowcertif)
{   ui->setupUi(this);
    ui->tableView->setModel(etmp.afficher());
    ui->lineEdit_idcertificat->setValidator(new QRegExpValidator(QRegExp("\\d{5}"),this));
    ui->lineEdit_3->setValidator(new QRegExpValidator(QRegExp("\\d{2}"),this));
    ui->lineEdit_4->setValidator(new QRegExpValidator(QRegExp("\\d{1}"),this));
    ui->lineEdit_5->setValidator(new QRegExpValidator(QRegExp("\\d{5}"),this));
     ui->lineEdit_chercher->setValidator(new QRegExpValidator(QRegExp("\\d{5}"),this));

}

MainWindowcertif::~MainWindowcertif()
{
    delete ui;
}
void MainWindowcertif::on_pushButton_ajouter_clicked()
{
    int idcertificat=ui->lineEdit_idcertificat->text().toInt();
    QString objaudit=ui->lineEdit_2->text();
    int durecertif=ui->lineEdit_3->text().toInt();
    int resultau=ui->lineEdit_4->text().toInt();


    Certificat c(idcertificat,resultau,durecertif,objaudit);
    bool test=c.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
      QObject::tr("ajout effectue\n"), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
      QObject::tr("ajout non effectue\n"), QMessageBox::Cancel);
     ui->tableView->setModel(etmp.afficher());
    ui->tableView_2->setModel(etmp.tri());


}
void MainWindowcertif::on_pushButton_2_supprimer_clicked() {
    int idcertificateffacer = ui->lineEdit_5->text().toInt();

   bool test=etmp.supprimer(idcertificateffacer);
   if(test)
   {
       QMessageBox::information(nullptr, QObject::tr("ok"),
     QObject::tr("suppression effectue\n"), QMessageBox::Cancel);

   }
   else
       QMessageBox::critical(nullptr, QObject::tr("not ok"),
     QObject::tr("suppression non effectue\n"), QMessageBox::Cancel);

   ui->tableView->setModel(etmp.afficher());
  ui->tableView_2->setModel(etmp.tri());

}

void MainWindowcertif::on_PDF_clicked()
{
    QString fileName = "C:/Users/HP/Desktop/PDFINTEGRATION/certificat.pdf";

    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));

    QPainter painter(&pdf);




    QImage photo("C:/Users/HP/Desktop/esprit/2eme/LOGO.png");
    painter.drawImage(QRect(0, 0, pdf.width(), pdf.height()), photo);
  painter.setPen(Qt::darkRed);
    painter.setFont(QFont("Times New Roman", 30, QFont::Bold));
    painter.drawText(QRect(0, 50, pdf.width(), 700), Qt::AlignCenter, "Certificat");


    painter.setPen(Qt::white);
    painter.setFont(QFont("Times New Roman", 12, QFont::Bold));


    painter.drawText(QRect(100, 1000, 2000, 300), Qt::AlignLeft, "ID Certificat");
    painter.drawText(QRect(4400, 1000, 2000, 300), Qt::AlignLeft, "Objectif Certificat");
    painter.drawText(QRect(2200, 1000, 2000, 300), Qt::AlignLeft, "Durée Certificat");
    painter.drawText(QRect(6600, 1000, 2000, 300), Qt::AlignLeft, "Résultat d'Audit");


    painter.setFont(QFont("Times New Roman", 10));

    QSqlQuery query;
    query.prepare("SELECT * FROM certificat");
    query.exec();

    int yPos = 1300;
    while (query.next())
    {
        QString idCertificat = query.value(0).toString();
        QString objectifCertificat = query.value(1).toString();
        QString dureeCertificat = query.value(2).toString();
        QString resultatAudit = query.value(3).toString();


        painter.drawText(QRect(100, yPos, 1800, 300), Qt::AlignLeft, idCertificat);
        painter.drawText(QRect(2200, yPos, 2000, 300), Qt::AlignLeft, objectifCertificat);
        painter.drawText(QRect(4400, yPos, 2000, 300), Qt::AlignLeft, dureeCertificat);
        painter.drawText(QRect(6600, yPos, 2000, 300), Qt::AlignLeft, resultatAudit);

        yPos += 300;
    }

    painter.end();

    QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
        QObject::tr("PDF Enregistré!\n" "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
}



void MainWindowcertif::on_cherchercertif_2_clicked()
{
    int idchercher = ui->lineEdit_chercher->text().toInt();
    QSqlQueryModel* model = etmp.recherche(idchercher);
    ui->tableView_3->setModel(model);
}

void MainWindowcertif::on_statistiquesButton_clicked()
{
    Certificat certificat;
    QStringList statistics = certificat.getObjectifCertificatStatistics();


    QChartView *chartView = new QChartView(this);
    QChart *chart = new QChart();
    /*QPieSeries *series = new QPieSeries();


    int totalOccurrences = 0;
    for (const QString& objectif : statistics) {
        int count = certificat.getOccurrences(objectif);
        totalOccurrences += count;
    }


    for (const QString& objectif : statistics) {
        int count = certificat.getOccurrences(objectif);
        qreal percentage = (count / static_cast<qreal>(totalOccurrences)) * 100.0;
        QString label = QString("%1 (%2%)").arg(objectif).arg(percentage, 0, 'f', 2);
        QPieSlice *slice = series->append(label, count);
        slice->setLabelVisible();
    }


    chart->addSeries(series);
    chart->setTitle("Objectif de l'Audit Statistiques");


    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    QDialog *dialog = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(chartView);
    dialog->setWindowTitle("Statistiques");
    dialog->setModal(true);
    dialog->resize(5000, 5000);
    dialog->exec();


    QPixmap pixmap = chartView->grab();
    QString filePath = "C:/taha/statistics.png";
    if (!filePath.isEmpty()) {
        if (pixmap.save(filePath)) {
            qDebug() << "Image saved successfully!";
        } else {
            qDebug() << "Failed to save the image!";
        }
    }*/
}
void MainWindowcertif::on_modifierButton_clicked()
{
    int idCertificat = ui->idCertificatLineEdit->text().toInt();
    QString objectifCertificat = ui->objectifCertificatLineEdit->text();
    int dureeCertificat = ui->dureeCertificatLineEdit->text().toInt();
    int resultatAudit = ui->resultatAuditLineEdit->text().toInt();

    Certificat c(idCertificat, resultatAudit, dureeCertificat, objectifCertificat);
    bool test = c.modifier();

    if (test) {
        QMessageBox::information(this, "Modification réussie", "Le certificat a été modifié avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur de modification", "Une erreur s'est produite lors de la modification du certificat.");
    }
}
void MainWindowcertif::on_pushButton_display_clicked()
{
    A.write_to_arduino();

}



void MainWindowcertif::update_label()
{
    // Query to retrieve the certificate with the highest audit result

QString query = "SELECT * FROM (SELECT * FROM certificat ORDER BY RESULTATDAUDIT DESC) WHERE ROWNUM = 1";
    // Create a QSqlQuery object
QSqlQuery sqlQuery;
sqlQuery.exec(query);

// Debugging output to check the connection to Arduino and the number of rows found
qDebug() << "Connected to Arduino on port:" << A.getarduino_port_name();
qDebug() << "Rows found in the query:" << sqlQuery.size();

// Check if the query executed successfully and if rows are found
if (sqlQuery.next()) {
    // Retrieve the row data using the QSqlRecord
    QSqlRecord record = sqlQuery.record();
    int resultatCertificat = record.value("RESULTATDAUDIT").toInt();

    // Update the text of the label with the highest audit result
    ui->label->setText( QString::number(resultatCertificat));
} else {
    // Handle the case when no rows are found
    ui->label->setText("No Audit Results Found");
}
}
