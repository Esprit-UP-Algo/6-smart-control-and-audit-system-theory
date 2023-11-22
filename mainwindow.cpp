#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contrat.h"
#include "QMessageBox"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QScreen>
#include <QPixmap>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tab_contrat->setModel(tempe.Afficher());
    ui->contrat_lineEdit_code->setValidator(new QRegExpValidator(QRegExp("\\d+"),this));
    ui->contrat_lineEdit_num->setValidator(new QRegExpValidator(QRegExp("\\d{9}"), this));
    ui->contrat_lineEdit_prix->setValidator(new QRegExpValidator(QRegExp("\\d+"),this));

    ui->contrat_lineEdit_td->setValidator(new QRegExpValidator(QRegExp("\\d{2}/\\d{2}/\\d{4}"), this));
    ui->contrat_lineEdit_tf->setValidator(new QRegExpValidator(QRegExp("\\d{2}/\\d{2}/\\d{4}"), this));
    ui->lineEdit_codemod->setValidator(new QRegExpValidator(QRegExp("\\d+"),this));
    ui->lineEdit_newnum->setValidator(new QRegExpValidator(QRegExp("\\d{9}"),this));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->contrat_lineEdit_code->text().toInt();
    int num=ui->contrat_lineEdit_num->text().toInt();
    int prix=ui->contrat_lineEdit_prix->text().toInt();
    QString td=ui->contrat_lineEdit_td->text();
    QString tf=ui->contrat_lineEdit_tf->text();
    QString d=ui->contrat_lineEdit_d->text();
    QString nom=ui->contrat_lineEdit_nom->text();
    QString loc=ui->contrat_lineEdit_loc->text();
    QString email=ui->contrat_lineEdit_email->text();
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
    c.SetcodeC(ui->contrat_le_id_sup->text().toInt());
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
    QString pass=ui->contrat_pass->text();
    Contrat c;
    QMessageBox msgBox;

    bool test =c.modifier(id,num,loc,pass);
    if(test)
    {



            msgBox.setText("modifier avec succes.");
            ui->tab_contrat->setModel(tempe.Afficher());

        }
        else

            msgBox.setText("Echec de modification");
            msgBox.exec();
}
void MainWindow::on_afficheur_clicked()
{



    QString emailToSearch = ui->contrat_lineEdit_code->text();


        QSqlQuery query;
        query.prepare("SELECT * FROM CONTRAT WHERE CODEC = :AAA");
        query.bindValue(":AAA", emailToSearch);

        if (query.exec() && query.next()) {

            QString mail = query.value(1).toString();
            QString date1erContact = query.value(2).toString();
            QString adresse = query.value(3).toString();


            QSqlQueryModel* model = new QSqlQueryModel();
            model->setQuery("SELECT * FROM CONTRAT WHERE codeC = '" + emailToSearch + "'");
            ui->tab_contrat->setModel(model);

            QMessageBox::information(this, "Client trouvé", "Coordonnées du client affichées.");
        } else {

            QMessageBox::warning(this, "Client non trouvé", "Aucun client trouvé avec cette adresse e-mail.");
        }

    }

void MainWindow::on_statistics_clicked()
{

    Contrat c;
    QString d=ui->contrat_domdom->text();
    double totalPrix;
    double pix;
    bool placeExists = c.calculateTotalPrix(d, totalPrix,pix);

    if (placeExists) {
        ui->contrat_values->setText(QString::number(totalPrix));
    } else {
        QMessageBox::warning(this, "Warning", "No data found for the given domain.");
    }
    QPieSeries *series=new QPieSeries();
    qDebug() << "pix: " << pix;

    series->setHoleSize(0.35);
double  percentage = (totalPrix/pix)*100;
QPieSlice *slice=series->append("your choise",percentage);
    slice->setExploded();
    series->append("Other ",100-percentage);
    QChart *chart=new QChart ();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("Donut Chart Example");
    QChartView *chartview =new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setParent(ui->horizontalFrame);
    ui->percent->setText(QString::number(percentage));
    ui->percent_2->setText(QString::number(100-percentage));

}


void  MainWindow::exportToPDF() {
    QString filename = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "Fichiers PDF (*.pdf)");

       if (!filename.isEmpty()) {
           QPdfWriter pdfWriter(filename);
           pdfWriter.setPageSize(QPageSize(QPageSize::A4));
           pdfWriter.setPageOrientation(QPageLayout::Portrait);
           pdfWriter.setCreator("houssem");

           QTextDocument doc;
           QTextCursor cursor(&doc);
           QTextCharFormat format;
            QTextBlockFormat blockFormat;
           format.setFontPointSize(100);



           Contrat contrat;


           QSqlQueryModel *clientModel = contrat.Afficher();


           for (int row = 0; row < clientModel->rowCount(); ++row) {
               QString clientInfo;
               for (int col = 0; col < clientModel->columnCount(); ++col) {
                   clientInfo += clientModel->data(clientModel->index(row, col)).toString() + "   ";
               }
               cursor.insertText(clientInfo, format);
               blockFormat.setLineHeight(150, QTextBlockFormat::FixedHeight);
                           cursor.setBlockFormat(blockFormat);
               cursor.insertBlock();
           }

           doc.setPageSize(QSizeF(pdfWriter.width(), pdfWriter.height()));
           doc.print(&pdfWriter);

           QProcess::startDetached("SumatraPDF.exe", QStringList() << filename);
       }
}





void MainWindow::on_exportpdf_clicked()
{
    exportToPDF();
}


void MainWindow::on_exportpng_clicked()
{
    int afficheur_code = ui->contrat_exportid->text().toInt();
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM CONTRAT WHERE CODEC = :codeC");
    selectQuery.bindValue(":codeC", afficheur_code);
    if (selectQuery.exec() && selectQuery.next() && selectQuery.isValid()) {
        QString code=selectQuery.value("CODEC").toString();
        QString prix=selectQuery.value("PRIXC").toString();
        QString num=selectQuery.value("NUM").toString();
        QString tf=selectQuery.value("TF").toString();
        QString td=selectQuery.value("TD").toString();
        QString domain=selectQuery.value("DOMAIN").toString();
        QString nom=selectQuery.value("NOMC").toString();
        QString loc=selectQuery.value("LOC").toString();

    QWidget widget;

    QPixmap screenshot = widget.grab();

    QWidget myWidget;

       QVBoxLayout* layout = new QVBoxLayout(&myWidget);

       QLabel* contentLabel = new QLabel("\n\n\n\n This contrat have the code : " + (code)+"\n\n\n  "
                                        "and the prix :"+(prix)+"\n\n\n"
                                         "and with the number of phone :" +(num)+"\n\n\n"
                                         "with the name :"+(nom)+"\n\n\n"
                                         "specialised in the domain :"+(domain)+"\n\n\n"
                                         "we will start working together from :"+(td)+"\n\n\n"
                                         "and we panned to end the contract in :"+(tf)+"\n"
                                         "\n\n\n\n\n"
                                         "notre signature ici                        votre signature ici\n\n\n\n\n\n\n");

       layout->addWidget(contentLabel);

       QPixmap screenshot1 = myWidget.grab();
    screenshot1.save("C:/Users/lenovo/Desktop/c++/zProjet/ProjetCpp/window_design.png", "PNG");
}}

void MainWindow::on_pushButton_clicked()
{
    int id=ui->contrat_id_login->text().toInt();
    QString pass=ui->contrat_pass_login->text();
    QSqlQuery query;
    QLabel* label = ui->contrat_log_in_shield;
    QLabel* label1 = ui->contrat_log_in_shield_2;
    query.prepare("SELECT EMAIL FROM CONTRAT WHERE CODEC = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        QString dbPassword = query.value("EMAIL").toString();

        if (dbPassword != pass) {
            qDebug() << "Incorrect password.";
            label1->setFixedSize(10000,10000);
            label->setFixedSize(10000, 10000);
            ui->contrat_pass_login->clear();

        }
        else
        {

            label1->setFixedSize(1,1);
            label->setFixedSize(1, 1);
        }
    } else {
        qDebug() << "Error checking id: make sure taht your id existe" ;
        label1->setFixedSize(10000,10000);
        label->setFixedSize(10000, 10000);
        ui->contrat_id_login->clear();
    }

}
