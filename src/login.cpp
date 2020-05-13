#include "../include/agree_gui/login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "../include/agree_gui/paginaprincipale.h"
#include "../include/agree_gui/main_window.hpp"



QString dati::username;
QString dati::password;
QString dati::Nome;
QString dati::Cognome;
QString dati::Data;
int dati::profilo;
int dati::password_i;
int flag1;
QString dati::count;
QString dati::sigla;



login::login(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::login)
{
  ui->setupUi(this);



  QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");

mydb.setDatabaseName("/home/alice/catkin_ws/src/agree_gui/database/Sqlite_prova2");
//  mydb.setDatabaseName("../src/agree_gui/database/Sqlite_prova2");







  // questo mostra nella prima pagina se il database è connesso
  if (!mydb.open())
     ui->label_status-> setText("Database non connesso");

     else

     ui->label_status ->setText("Database connesso...");

  //placeholder text
   ui->lineEdit_username->setPlaceholderText("Username");
   ui->lineEdit_password->setPlaceholderText("Password");
   QSqlQuery query;
   query.prepare("select count (*) from Count");
   query.exec();
   while(query.next())
   {
     query.first();
     dati::count= query.value(0).toString();

     qDebug()<< dati::count;
   }
}

login::~login()
{
  delete ui;
}

void login::on_pushButton_accedi_clicked()
{

 //fasi per il login: inserisco username e password da tastiera (variabili che vengono salvate nelle variabili globali così poi da poter essere utilizzate anche nelle altre finestre)
     dati::username= ui->lineEdit_username->text();
     dati::password = ui->lineEdit_password->text();

     // dichiaro una query
    QSqlQuery qry;

 // modo condensato in cui preparazione della query ed esecuzione avvengono simultaneamente : vado a confrontare i  dati del database (nella tabella Users) con quelli immessi da tastiera

    if (qry.exec("select *from Users where Username = '"+dati::username+"' and Password = '"+dati::password+"' "))
    {

 //inizializzo variabile contatore per verificare se ci sono più utenti con la stessa username e password
        int count=0;
        while(qry.next())
        {
            count++;
        }

 // se il contatore si ferma a uno dopo aver passato tutta la tabella in questione allora i dati inseriti sono corretti e posso entrare nella mia pagina
        if (count==1){

            ui->label_status->setText("Username e Password corretti");
            // voglio associare a una variabile il valore dell'elemento Profilo a seconda dell'id_utente appena inserito
             QSqlQuery query;
             query.prepare("select Profilo from Users where Username = '"+dati::username+"' and Password = '"+dati::password+"'");
             query.exec();
             while(query.next()){
                 dati::profilo = query.value(0).toInt();
             }
     qDebug () << dati::profilo;

     if (dati::profilo == 1){
            this->hide();
            Paginaprincipale = new paginaprincipale(this);
            Paginaprincipale -> show();

        }
     //apro una finestra in caso di scenario 3
//     else if(dati::profilo==2){
//         this->hide();
//         Sc_assistivo = new sc_assistivo(this);
//         Sc_assistivo -> show();
//        }
    }

        if (count >1)
            ui->label_status->setText("Username e Password già presenti nel database");
        if (count<1)
            ui->label_status->setText("username o password non corretti");

}

    }


void login::on_pushButton_newrec_clicked()
{

  ui->tabWidget->setCurrentWidget(ui->tab_2);
  flag1=1;


}

void login::on_pushButton_salva_clicked()
{
  QString Nome,Cognome, Username, Password, Conferma, Profilo;
  QString Data;
 dati::Nome= ui->lineEdit_nome->text();
  dati::Cognome = ui->lineEdit_cognome-> text();
  dati::Data =ui->lineEdit_data->text();
 dati::password= ui->lineEdit_password_2->text();
Conferma = ui ->lineEdit_conferma->text();


// dichiaro una variabile stringa, in cui salvo una stringa (numerica) che poi vado a scrivere nel database nella colonna profilo così da identificare l'utente appena loggato e aprire la finestra dedicata
  if(ui->radioButton_terapista->isChecked()) {
      Profilo =QString::number(1); // creo una variabile in qui assegno un valore in base al radio button selezionato. a questo punto riassocio la variabile all'elemento della struct che si riferisce alla colonna della tabella in cui sto scrivendo,mi serve per poter leggere da database i diversi profili e quindi aprire diverse finestre a seconda del profilo selezionato
      dati::profilo = Profilo.toInt();
      dati::sigla= "t";

  }
  else if(ui->radioButton_tecnico ->isChecked()) {
      Profilo =QString::number(2);
      dati::profilo = Profilo.toInt();
      dati::sigla= "tc";

  }
  else if(ui->radioButton_utente ->isChecked()) {
      Profilo=QString::number(3);
      dati::profilo = Profilo.toInt();
      dati::sigla = "u";
  }
     qDebug()<<dati::profilo;

       dati::username= dati::Nome+ dati::Cognome+ dati::sigla+ dati::count;



     QSqlQuery qry;

if (dati::password == Conferma) {

     if(!qry.exec("insert into Users (Nome,Cognome,Data_di_Nascita, Username,Password,Profilo) values ('"+dati::Nome+"', '"+dati::Cognome+"','"+dati::Data+"', '"+dati::username+"', '"+dati::password+"', '"+Profilo+"')" ))
     {
            QMessageBox ::critical(this,tr("Errore"),tr("Username già presente nel database"));
     }
     else
     {
         QMessageBox ::information(this,tr("Save"),tr("Salvato"));
         QMessageBox::information(this, tr("Information"), QString("Nuovo utente creato. Username : %1  e password:  %2").arg(dati::username).arg(dati::password));
         //mydb1.close();
         this ->hide();

 //capire come mai non si aprono più le finestre interessate
         if (dati::profilo == 1){
         Paginaprincipale  = new paginaprincipale(this);
         Paginaprincipale->show();
         //mydb.close();
        }
//        else if(dati::profilo == 3) {
//             Sc_assistivo = new sc_assistivo(this);
//             Sc_assistivo ->show();
//            // mydb.close();
//         }

         }
}
else {
       QMessageBox ::critical(this,tr("Errore"),tr("Le Password non corrispondono"));
       qDebug() << dati::password;
       qDebug() << Conferma;


     }
QSqlQuery qryc;
qryc.prepare("insert into Count (username, cont) values('"+dati::username+"', '"+dati::count+"')");
qryc.exec();

}


