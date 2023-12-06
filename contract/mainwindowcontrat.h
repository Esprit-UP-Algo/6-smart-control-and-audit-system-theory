#ifndef MAINWINDOWCONTRAT_H
#define MAINWINDOWCONTRAT_H

#include <QMainWindow>
#include <QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include <QMainWindow>
#include "contrat.h"
#include <QSerialPort>
#include <QTextEdit>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowContrat; }
QT_END_NAMESPACE

class MainWindowContrat : public QMainWindow
{
    Q_OBJECT

public:
    MainWindowContrat(QWidget *parent = nullptr);
    ~MainWindowContrat();
    void exportToPDF();
private slots:
    void on_pb_ajouter_clicked();

    void on_supp_clicked();
    //void readData();


    void on_MODIFIER_clicked();

    void on_afficheur_clicked();

    void on_statistics_clicked();

    void on_exportpdf_clicked();

    void on_exportpng_clicked();

    //void on_pushButton_clicked();
private:
    Ui::MainWindowContrat *ui;
    Contrat tempe;
    QByteArray data;
    QSerialPort *serial;
    QTextEdit *textEdit;
};
#endif // MAINWINDOWCONTRAT_H
