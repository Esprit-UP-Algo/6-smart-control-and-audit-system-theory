#ifndef MAINWINDOWMISSION_H
#define MAINWINDOWMISSION_H

#include <QMainWindow>
#include "mission.h"
QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE


namespace Ui {
class MainWindowmission ;
}

class MainWindowmission : public QMainWindow
{
    Q_OBJECT

public:
    mission m;
    explicit MainWindowmission(QWidget *parent = nullptr);
    ~MainWindowmission();

private slots:
    void on_pushButton_ajouter_2_clicked();

    void on_pushButton_supp_2_clicked();

    void on_affichem_2_clicked();

    void on_pushButton_modifier_2_clicked();

    void on_pb_recher_2_clicked();

    void on_pb_trier_2_clicked();
void on_pb_stat_2_clicked();


    void on_pb_pdf_2_clicked();

    void on_png_2_clicked();

    void on_tableau_2_clicked();

private:
    Ui::MainWindowmission *ui;
};

#endif // MAINWINDOWMISSION_H
