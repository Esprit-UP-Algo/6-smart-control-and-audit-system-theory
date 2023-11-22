#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "mission.h"
QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    mission m;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajouter_clicked();

    void on_pushButton_supp_clicked();

    void on_affichem_clicked();

    void on_pushButton_modifier_clicked();

    void on_pb_recher_clicked();

    void on_pb_trier_clicked();

    void on_pb_stat_clicked();

    void on_pb_pdf_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

