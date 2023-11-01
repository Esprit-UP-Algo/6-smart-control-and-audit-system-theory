#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "contrat.h"
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
    void on_pb_ajouter_clicked();

    void on_supp_clicked();


    void on_MODIFIER_clicked();

private:
    Ui::MainWindow *ui;
    Contrat tempe;
};

#endif // MAINWINDOW_H
