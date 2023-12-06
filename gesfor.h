//DONE
#ifndef GESFOR_H
#define GESFOR_H
#include "formation.h"
#include"arduino.h"

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include"QDate"
#include<QtDebug>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QChart>
#include <QPieSeries>
#include <QPieSlice>
#include <QChartView>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class gesfor; }
QT_END_NAMESPACE

class gesfor : public QMainWindow
{
    Q_OBJECT

public:
    gesfor(QWidget *parent = nullptr);
    ~gesfor();
    bool validerSaisie(QString cineffacer);
     bool recherche(QString code);

     float getRandomPercentage();
private slots:
     void on_pushButton_ajoutrrf_clicked();

     void on_pushButton_supprimerf_clicked();

     void on_pushButton_modifierf_clicked();

     void on_pushButton_confirmer_clicked();






     void on_pushButton_r_clicked();

     void on_pushButton_trif_clicked();



     void on_pushButton_PDFF_clicked();



     void on_pushButton_stats_clicked();
     void sendMail();
     void mailSent(QString);

     void browse();

      int obtenirNombreType(int type);

      void mettreAJourAffichage();
     //void update_label();

     void on_pushButton_display_clicked();

private:
    Ui::gesfor *ui;
    formation sf;
    formation f;
    QString infoToShow;
     bool rechercheEffectuee;
    bool cinExists(QString code);
    void rechercherFormationParCode(int code);
    bool rechercheEnCours;
    QStringList files;
    QtCharts::QPieSeries *PieSeries;
    QtCharts::QChartView *ChartView;
    Arduino A;
    QByteArray data;
};
#endif // GESFOR_H
