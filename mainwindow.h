#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Mission.h"
#include <QMessageBox>

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

    void on_pushButtonAjoutMission_clicked();

    void on_pushButtonSupprimerMission_clicked();

    void on_pushButtonModifierMission_clicked();
    void on_tableViewMission_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Mission Atmp;
};

#endif // MAINWINDOW_H

