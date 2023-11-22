#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QFileDialog>
#include <QPushButton>
#include <QChartView>
#include <QPieSeries>
#include <QChart>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include "certificat.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_2_supprimer_clicked();
    void on_PDF_clicked();
void on_cherchercertif_2_clicked();
void on_statistiquesButton_clicked();
 void on_modifierButton_clicked();

private:
    Ui::MainWindow *ui;
    Certificat etmp;
QtCharts::QChartView *chartView;
};

#endif // MAINWINDOW_H
