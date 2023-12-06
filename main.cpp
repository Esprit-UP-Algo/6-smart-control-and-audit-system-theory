//DONE
#include <QApplication>
#include <QMessageBox>
#include "connexion.h"
#include "formation/gesfor.h"
#include "auditeur/mainwindow.h"
#include "contract/mainwindowcontrat.h"
#include "widget.h"
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    connexion c;
    bool test=c.createconnect();
    gesfor w;
    MainWindowContrat m;
    widget i;
    MainWindow d;
    login l;
    l.show();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
