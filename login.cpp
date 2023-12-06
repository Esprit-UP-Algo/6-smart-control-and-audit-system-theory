#include "login.h"
#include "ui_login.h"
#include<QMessageBox>
//#include "arduino.h"
#include "ui_login.h"
#include "login.h"
//#include "connection.h"
//#include "windowsakouhi.h"
//#include "arduino.h"
//#include"widget.h"
//#include "employe.h"
//#include "oublier.h"
//#include "integration.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
 ui->setupUi(this);
       /* int ret = A.connect_arduino();
        switch (ret) {
        case 0:
            qDebug() << "Arduino est disponible et connecté à : " << A.getarduino_port_name();
            break;
        case 1:
            qDebug() << "Arduino est disponible mais non connecté à : " << A.getarduino_port_name();
            break;
        case -1:
            qDebug() << "Arduino n'est pas disponible";
            break;
        }

        QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(update_label()));
*/
  }
login::~login()
{
    delete ui;
}

/*QSerialPort* login::getserial() {
    return A.getserial();
}*/



/* void login::update_label()
{ QByteArray data = A.getserial()->readAll();
    QString receivedData = QString::fromUtf8(data);

    if (!receivedData.isEmpty()) {
        // Supposons que les données série contiennent uniquement l'UID
        QString badgeCode = receivedData.trimmed();
        qDebug() << badgeCode;



        QSqlQuery query;
        query.prepare("SELECT * FROM EMPLOYE WHERE RFID=:badgeCode ");
        query.bindValue(":badgeCode", badgeCode);
        QString badgeCode1 = receivedData;
               badgeCode1.remove(QChar(' '));

        if (query.exec() && query.next()) {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Login réussi avec succès.\n"
                            "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
            this->hide();
                        MaClasse *auth = new MaClasse;
                        auth->show();

                         // Mettre à jour l'écran LCD avec l'identifiant

        } else {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                QObject::tr("Veuillez vérifier le badge.\n"
                            "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        }
    }


      }
*/

void login::on_pushButton_clicked()
{
    QString id = ui->lineEdit_username->text();
       QString mdp = ui->lineEdit_password->text();
      QSqlQuery query;
      //query.prepare("SELECT * FROM employe WHERE IDENTIFIANT=:idy");
       //  query.bindValue(":idy",idi);

         if ( id=="1234567" && mdp=="yy00")
      {
          QMessageBox::information(this, QObject::tr("Login is open"),
                      QObject::tr("Username and passord is correct.\n"
                                  "open."), QMessageBox::Cancel);

          this->hide();
                      integration *auth = new integration;
                      auth->show();
      }
       else {
          QMessageBox::warning(this, QObject::tr("Login is not  open"),
                      QObject::tr("Username and passord is uncorrect.\n"
                                  "try again."), QMessageBox::Cancel);
      }
}
/*void login::on_pushButton_clicked()
{
        // Récupérer le nom d'utilisateur et le mot de passe entrés par l'utilisateur
        QString username = lineEdit_username->text();
        QString password = lineEdit_password->text();

        // Vérifier la connexion
        if (verifierConnexion(username, password)) {
            // Connexion réussie, afficher l'interface principale
            QMessageBox::information(this, "Login Successful", "Welcome to Windowsakouhi!");
        } else {
            // Échec de la connexion, afficher un message d'erreur
            QMessageBox::warning(this, "Login Failed", "Employee not found or incorrect password");
        }
    }*/
/*void login::on_pushButton_2_clicked(QTableView*  employe)
{
    QString identifiant = ui->lineEdit_username->text();

    // Vérifier si l'identifiant est présent dans le tableau des employés
    bool utilisateurTrouve = false;
    Employe E1;  // Déplacer la création de l'objet à l'extérieur de la boucle
    for (int row = 0; row < employe->model()->rowCount(); ++row) {
        QString identifiantDansTableau = employe->model()->data(employe->model()->index(row, 0), Qt::DisplayRole).toString();

        if (identifiantDansTableau == identifiant) {
            utilisateurTrouve = true;

            // Obtenir les questions de sécurité
            QString question1 = employe->model()->data(employe->model()->index(row, 10), Qt::DisplayRole).toString();
            QString question2 = employe->model()->data(employe->model()->index(row, 11), Qt::DisplayRole).toString();
            QString val ="répondre";
            // Demander les réponses à l'utilisateur
            QString reponse1 = QInputDialog::getText(this, val, "Quel est votre plat préféré ?");
            QString reponse2 = QInputDialog::getText(this, val, " Quel était le nom de votre école primaire ?");

            // Vérifier les réponses
            if (reponse1 == question1 && reponse2 == question2) {
                // Réponses correctes, demander le nouveau mot de passe
                QString nouveauMotDePasse = QInputDialog::getText(this, "Nouveau mot de passe", "Entrez votre nouveau mot de passe:");

                E1.setid(identifiant.toInt());
                E1.setmot_de_passe(nouveauMotDePasse);
                bool modificationReussie = E1.modifier();

                if (modificationReussie) {
                    QMessageBox::information(this, "Modification réussie", "Le mot de passe a été modifié avec succès.");
                } else {
                    QMessageBox::warning(this, "Échec de la modification", "La modification du mot de passe a échoué.");
                }
            } else {
                // Réponses incorrectes
                QMessageBox::warning(this, "Réponse incorrecte", "Les réponses aux questions de sécurité sont incorrectes.");
            }

            break;  // Sortir de la boucle après avoir trouvé l'utilisateur
        }
    }

    if (!utilisateurTrouve) {
        // Identifiant introuvable
        QMessageBox::warning(this, "Utilisateur introuvable", "L'identifiant n'a pas été trouvé dans le tableau des employés.");
    }
}*/
