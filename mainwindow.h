#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include <QMainWindow>
#include "contrat.h"
#include <QSerialPort>
#include <QTextEdit>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void exportToPDF();
private slots:
    void on_pb_ajouter_clicked();

    void on_supp_clicked();
    void readData();


    void on_MODIFIER_clicked();

    void on_afficheur_clicked();

    void on_statistics_clicked();

    void on_exportpdf_clicked();

    void on_exportpng_clicked();

    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
    Contrat tempe;
    QByteArray data;
    QSerialPort *serial;
    QTextEdit *textEdit;
};

#endif // MAINWINDOW_H
