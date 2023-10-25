#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "contrat.h"
#include <QMessageBox>
#include <QDebug>
#include <QApplication>
using namespace std;
#include"connection.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    bool test_id,test_price,test_num;
    int contrat_id=ui->lineEdit_id->text().toInt(&test_id);
    QString  contrat_name =ui->lineEdit_name->text();
    QString  contrat_Start =ui->lineEdit_Stime->text();
    QString  contrat_end =ui->lineEdit_Ftime->text();
    QString  contrat_field =ui->lineEdit_field->text();
    double contrat_price =ui->lineEdit_price->text().toDouble(&test_price);
    int contrat_num= ui->lineEdit_num->text().toInt(&test_num);
    QString contrat_email=ui->lineEdit_email->text();
    if(!test_id)
        QMessageBox::critical(this,"id Problem","make sure that all the id is numbers");
    Contrat c(contrat_id,contrat_name,contrat_Start,contrat_end,contrat_field,contrat_price,contrat_num,contrat_email);
    QMessageBox::StandardButton reply=QMessageBox::question(this,"make sure","are you sure you wanna save this file under this id",QMessageBox ::Yes|QMessageBox::No);

    if (reply==QMessageBox::Yes){
        QApplication::quit();}
}
