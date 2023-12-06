
#include "login.h"
#include "ui_login.h"
#include "mainwindowcontrat.h"
#include "ui_mainwindowcontrat.h"
#include "contrat.h"
#include"widget.h"
#include "QMessageBox"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QScreen>
#include <QPixmap>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    int id=ui->contrat_id_login->text().toInt();
    QString pass=ui->contrat_pass_login->text();
    QSqlQuery query;
    //QLabel* label = ui->contrat_log_in_shield;
    //QLabel* label1 = ui->contrat_log_in_shield_2;
    query.prepare("SELECT EMAIL FROM CONTRAT WHERE CODEC = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        QString dbPassword = query.value("EMAIL").toString();

        if (dbPassword != pass) {
            qDebug() << "Incorrect password.";
           // label1->setFixedSize(10000,10000);
           // label->setFixedSize(10000, 10000);
            ui->contrat_pass_login->clear();

        }
        else
        {
            widget *auth =new widget;
            auth->show();

            //label1->setFixedSize(1,1);
            //label->setFixedSize(1, 1);
        }
    } else {
        qDebug() << "Error checking id: make sure taht your id existe" ;
        QMessageBox::warning(this, "Warning", "this user not found.");
       // label1->setFixedSize(10000,10000);
        //label->setFixedSize(10000, 10000);
        ui->contrat_id_login->clear();
    }

}
