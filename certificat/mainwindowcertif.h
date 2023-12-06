#ifndef MAINWINDOWCERTIF_H
#define MAINWINDOWCERTIF_H
#include <QMainWindow>
#include <QPixmap>
#include <QFileDialog>
#include <QPushButton>
#include <QChartView>
#include <QPieSeries>
#include <QChart>
//#include "arduinocertif.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include "certificat.h"
#include "arduinocertif.h"

namespace Ui {
class MainWindowcertif;
}

class MainWindowcertif : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowcertif(QWidget *parent = nullptr);
    ~MainWindowcertif();
private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_2_supprimer_clicked();
    void on_PDF_clicked();
void on_cherchercertif_2_clicked();
void on_statistiquesButton_clicked();
 void on_modifierButton_clicked();
 void on_pushButton_display_clicked();
 void update_label();

public slots:
 //void update_label();
private:
    Ui::MainWindowcertif *ui;
    Certificat etmp;
QtCharts::QChartView *chartView;
Arduinocertif A;
QByteArray data;

};
#endif // MAINWINDOWCERTIF_H
