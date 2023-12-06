#include "mainwindowmission.h"
#include "ui_mainwindowmission.h"
#include <QString>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
using namespace std;
#include"mission.h"
//#include"connection.h"
#include <iostream>
#include <QtCharts/QPieSeries>

#include <QPieSeries>
#include <QPieSlice>
#include <QChart>
#include <QChartView>
#include <QStackedWidget>
#include <QtCharts>
#include <QSqlQuery>

#include<QPrinter>
#include<QPainter>
#include<QPdfWriter>
#include<QTextTable>
#include<QTextDocument>

#include <QVBoxLayout>

#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QMessageBox>
#include <QSqlError>
#include <QFileDialog>
#include <QPieSeries>
#include <QPieSlice>
#include <QChart>
#include <QChartView>
#include <QStackedWidget>
#include <QtCharts>
#include <QSqlQuery>
#include <QPrinter>
#include<QPainter>
#include<QPdfWriter>
#include<QTextTable>
#include<QTextDocument>

#include <QVBoxLayout>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
MainWindowmission::MainWindowmission(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowmission)
{
    ui->setupUi(this);
    ui->tableView->setModel(m.afficher());

    ui->lineEdit_DATE->setValidator(new QRegExpValidator(QRegExp("\\d{2}/\\d{2}/\\d{4}"),this));

}

MainWindowmission::~MainWindowmission()
{
    delete ui;
}

void MainWindowmission::on_pushButton_ajouter_clicked()
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

void MainWindowmission::on_pushButton_supp_clicked()
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



void MainWindowmission::on_affichem_clicked()
{

    ui->tableView->setModel(m.afficher());
}

void MainWindowmission::on_pushButton_modifier_clicked()
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
void MainWindowmission::on_pb_recher_clicked()

{
int code_mission=ui->lineEdit_CODE_2->text().toInt();

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    QString res=QString::number(code_mission);
    query.prepare("SELECT  * FROM MISSION WHERE CODE_MISSION = :CODE_MISSION");
    query.bindValue(":CODE_MISSION", res);

    if (query.exec()) {
        model->setQuery(query);
        ui->tableView->setModel(model);

    } else {

        qDebug() << "Erreur de requête SQL : " << query.lastError().text();
    }


}

void MainWindowmission::on_pb_trier_clicked()
{
    QSqlQueryModel *sortedModel = m.trier(2);
    ui->tableView->setModel(sortedModel);
}
void MainWindowmission::on_pb_stat_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT STATUT_MISSION, COUNT(*) FROM MISSION GROUP BY STATUT_MISSION");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête.";
        return;
    }

    QPieSeries *series = new QPieSeries();

    while (query.next()) {
        QString STATUT_MISSION = query.value(0).toString();
        int count = query.value(1).toInt();  // Use index 1 for COUNT(*)

        QPieSlice *slice = new QPieSlice(STATUT_MISSION, count);
        series->append(slice);
    }

    foreach(QPieSlice *slice, series->slices()) {
        QString label = QString("%1 (%2%)")
            .arg(slice->label())
            .arg(100 * slice->percentage(), 0, 'f', 1);
        slice->setLabel(label);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des missions selon le statut");

    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);
    chartView->show();
}


void MainWindowmission::on_pb_pdf_clicked()
{  QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");
    if (fileName.isEmpty()) {
        return;
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QTextCursor cursor(&doc);


    QTextCharFormat headerFormat;
    headerFormat.setFontPointSize(14);
    headerFormat.setFontWeight(QFont::Bold);
    cursor.setCharFormat(headerFormat);
    cursor.insertText("ordre de mission\n\n");

    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignLeft);
    QTextTable *table = cursor.insertTable(1, 7, tableFormat);
    QTextCursor cellCursor;

    cellCursor = table->cellAt(0, 0).firstCursorPosition();
    cellCursor.insertText("code de mission\n");

    cellCursor = table->cellAt(0, 1).firstCursorPosition();
    cellCursor.insertText("date de mission\n");

    cellCursor = table->cellAt(0, 2).firstCursorPosition();
    cellCursor.insertText("statut de mission");

    QSqlQueryModel *model = static_cast<QSqlQueryModel*>(ui->tableView->model());


    for (int row = 0; row < model->rowCount(); ++row) {
        table->appendRows(1);

        for (int col = 0; col < 7; ++col) {
            cellCursor = table->cellAt(row + 1, col).firstCursorPosition();
            cellCursor.insertText(model->data(model->index(row, col)).toString());
        }
    }

    doc.print(&printer);


    QMessageBox::information(this, "Succès", "Ordre de mission sous forme de PDF.");
}



#include <QVBoxLayout>
#include <QWidget>
void MainWindowmission::on_png_clicked()
{        int afficheur_code = ui->lineEdit_CODE->text().toInt();
        QSqlQuery selectQuery;
        selectQuery.prepare("SELECT * FROM MISSION WHERE CODE_MISSION = :codeC");
        selectQuery.bindValue(":codeC", afficheur_code);
        if (selectQuery.exec() && selectQuery.next() && selectQuery.isValid()) {
            QString code=selectQuery.value("code_mission").toString();
            QString prix=selectQuery.value("date_mission").toString();
            QString num=selectQuery.value("statut_mission").toString();


        QWidget widget;

        QPixmap screenshot = widget.grab();

        QWidget myWidget;

           QVBoxLayout* layout = new QVBoxLayout(&myWidget);


           QLabel* contentLabel = new QLabel("\n\n\n\n\n\n This mission has the code : " + (code)+"\n\n\n  "
                                            "and the date :"+(prix)+"\n\n\n"
                                             "and with the status :" +(num)+"\n\n\n"

                                             "\n\n\n\n\n\n"
                                             "your signature here                        votre signature here\n\n\n\n\n\n\n");

           layout->addWidget(contentLabel);

           QPixmap screenshot1 = myWidget.grab();
        screenshot1.save("C:/Users/jihen/OneDrive/Bureau/projet2/window_design.jpeg", "JPEG");

    }
}

void MainWindowmission::on_tableau_clicked()
{

  ui->tableView->setModel(m.tableau());

}
