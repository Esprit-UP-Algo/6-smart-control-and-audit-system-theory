#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
using namespace std;
#include"mission.h"
#include"connection.h"
#include <iostream>
#include <QtCharts/QPieSeries>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(m.afficher());

    ui->lineEdit_DATE->setValidator(new QRegExpValidator(QRegExp("\\d{2}/\\d{2}/\\d{4}"),this));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajouter_clicked()
{
 qDebug();

 int code_mission=ui->lineEdit_CODE->text().toInt();

    QString date_mission=ui->lineEdit_DATE->text();
    QString statut_mission=ui->lineEdit_STATUT->text();

    mission m(code_mission, date_mission,statut_mission);

bool test=m.ajouter();
if (test){
    QMessageBox::information(nullptr, QObject::tr("ok"),

                QObject::tr("ajout avec success.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                QObject::tr(" ajout non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_supp_clicked()
{
    int code_mission=ui->lineEdit_Supp->text().toInt();
    bool test=m.supprimer(code_mission);
if (test)
 {   QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("suppression avec success.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
else
    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                QObject::tr(" suppression non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}



void MainWindow::on_affichem_clicked()
{

    ui->tableView->setModel(m.afficher());
}

void MainWindow::on_pushButton_modifier_clicked()
{
    qDebug();
    int code_mission=ui->lineEdit_CODE->text().toInt();

       QString date_mission=ui->lineEdit_DATE->text();
       QString statut_mission=ui->lineEdit_STATUT->text();

       mission m(code_mission, date_mission,statut_mission);

    bool test=m.modifier(code_mission);
    if (test){ ui->tableView->setModel(m.afficher());
    QMessageBox::information(nullptr, QObject::tr("ok"), QObject::tr("update avec success.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
   else
   QMessageBox::critical(nullptr, QObject::tr("not ok"), QObject::tr(" update non effectué.\n" "Click Cancel to exit."), QMessageBox::Cancel);

}
void MainWindow::on_pb_recher_clicked()

{
int code_mission=ui->lineEdit_CODE->text().toInt();
    // Créez un modèle de requête SQL pour afficher la livraison recherchée.
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT  * FROM EMPLOYEE WHERE NOM = :NOM");
    query.bindValue(":CODE_MISSION", code_mission);

    if (query.exec()) {
        model->setQuery(query);
        ui->tableView->setModel(model);

    } else {
        // Gérez les erreurs de requête SQL si nécessaire.
        qDebug() << "Erreur de requête SQL : " << query.lastError().text();
    }


}
void MainWindow::on_pb_trier_clicked()
{
    QSqlQueryModel *sortedModel = m.trier(2);
    ui->tableView->setModel(sortedModel);
}
void MainWindow::on_pb_stat_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT NOM, ABSENCE(*) FROM EMPLOYEE GROUP BY NOM");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête.";
        //db.close();
        return;
    }

    // Création de la série de données pour le graphique en secteurs
    QPieSeries *series = new QPieSeries();

    while (query.next()) {
        QString nom= query.value(0).toString();
        int absence = query.value(1).toInt();
        series->append(nom, absence);
    }

    foreach(QPieSlice *slice, series->slices()) {
        QString label = QString("%1 (%2%)")
            .arg(slice->label())
            .arg(100 * slice->percentage(), 0, 'f', 1);
        slice->setLabel(label);
    }

    // Création du graphique et ajout de la série de données
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des employes selon l'e statut'absence ");

    // Configuration du graphique
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setAnimationOptions(QChart::AllAnimations);

    // Affichage du graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);
    chartView->show();
}
void MainWindow::on_pb_pdf_clicked()
{  QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");
    if (fileName.isEmpty()) {
        return;  // L'utilisateur a annulé la boîte de dialogue
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QTextCursor cursor(&doc);

    // En-tête du document
    QTextCharFormat headerFormat;
    headerFormat.setFontPointSize(14);
    headerFormat.setFontWeight(QFont::Bold);
    cursor.setCharFormat(headerFormat);
    cursor.insertText("Liste des livraisons\n\n");

    // Crée un tableau avec des colonnes pour chaque champ de la table
    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignLeft);
    QTextTable *table = cursor.insertTable(1, 7, tableFormat);
    QTextCursor cellCursor;

    // Remplir les en-têtes de colonne
    cellCursor = table->cellAt(0, 0).firstCursorPosition();
    cellCursor.insertText("code de mission");

    cellCursor = table->cellAt(0, 1).firstCursorPosition();
    cellCursor.insertText("date de mission");

    cellCursor = table->cellAt(0, 2).firstCursorPosition();
    cellCursor.insertText("statut de mission");

    // Obtain the client data from your table model
    QSqlQueryModel *model = static_cast<QSqlQueryModel*>(ui->tableView->model());

    // Fill the table data
    for (int row = 0; row < model->rowCount(); ++row) {
        table->appendRows(1);

        for (int col = 0; col < 7; ++col) {
            cellCursor = table->cellAt(row + 1, col).firstCursorPosition();
            cellCursor.insertText(model->data(model->index(row, col)).toString());
        }
    }

    doc.print(&printer);

    // Display a success message
    QMessageBox::information(this, "Succès", "Liste des livraisons exportée sous forme de PDF.");
}

