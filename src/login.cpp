#include "../include/agree_gui/login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "../include/agree_gui/paginaprincipale.h"
#include "../include/agree_gui/main_window.hpp"
#include "../include/agree_gui/sc_assistivo.h"




/**********************       DICHIARAZIONE VARIABILI GLOBALI                           *********************/
QString dati::username;
QString dati::password;
QString dati::Nome;
QString dati::Cognome;
QString dati::Data;
QString dati::user_devel;
QString dati::pass_devel;
int dati::profilo;
int dati::password_i;
int flag1;
QString dati::count;
QString dati::sigla;
int dati::nuovo_utente;
int16_t dati::status1=0, dati::command_login=0, dati::command_old_login = 1, dati::flag_sc;





login::login(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::login)
{
 //setto le icone dei pulsanti
//  QPixmap pixmap("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Add.png");
//  QIcon ButtonIcon(pixmap);
//  ui->pushButton_accedi->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Male.png"));
//  ui->pushButton_accedi->setIconSize(pixmap.rect().size());



  ui->setupUi(this);

/**********************       DICHIARO NODO                           *********************/
  ros::NodeHandle n;

/**********************       CREO TOPIC                          *********************/
status_publisher = n.advertise<std_msgs::Int16>("/gui/status", 1000);
command_subscriber = n.subscribe("/gui/command", 1000, &login::callback_log, this); //creo il topic a cui faccio il subscribe



/**********************       COLLEGO DATABASE                            *********************/
  QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
//mydb.setDatabaseName("~/alice/catkin_ws/src/agree_gui/database/Sqlite_prova2");
mydb.setDatabaseName("/home/alice/catkin_ws/src/agree_gui/database/Sqlite_prova2");
//  mydb.setDatabaseName("../src/agree_gui/database/Sqlite_prova2");
mydb.setHostName("alice");
mydb.setUserName("alice");
mydb.setPassword("ali");
this->showMaximized();

  // questo mostra nella prima pagina se il database è connesso
  if (!mydb.open())
     ui->label_status-> setText("Database non connesso");

     else

     ui->label_status ->setText("Database connesso...");

  //placeholder text
   ui->lineEdit_username->setPlaceholderText("Username");
   ui->lineEdit_password->setPlaceholderText("Password");

   dati::user_devel= "aaa";
   dati::pass_devel = "00";

   QSqlQuery query;
   query.prepare("select count (*) from Count");
   query.exec();
   while(query.next())
   {
     query.first();
     dati::count= query.value(0).toString();


   }

/**********************       CONNETTO LOGIN CON PAGINAPRINCIPALE                  *********************/
   Paginaprincipale = new paginaprincipale();

   connect(Paginaprincipale, SIGNAL(ShowMain()), this, SLOT(showlogin()));
   qDebug()<< "conn:" << connect(Paginaprincipale, SIGNAL(ShowMain()), this, SLOT(showlogin()));


   /**********************       CONNETTO LOGIN CON SC_ASSISTIVO                  *********************/
      Sc_assistivo = new sc_assistivo();

      connect(Sc_assistivo, SIGNAL(ShowMain_sc3()), this, SLOT(showlogin_sc3()));
      qDebug()<< "conn:" << connect(Sc_assistivo, SIGNAL(ShowMain_sc3()), this, SLOT(showlogin_sc3()));

}

login::~login()
{
  delete ui;
}

void login::callback_log(const agree_gui::agree_gui_command msg_command) {
  dati::command_login = msg_command.mode;
//cambia_status();
  if((dati::command_old_login) != (dati::command_login)) {
    dati::command_old_login=dati::command_login;
   ROS_INFO("I heard: %d Log Page", dati::command_login);

    if (dati::command_old_login == 1002) {

      this->hide();

   }
    if(dati::command_old_login == 3002) {
      this ->hide();
//      Sc_assistivo = new sc_assistivo();
//                  Sc_assistivo->show();
    }
  }
}
/**********************       MOSTRA LA FINESTRA DI LOGIN                             ********************/
void login::showlogin() {
  show();
  qDebug()<<"sono in prova slot";
}

/**********************       MOSTRA LA FINESTRA DI LOGIN                             ********************/
void login::showlogin_sc3() {
  show();
  qDebug()<<"sono in prova slot sc3";
}
/**********************       FUNZIONE ACCEDI                                         ********************/

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


     if (dati::profilo == 1){
       dati::status1 =1000;
       msg_status.data = dati::status1;
       ROS_INFO ("Push button ################# %d", msg_status.data);
       status_publisher.publish(msg_status);
       dati::flag_sc= 1;
      ros::NodeHandle n;
     n.setParam("scenario", dati::flag_sc);






        }
     //apro una finestra in caso di scenario 3
     else if(dati::profilo==3){




       //SETTO IL FLAG PER FAR CAPIRE CHE È SCENARIO 3

       dati::status1 =3001;
       msg_status.data = dati::status1;
       ROS_INFO ("Push button ################# %d", msg_status.data);
       status_publisher.publish(msg_status);
        dati::flag_sc= 3;
       ros::NodeHandle n;
      n.setParam("scenario", dati::flag_sc);


        }
    }

        if (count >1)
            ui->label_status->setText("Username e Password già presenti nel database");
        if (count<1)
            ui->label_status->setText("username o password non corretti");

}
    if(dati::username == dati::user_devel && dati::password == dati::pass_devel) {
//      dati::status1 =31;
//      msg_status.data = dati::status1;
//      ROS_INFO ("Push button ################# %d", msg_status.data);
//      status_publisher.publish(msg_status);



    }

    }

/**********************       FUNZIONE NUOVA REGISTRAZIONE                            ********************/
void login::on_pushButton_newrec_clicked()
{

  ui->tabWidget->setCurrentWidget(ui->tab_2);
  flag1=1;


}

/**********************       FUNZIONE SALVA NUOVA REGISTRAZIONE                      *********************/

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
      dati::nuovo_utente=1;
  }
     qDebug()<<dati::profilo;

       dati::username= dati::Nome+ dati::Cognome+ dati::sigla+ dati::count;



     QSqlQuery qry;
     QSqlQuery qry2;


if (dati::password == Conferma) {

     if(!qry.exec("insert into Users (Nome,Cognome,Data_di_Nascita, Username,Password,Profilo) values ('"+dati::Nome+"', '"+dati::Cognome+"','"+dati::Data+"', '"+dati::username+"', '"+dati::password+"', '"+Profilo+"')" ))
     {
            QMessageBox ::critical(this,tr("Errore"),tr("Username già presente nel database"));
     }
     else
     {
         QMessageBox ::information(this,tr("Save"),tr("Salvato"));
         QMessageBox::information(this, tr("Information"), QString("Nuovo utente creato. Username : %1  e password:  %2").arg(dati::username).arg(dati::password));
         //mydb.close();
         this ->hide();

 //capire come mai non si aprono più le finestre interessate
         if (dati::profilo == 1){
           dati::status1 = 1000;



         Paginaprincipale  = new paginaprincipale(this);
         connect(Paginaprincipale, SIGNAL(ShowMain()), this, SLOT(showlogin()));
         Paginaprincipale->show();


         std_msgs::Int16 msg;
         msg.data = dati::status1;
         ROS_INFO ("sbagliato? %d", msg.data);
         status_publisher.publish(msg);
         dati::flag_sc= 1;
        ros::NodeHandle n;
       n.setParam("scenario", dati::flag_sc);

        }
        else if(dati::profilo == 3) {

           if(!qry2.exec("insert into Utenti_ass (usernameass, Nome, Cognome, DataNascita) values ('"+dati::username+"', '"+dati::Nome+"', '"+dati::Cognome+"', '"+dati::Data+"')"))
          {
            QMessageBox ::critical(this,tr("Errore"),tr("uff"));
          }
       else {

//           Sc_assistivo = new sc_assistivo(this);
//                       Sc_assistivo->show();


//                       dati::status1 =1;
//                       msg_status.data = dati::status1;
//                       ROS_INFO ("Push button ################# %d", msg_status.data);
//                       status_publisher.publish(msg_status);
                     //SETTO IL FLAG PER FAR CAPIRE CHE È SCENARIO 3
                      dati::flag_sc=3;
                     ros::NodeHandle n;
                    n.setParam("scenario", dati::flag_sc);


          }


         }

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


