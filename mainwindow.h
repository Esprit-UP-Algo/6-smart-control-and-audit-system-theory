#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "auditeur.h"
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

    void on_pushButtonAjoutAuditeur_clicked();

    void on_pushButtonSupprimerAuditeur_clicked();

    void on_pushButtonModifierAuditeur_clicked();
    void on_tableViewAuditeur_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Auditeur Atmp;
};

#endif // MAINWINDOW_H

