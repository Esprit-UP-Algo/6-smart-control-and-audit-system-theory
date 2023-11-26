#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtCharts>
#include <QPainter>
#include "auditeur.h"
#include "sms.h"

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

    void on_lineEditRechercheAudit_textChanged(const QString &arg1);

    void on_pushButtonTrierAudit_clicked();

    void on_pushButtonPDFauditeur_clicked();

    void on_pushButtonStatAudit_clicked();



    void on_pushButtonArchiveraudit_clicked();

    void on_tableViewArchive_clicked(const QModelIndex &index);

    void on_pushButtonDesarchiver_clicked();

    void on_tableViewAuditeur_doubleClicked(const QModelIndex &index);

    void on_pushButtonEnvoyerSms_clicked();

private:
    Ui::MainWindow *ui;
    Auditeur Atmp;
};

#endif // MAINWINDOW_H
