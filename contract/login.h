#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMainWindow>
#include <QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include <QMainWindow>
#include "contrat.h"
#include <QSerialPort>
#include <QTextEdit>
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
private slots :
    void on_pushButton_clicked();
private:
    Ui::login *ui;

};

#endif // LOGIN_H
