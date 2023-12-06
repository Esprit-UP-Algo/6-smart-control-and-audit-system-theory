#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include <QStackedWidget>
#include "formation/gesfor.h"
#include "contract/mainwindowcontrat.h"
#include "auditeur/mainwindow.h"
#include "certificat/mainwindowcertif.h"
#include "mission/mainwindowmission.h"

namespace Ui {
class widget;
}

class widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit widget(QWidget *parent = nullptr);
    ~widget();
private slots:


    void on_pushButton_formation_clicked();

    void on_pushButton_contract_clicked();

    void on_pushButton_auditeur_clicked();

    void on_pushButton_certificat_clicked();

    void on_pushButton_mission_clicked();

private:
    Ui::widget *ui;
    gesfor *formation;
    MainWindowContrat *contract;
    MainWindow *auditeur;
    MainWindowcertif *certificat;
    MainWindowmission *mission;
};

#endif // WIDGET_H
