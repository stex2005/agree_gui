#include "../include/agree_gui/paginaprincipale.h"
#include "ui_paginaprincipale.h"
#include "../include/agree_gui/login.h"
#include "../include/agree_gui/main_window.hpp"
#include "../include/agree_gui/sc_assistivo.h"
#include "../include/agree_gui/matrixwidget.h"
#include "../include/agree_gui/qnode.hpp"
#include <QMessageBox>

int flag;
int prova;
QString dati::codice_id;
QString dati::ind;
QString dati::NomeP, dati::CognomeP, dati::data1;
QString dati::uservecchio;
QString dati::count_act;
QString dati::lato, dati::lato_prec; // 1 destro, 0 sinistro
QString dati::modulo_spalla, dati::modulo_gomito, dati::modulo_polso;
QString dati::modulo_spalla_prec, dati::modulo_gomito_prec, dati::modulo_polso_prec;
QString dati::modulo_eeg, dati::modulo_emg;
QString dati::mano;
QString dati::oi;
QString dati::modulo_prec;
QString dati::modulo_eeg_prec, dati::modulo_emg_prec;
QString dati::oi_prec;
QString dati::mano_prec;
QString dati::data_vecchia;
QString dati::modulo_extra;
QString dati::modulo_prec1;
int     dati::l_eeg_p, dati::l_emg_p;
int     dati::l_m_p;
int     dati::l_oi_p;
QString dati::ex1_prec, dati::ex2_prec, dati::ex3_prec, dati::ex4_prec, dati::ex5_prec, dati::ex6_prec, dati::ex7_prec;
int     dati::lex1, dati::lex2, dati::lex3, dati::lex4, dati::lex5, dati::lex6, dati::lex7;
QString dati::rip1_prec, dati::rip2_prec, dati::rip3_prec, dati::rip4_prec, dati::rip5_prec, dati::rip6_prec, dati::rip7_prec;
QString dati::ogg1_prec, dati::ogg2_prec, dati::ogg3_prec, dati::ogg4_prec, dati::ogg5_prec, dati::ogg6_prec, dati::ogg7_prec;
QString dati::mood;
QString dati::mood_prec;
QString dati::ex1, dati::ex2, dati::ex3, dati::ex4, dati::ex5, dati::ex6, dati::ex7;
QString dati::num_ex1, dati::num_ex2, dati::num_ex3, dati::num_ex4, dati::num_ex5, dati::num_ex6, dati::num_ex7;

QString dati::rip1, dati::rip2, dati::rip3, dati::rip4, dati::rip5, dati::rip6, dati::rip7;
QString dati::next_img;
//using namespace agree_gui;
 SignalHelper *helper;
void callback(const std_msgs::StringConstPtr& str) {
   ROS_INFO("I heard: [%s]", str->data.c_str());
   dati::next_img = str->data.c_str();
 // qDebug()<< dati::next_img;

 // helper->SendSignal();

}
void paginaprincipale::prova_signal() {

  if (dati::next_img == "a") {
 qDebug()<< "sono nella funzione prova_signal";
    helper->SendSignal();
  }
}
paginaprincipale::paginaprincipale(QWidget *parent) :


  QDialog(parent),

  ui(new Ui::paginaprincipale)



{
  using namespace  agree_gui;
qDebug()<< "qui";
   helper = new SignalHelper();
   prova_signal();
  connect(helper, SIGNAL(SignalName()),this, SLOT(next_img()));
  ui->setupUi(this);
  ui->tabWidget->setCurrentWidget(ui->tab);
  ui->stackedWidget->setCurrentWidget(ui->page_3);
//  MatrixWidget * matrix = new MatrixWidget (this);
     ui->verticalLayout->addWidget(matrix);
     // ho aggiunto questi
     ros::NodeHandle n;
chatter_publisher = n.advertise<std_msgs::String>("/status", 1000);
//definisco topic

//definisco topic da cui faccio subscribe

 command_subscriber = n.subscribe("/command", 1000, callback); //creo il topic a cui faccio il subscribe


//connetto combobox con combo box
connect(ui->comboBox_ex1, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo()));
connect(ui->comboBox_ex2, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo()));
connect(ui->comboBox_ex3, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo()));
connect(ui->comboBox_ex4, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo()));
connect(ui->comboBox_ex5, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo()));
connect(ui->comboBox_ex6, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo()));
connect(ui->comboBox_ex7, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo()));

//connect(ui->lineEdit_ex1, SIGNAL(TextChanged(QString)),this, SLOT(update_tempo_terapia(QString)));


connect(ui->lineEdit_ex1, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_terapia()));
connect(ui->lineEdit_ex2, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_terapia()));
connect(ui->lineEdit_ex3, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_terapia()));
connect(ui->lineEdit_ex4, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_terapia()));
connect(ui->lineEdit_ex5, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_terapia()));
connect(ui->lineEdit_ex6, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_terapia()));
connect(ui->lineEdit_ex7, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_terapia()));

connect(ui->checkBox_ex1, SIGNAL(clicked(bool)), this, SLOT(enable_combo_ex()));
connect(ui->checkBox_ex2, SIGNAL(clicked(bool)), this, SLOT(enable_combo_ex()));
connect(ui->checkBox_ex3, SIGNAL(clicked(bool)), this, SLOT(enable_combo_ex()));
connect(ui->checkBox_ex4, SIGNAL(clicked(bool)), this, SLOT(enable_combo_ex()));
connect(ui->checkBox_ex5, SIGNAL(clicked(bool)), this, SLOT(enable_combo_ex()));
connect(ui->checkBox_ex6, SIGNAL(clicked(bool)), this, SLOT(enable_combo_ex()));
connect(ui->checkBox_7, SIGNAL(clicked(bool)), this, SLOT(enable_combo_ex()));

timer = new QTimer(this);

// setup signal and slot
connect(timer, SIGNAL(timeout()),
      this, SLOT(prova_signal()));

// msec






 // prova immagini
  QPixmap pic1("/home/alice/catkin_ws/src/agree_gui/resources/images/img/modalità/mob_pass.png");
  ui->label_pass->setPixmap(pic1);

    QPixmap pic2("/home/alice/catkin_ws/src/agree_gui/resources/images/img/modalità/trigger.png");
    ui->label_trigger->setPixmap(pic2);

    QPixmap pic3("/home/alice/catkin_ws/src/agree_gui/resources/images/img/modalità/asasn.png");
    ui->label_asasne->setPixmap(pic3);

    QPixmap pic4("/home/alice/catkin_ws/src/agree_gui/resources/images/img/modalità/antg.png");
    ui->label_antig->setPixmap(pic4);

    QPixmap pic5("/home/alice/catkin_ws/src/agree_gui/resources/images/img/modalità/challenging.png");
    ui->label_chall->setPixmap(pic5);


  //creo la data
  QDate data;
data= QDate::currentDate();
 dati::data1= data.toString(Qt::ISODate);
ui->label_date->setText(data.toString());


  QSqlDatabase mydb2 = QSqlDatabase::database();
  QSqlQuery * qry3 = new QSqlQuery(mydb2);
  qry3 -> prepare("select Nome, Cognome from Users where Username = '"+dati::username+"' and Password = '"+dati::password+"'" );
  qry3 -> exec();
  while(qry3->next()){

     ui->label_status->setText(qry3->value(0).toString() + " " +  qry3->value(1).toString());
}
}

paginaprincipale::~paginaprincipale()
{
  delete ui;


}

void paginaprincipale::on_pushButton_nuovopaziente_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_4);
     flag=1; //nuovo paziente
    ui->lineEdit_nome->clear();
    ui-> lineEdit_cognome -> clear();
    ui-> lineEdit_datanascita ->clear();
    ui-> lineEdit_patologia -> clear();
    ui->lineEdit_storiaclinica ->clear();
    ui->lineEdit_braccio->clear();
    ui ->lineEdit_avambraccio->clear();
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

void paginaprincipale::on_pushButton_salva_clicked()
{

    QString Data, Sesso, Patologia, Lato, storiaclinica,Lunghezza_braccio, Lunghezza_avambraccio,sigla;
    dati::NomeP = ui->lineEdit_nome-> text();
    dati::CognomeP = ui-> lineEdit_cognome -> text();
    Data = ui-> lineEdit_datanascita -> text();
    Sesso = ui-> comboBox_sesso -> currentText();
    Patologia = ui-> lineEdit_patologia -> text();
    Lato = ui-> comboBox_latodominante-> currentText();
    storiaclinica = ui->lineEdit_storiaclinica ->text();
    Lunghezza_braccio = ui->lineEdit_braccio -> text();
  //  float Lunghezza_braccio_f = Lunghezza_braccio.toFloat();
    Lunghezza_avambraccio = ui->lineEdit_avambraccio-> text();
   // float Lunghezza_avambraccio_f = Lunghezza_avambraccio.toFloat();
    dati::sigla = "p";
  //   dati::codice_id= dati::NomeP + dati::CognomeP + sigla+dati::count;
 if(flag==1)
   // controllo unicità paziente
 { QSqlQuery qry11;
   qry11.prepare("select * from Pazienti where NomePaziente = '"+dati::NomeP+"'and  Cognome = '"+dati::CognomeP+"' ");
   qry11.exec();
   if (qry11.exec()){
   int cont=0;
   while(qry11.next())
   {
       cont++;
   }
// se paziente unico lo salvo
   if (cont==0) {
     if (!(dati::NomeP=="") || !(dati::CognomeP == "")){

  dati::codice_id= dati::NomeP + dati::CognomeP + dati::sigla+dati::count;
    QSqlQuery qry;
   qry.prepare("insert into Pazienti (Codice_ID, UsernameDOC, NomePaziente, Cognome, DatadiNascita, Patologia, Sesso, Lato_paretico, LunghezzaBraccio, LunghezzaAvambraccio, StoriaClinica) values ('"+dati::codice_id+"', '"+dati::username+"', '"+dati::NomeP+"', '"+dati::CognomeP+"','"+Data+"', '"+Patologia+"', '"+Sesso+"', '"+Lato+"', '"+Lunghezza_braccio+"', '"+Lunghezza_avambraccio+"', '"+storiaclinica+"')" );
   if(qry.exec()) {
// se lo salvo lo comunico e copio username in tabella count
      QMessageBox ::information(this,tr("Salvataggio"),tr(" Paziente Salvato Correttamente"));
      ui->stackedWidget->setCurrentWidget(ui->page_3);
      QSqlQuery qryc;
      qryc.prepare("insert into Count (username,cont) values('"+dati::codice_id+"', '"+dati::count+"')");
      qryc.exec();
      }
   else qDebug()<<qry.lastError();
   }
     else {
       QMessageBox::warning(this,tr("Attenzione"), tr("Inserire Nome e Cognome del paziente!"));
     }
   }
// se esiste già non è eseguo la  query
      else if (cont==1)
      {
        QMessageBox ::critical(this,tr("Errore"),tr("Attenzione: Paziente già presente nel database"));
      }
    }
 else qDebug()<<qry11.lastError();
   }
 if (flag==2) {
   qDebug()<<dati::count_act;
  dati::codice_id= dati::NomeP+ dati::CognomeP+ dati::sigla+ dati::count_act;
  qDebug()<<dati::codice_id;

      QSqlQuery qry6;
      qry6.prepare("update Pazienti set Codice_ID= '"+dati::codice_id+"', NomePaziente ='"+dati::NomeP+"', Cognome= '"+dati::CognomeP+"', DatadiNascita= '"+Data+"',  Patologia = '"+Patologia+"', Sesso='"+Sesso+"', Lato_paretico = '"+Lato+"', StoriaClinica = '"+storiaclinica+"', LunghezzaBraccio ='"+Lunghezza_braccio+"', LunghezzaAvambraccio = '"+Lunghezza_avambraccio+"' where Codice_ID = '"+dati::ind+"'");
      if (qry6.exec())
      {
        QMessageBox ::information(this,tr("Modifica"),tr(" Dati del Paziente Modificati Correttamente"));
        QMessageBox::information(this, tr("Information"), tr("Premere Elenco Pazienti per aggiornare il database dei Pazienti"));
        ui->stackedWidget->setCurrentWidget(ui->page_3);

        QSqlQuery qry12;
        qry12.prepare("update Count set username= '"+dati::codice_id+"'  where cont = '"+dati::count_act+"'");
        qry12.exec();
      }
      else {
        QMessageBox ::critical(this,tr("Errore"),tr("bo3"));

      }
    }
}

void paginaprincipale::on_pushButton_elencoPazienti_clicked()
{    prova_signal();
  //carico la tabella dei pazienti
      QSqlQueryModel *model = new QSqlQueryModel();
      QSqlQuery * qry1 = new QSqlQuery(mydb2);
      qry1 -> prepare("select Codice_ID, NomePaziente, Cognome, DatadiNascita, Patologia, Sesso, Lato_paretico, LunghezzaBraccio, LunghezzaAvambraccio, StoriaClinica from Pazienti where UsernameDOC = '"+dati::username+"' order by Cognome  asc");
      qry1 -> exec();
      if(qry1->exec()) {
      model -> setQuery(*qry1);
      ui->tableView_database->setModel(model);
      ui->tableView_database->resizeColumnsToContents();

    //  qDebug() << (model->rowCount());
      }
      else qDebug()<<qry1->lastError();
}

void paginaprincipale::on_tableView_database_activated(const QModelIndex &index)
{
     dati::ind= ui-> tableView_database->model()->data(index).toString();
 flag= 3; //paziente selezionato
}

void paginaprincipale::on_pushButton_eliminapaziente_clicked()
{   if(flag==3)
  {
    QSqlQuery qry7;
    qry7.prepare("select NomePaziente, Cognome from Pazienti  where Codice_ID= '"+dati::ind+"'");
    qry7.exec();
    while(qry7.next())
    {
      dati::NomeP = qry7.value(0).toString();
      dati::CognomeP = qry7.value(1).toString();
//      QMessageBox msgBox;
//      msgBox.setText("The document has been modified.");
//      msgBox.setInformativeText("Do you want to save your changes?");
//      msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
//      msgBox.setDefaultButton(QMessageBox::Save);
//      int ret = msgBox.exec();
//      QMessageBox risposta(QMessageBox::Question ,tr("Conferma"), tr("Si è scelto eliminare i dati relativi al paziente : %1 %2") .arg(dati::NomeP).arg(dati::CognomeP), QMessageBox::Yes | QMessageBox::No,this);
//      QAbstractButton* pButtonYes =    risposta.setButtonText(QMessageBox::Yes, tr("Conferma"));
//      QAbstractButton* pButtonNo =     risposta.setButtonText(QMessageBox::No, tr("No"));
    //      if (risposta.exec()==QMessageBox::Yes)
      QMessageBox risposta;
      risposta.setText(tr("Si è scelto eliminare i dati relativi al paziente : %1 %2") .arg(dati::NomeP).arg(dati::CognomeP));
      QAbstractButton* pButtonYes = risposta.addButton(tr("Conferma"), QMessageBox::YesRole);
      QAbstractButton* pButtonNo =  risposta.addButton(tr("No"), QMessageBox::NoRole);
      risposta.exec();
      if(risposta.clickedButton()==pButtonYes)
      {
        QSqlQuery qry4;
        qry4.prepare("delete from Pazienti where Codice_ID ='"+dati::ind+"'");
        qry4.exec();

        QSqlQuery qry5;
        qry5.prepare("delete from Parametri_Paziente where Codice_ID ='"+dati::ind+"'");
        qry5.exec();
        QMessageBox ::information(this,tr("Eliminazione"),tr("Paziente Eliminato"));
        QMessageBox::information(this, tr("Information"), tr("Premere Elenco Pazienti per aggiornare il database dei Pazienti"));

      }
      else if(risposta.clickedButton()==pButtonNo)
      {
        ui->stackedWidget->setCurrentWidget(ui->page_3);
      }
    }

  }
  else
  {
    QMessageBox ::warning(this,tr("Attenzione"),tr("Selezionare con doppio click il paziente che si vuole eliminare"));
  }
}

void paginaprincipale::on_pushButton_modifica_clicked()
{ if (flag==3)
  {
 ui->stackedWidget->setCurrentWidget(ui->page_4);

 QSqlQuery qry5;
    qry5.prepare("select * from Pazienti where Codice_ID = '"+dati::ind+"'");
    if (qry5.exec())
    {
      while(qry5.next())
      { flag=2; //modifica paziente
        ui->lineEdit_nome ->setText(qry5.value(2).toString());
        ui->lineEdit_cognome->setText(qry5.value(3).toString());
        ui->lineEdit_datanascita ->setText(qry5.value(4).toString());
        ui->comboBox_sesso->setCurrentText(qry5.value(6).toString());
        ui->lineEdit_patologia ->setText(qry5.value(5).toString());
        ui->comboBox_latodominante->setCurrentText(qry5.value(7).toString());
        ui->lineEdit_storiaclinica ->setText(qry5.value(10).toString());
        ui->lineEdit_braccio->setText(qry5.value(8).toString());
        ui->lineEdit_avambraccio->setText(qry5.value(9).toString());
            QSqlQuery prova1;
         prova1.prepare("select cont from Count where username = '"+dati::ind+"'");
         prova1.exec();
         while(prova1.next())
         { dati::count_act= prova1.value(0).toString();
           qDebug()<< dati::count_act;
         }
      }
    }

      else {
          QMessageBox ::critical(this,tr("Errore"),tr("boh2"));
      }
  }
  else {
    QMessageBox ::warning(this,tr("Attenzione"),tr("Selezionare con doppio click il paziente che si vuole Modificare"));

  }
    }

void paginaprincipale::on_pushButton_utente_clicked()
{
  ui->stackedWidget->setCurrentWidget(ui->page_5);
     QSqlQuery qry3;
     qry3.prepare("select * from Users where Username = '"+dati::username+"'");
     if (qry3.exec())
     {
       while(qry3.next())
       {
         ui->lineEdit_nome_2 ->setText(qry3.value(0).toString());
         ui->lineEdit_cognome_2->setText(qry3.value(1).toString());
         ui->lineEdit_data ->setText(qry3.value(2).toString());
         ui->lineEdit_password_2 ->setText(qry3.value(4).toString());
         ui->lineEdit_conferma ->setText(qry3.value(4).toString());
         dati::uservecchio=dati::username;
         QSqlQuery prova1;
         prova1.prepare("select cont from Count where username = '"+dati::username+"'");
         prova1.exec();
         while(prova1.next())
        {
           dati::count_act= prova1.value(0).toString();
           qDebug()<< dati::count_act;
      }
      }
     }
       else
       {
           QMessageBox ::critical(this,tr("Errore"),tr("boh3"));
       }
}

void paginaprincipale::on_pushButton_salva_2_clicked()
{
  QSqlQuery qry6;
  QString Profilo;
  dati::Nome = ui->lineEdit_nome_2-> text();
  dati::Cognome = ui->lineEdit_cognome_2->text();
  dati::Data = ui->lineEdit_data->text();
  if(ui->radioButton_terapista->isChecked())
  {
      Profilo =QString::number(1); // creo una variabile in qui assegno un valore in base al radio button selezionato. a questo punto riassocio la variabile all'elemento della struct che si riferisce alla colonna della tabella in cui sto scrivendo,mi serve per poter leggere da database i diversi profili e quindi aprire diverse finestre a seconda del profilo selezionato
      dati::profilo = Profilo.toInt();
      dati::sigla= "t";
  }
  else if(ui->radioButton_tecnico ->isChecked())
  {
      Profilo =QString::number(2);
      dati::profilo = Profilo.toInt();
      dati::sigla= "tc";
  }
  else if(ui->radioButton_utente ->isChecked())
  {
      Profilo=QString::number(3);
      dati::profilo = Profilo.toInt();
      dati::sigla = "u";
  }
  dati::username = dati::Nome+ dati::Cognome + dati::sigla + dati::count_act;

  qry6.prepare("update Users set Username= '"+dati::username+"', Nome ='"+dati::Nome+"', Cognome= '"+dati::Cognome+"', Data_di_Nascita= '"+dati::Data+"',  Password= '"+dati::password+"' where Username = '"+dati::uservecchio+"'");
  if (qry6.exec())
  {
    QMessageBox ::information(this,tr("Modifica"),tr("Dati Utente Modificati Correttamente"));
    ui->stackedWidget->setCurrentWidget(ui->page_3);

    qDebug() << dati::username;
    QSqlQuery qry12;
    qry12.prepare("update Count set username= '"+dati::username+"'  where cont = '"+dati::count_act+"'");
    qry12.exec();
    if(qry12.exec())
    {
      QSqlQuery prova2;
      prova2.prepare("update Pazienti set usernameDoc = '"+dati::username+"' where UsernameDoc = '"+dati::uservecchio+"'" );
      prova2.exec();
    }
  }
  else
  {
    QMessageBox ::critical(this,tr("Errore"),tr("bo3"));
  }
}

void paginaprincipale::on_pushButton_vestizioneAgree_clicked()
{
  if (flag==3)
  {
    qDebug()<< dati::ind;
    QSqlQuery qry7;
    qry7.prepare("select NomePaziente, Cognome from Pazienti  where codice_ID= '"+dati::ind+"'");
    qry7.exec();
    while(qry7.next())
    {
      dati::NomeP = qry7.value(0).toString();
      dati::CognomeP = qry7.value(1).toString();
      ui->label_status2->setText("Paziente: " + qry7.value(0).toString()+ " "+ qry7.value(1).toString());
      QMessageBox risposta;
      risposta.setText(tr("Si è scelto di iniziare la sessione di terapia del paziente : %1 %2") .arg(dati::NomeP).arg(dati::CognomeP));
      QAbstractButton* pButtonYes = risposta.addButton(tr("Conferma"), QMessageBox::YesRole);
      QAbstractButton* pButtonNo =  risposta.addButton(tr("No"), QMessageBox::NoRole);
      risposta.exec();
      if(risposta.clickedButton()==pButtonYes)
     // QMessageBox::StandardButton risposta= QMessageBox::question(this,tr("Conferma"), tr("Si è scelto di iniziare la sessione di terapia del paziente : %1 %2") .arg(dati::NomeP).arg(dati::CognomeP), QMessageBox::Yes | QMessageBox::No);
     // if (risposta==QMessageBox::Yes)
      {
        QSqlQuery selezione; // selezioni l'ultima riga salvata con questo codice id
        selezione.prepare ("select *  from Parametri_Paziente where Codice_ID = '"+dati::ind+"' order by Data_acquisizione desc limit 1");
        if (selezione.exec())
        {
          while(selezione.next())
          {
            QString FESm2, FESM2, AASm2, AASM2, RIESm2, RIESM2, Gm2, GM2, Pm2, PM2;
            dati::data_vecchia = selezione.value(2).toString();
            FESm2 = selezione.value(3).toString();
            FESM2 = selezione.value(4).toString();
            AASm2 = selezione.value(5).toString();
            AASM2 = selezione.value(6).toString();
            RIESm2 = selezione.value(7).toString();
            RIESM2 = selezione.value(8).toString();
            Gm2 = selezione.value(9).toString();
            GM2 = selezione.value(10).toString();
            Pm2 = selezione.value(11).toString();
            PM2 = selezione.value(12).toString();
            dati::lato_prec= selezione.value(13).toString();
            dati::modulo_spalla_prec = selezione.value(14).toString();
            dati::modulo_gomito_prec = selezione.value(15).toString();
            dati::modulo_polso_prec = selezione.value(16).toString();
            dati::modulo_eeg_prec = selezione.value(17).toString();
            dati::modulo_emg_prec = selezione.value(18).toString();
            dati::mano_prec = selezione.value(19).toString();
            dati::oi_prec = selezione.value(20).toString();
            dati::mood_prec = selezione.value(21).toString();
            dati::l_eeg_p = dati::modulo_eeg_prec.length();
            dati::l_emg_p = dati::modulo_emg_prec.length();
            dati::l_m_p = dati::mano_prec.length();
            dati::l_oi_p = dati::oi_prec.length();
            dati::ex1_prec= selezione.value(22).toString();
            dati::rip1_prec = selezione.value(23).toString();
            dati::ogg1_prec = selezione.value(24).toString();
            dati::ex2_prec = selezione.value(25).toString();
            dati::rip2_prec = selezione.value(26).toString();
            dati::ogg2_prec = selezione.value(27).toString();
            dati::ex3_prec = selezione.value(28).toString();
            dati::rip3_prec = selezione.value(29).toString();
            dati::ogg3_prec = selezione.value(30).toString();
            dati::ex4_prec = selezione.value(31).toString();
            dati::rip4_prec = selezione.value(32).toString();
            dati::ogg4_prec = selezione.value(33).toString();
            dati::ex5_prec = selezione.value(34).toString();
            dati::rip5_prec = selezione.value(35).toString();
            dati::ogg5_prec = selezione.value(36).toString();
            dati::ex6_prec = selezione.value(37).toString();
            dati::rip6_prec = selezione.value(38).toString();
            dati::ogg6_prec = selezione.value(39).toString();
            dati::ex7_prec= selezione.value(40).toString();
            dati::rip7_prec = selezione.value(41).toString();
            dati::ogg7_prec = selezione.value(42).toString();
            dati::lex1 = dati::ex1_prec.length();
            dati::lex2 = dati::ex2_prec.length();
            dati::lex3 = dati::ex3_prec.length();
            dati::lex4 = dati::ex4_prec.length();
            dati::lex5 = dati::ex5_prec.length();
            dati::lex6 = dati::ex6_prec.length();
            dati::lex7 = dati::ex7_prec.length();


            ui->lineEdit_flessospallamin->setText(FESm2);
            ui->lineEdit_flessospallamax->setText(FESM2);
            ui->lineEdit_adduzionespallamin->setText(AASm2);
            ui->lineEdit_adduzionespallamax->setText(AASM2);
            ui->lineEdit_rotazionespallamin->setText(RIESm2);
            ui->lineEdit_rotazionespallamax->setText(RIESM2);
            ui->lineEdit_gomitomin->setText(Gm2);
            ui->lineEdit_gomitomax->setText(GM2);
            ui ->lineEdit_polomin->setText(Pm2);
            ui->lineEdit_polsomax->setText(PM2);

         flag = 4; //rilevo la presenza di una configurazione precedente
        }
        }
        if (!(flag==4))
        {
          QString FESm1, FESM1, AASm1, AASM1, RIESm1, RIESM1,Gm1, GM1, Pm1,PM1;
               FESm1= ui->lineEdit_flessospallamin->placeholderText();
               FESM1 = ui->lineEdit_flessospallamax->placeholderText();
               AASm1= ui->lineEdit_adduzionespallamin->placeholderText();
               AASM1 = ui->lineEdit_adduzionespallamax->placeholderText();
               RIESm1= ui->lineEdit_rotazionespallamin->placeholderText();
               RIESM1 = ui->lineEdit_rotazionespallamax->placeholderText();
               Gm1= ui->lineEdit_gomitomin->placeholderText();
               GM1 = ui->lineEdit_gomitomax->placeholderText();
               Pm1 = ui ->lineEdit_polomin->placeholderText();
               PM1 = ui->lineEdit_polsomax->placeholderText();
                ui->lineEdit_flessospallamin->setText(FESm1);
                ui->lineEdit_flessospallamax->setText(FESM1);
                ui->lineEdit_adduzionespallamin->setText(AASm1);
                ui->lineEdit_adduzionespallamax->setText(AASM1);
                ui->lineEdit_rotazionespallamin->setText(RIESm1);
                ui->lineEdit_rotazionespallamax->setText(RIESM1);
                ui->lineEdit_gomitomin->setText(Gm1);
                ui->lineEdit_gomitomax->setText(GM1);
                ui ->lineEdit_polomin->setText(Pm1);
                ui->lineEdit_polsomax->setText(PM1);


                QSqlQuery insert;
                insert.prepare("insert into Parametri_Paziente (Codice_ID, UsernameDoc, Data_acquisizione) values ('"+dati::ind+"', '"+dati::username+"', '"+dati::data1+"')");
                if (insert.exec())
                {
                  ui->tabWidget->setCurrentWidget(ui->tab_2);
                  ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);
                }
             }
        }
 if (flag==4)
 {

     QSqlQuery insert;
     insert.prepare("insert into Parametri_Paziente (Codice_ID, UsernameDoc, Data_acquisizione) values ('"+dati::ind+"', '"+dati::username+"', '"+dati::data1+"')");

     if (insert.exec())
     {        // if (flag==4)
      // {  ui->tabWidget_2->setCurrentWidget(ui->tab_controllo);
         if(dati::lato_prec == "0") ui->checkBox_sinistro->setChecked(true);
         else if (dati::lato_prec == "1") ui->checkBox_destro->setChecked(true);

         if(dati::modulo_spalla_prec=="1" && dati::modulo_gomito_prec=="0" && dati::modulo_polso_prec=="0")
         {
           dati::modulo_prec1= "Spalla";

           ui->checkBox_spalla->setChecked(true);
         }
         if (dati::modulo_gomito_prec== "1" && dati::modulo_polso_prec =="0") {
           dati::modulo_prec1 = "Spalla e Gomito";

           ui-> checkBox_gomito ->setChecked(true);
         }
         if (dati::modulo_polso_prec=="1") {
           dati::modulo_prec1 = "Spalla, Gomito e Polso";

           ui->checkBox_polso->setChecked(true);
         }

                  if (dati::modulo_emg_prec=="1")
                  {
                    ui->checkBox_emg_2->setChecked(true);
                  }
                  else if(dati::modulo_eeg_prec=="1")
                  {
                    ui->checkBox_eeg_2->setChecked(true);
                  }
                  else {
                    ui->checkBox_eeg_2->setChecked(false);
                    ui->checkBox_emg_2->setChecked(false);
                  }
                  if(!(dati::l_m_p==0))
                  {
                    ui->checkBox_MAP_2->setChecked(true);
                    prova= 5;
                  }
                  else {
                    ui->checkBox_MAP_2->setChecked(false);
                  }
//                  if(!(dati::l_oi_p==0))
//                  {
//                    ui->checkBox_oi_2->setChecked(true);
//                  }
//                  else {
//                    ui->checkBox_oi_2->setChecked(false);
//                  }

       }
       ui->tabWidget->setCurrentWidget(ui->tab_2);
       ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);
     }


      else if(risposta.clickedButton()==pButtonNo){
        ui->tabWidget->setCurrentWidget(ui->tab);
        ui->stackedWidget->setCurrentWidget(ui->page_3);
      }
    //}
}
  }
  else
  {
      QMessageBox ::warning(this,tr("Attenzione"),tr("Selezionare con doppio click il paziente di cui si vuole iniziare la seduta riabilitativa"));

  }
}

void paginaprincipale::on_pushButton_home_clicked()
{
      ui->tabWidget->setCurrentWidget(ui->tab);
      ui->stackedWidget->setCurrentWidget(ui->page_3);
}

void paginaprincipale::on_pushButton_salta_clicked()
{    qDebug() << sel_tut;
     if(curTut<sel_tut.size()) {
       key2 = sel_tut.at(curTut);
       qDebug() << key2;
       if(TutInfoMap.find(key2) != TutInfoMap.end()) {
         TutInfo &one2 = TutInfoMap[key2];
         if(curImg < one2.img.size()){
           ui->label_img_tut -> setPixmap(one2.img.at(curImg));
           curImg ++;
         }
         if(curImg == one2.img.size()) {
           curImg =0;
           curTut ++;
         }
       }
     }

}

void paginaprincipale::on_pushButton_salvaconf_clicked()
{
    QString FESm1, FESM1, AASm1, AASM1, RIESm1, RIESM1,Gm1, GM1, Pm1,PM1;
    FESm1= ui->lineEdit_flessospallamin->text();
    FESM1 = ui->lineEdit_flessospallamax->text();
    AASm1= ui->lineEdit_adduzionespallamin->text();
    AASM1 = ui->lineEdit_flessospallamax->text();
    RIESm1= ui->lineEdit_rotazionespallamin->text();
    RIESM1 = ui->lineEdit_rotazionespallamax->text();
    Gm1= ui->lineEdit_gomitomin->text();
    GM1 = ui->lineEdit_gomitomax->text();
    Pm1 = ui ->lineEdit_polomin->text();
    PM1= ui->lineEdit_polsomax->text();

    QSqlQuery qry9;
  // qry9.prepare("insert into Parametri_Paziente (Codice_ID, UsernameDOC, Data_acquisizione, ROM1_min, ROM1_max, ROM2_min, ROM2_max, ROM3_min, ROM3_max, ROM4_min, ROM4_max, ROM5_min, ROM5_max) values('"+dati::ind+"', '"+dati::username+"', '"+dati::data1+"','"+FESm1+"', '"+FESM1+"', '"+AASm1+"', '"+AASM1+"', '"+RIESm1+"', '"+RIESM1+"', '"+Gm1+"', '"+GM1+"', '"+Pm1+"', '"+PM1+"') ");
    qry9.prepare("update Parametri_Paziente set ROM1_min = '"+FESm1+"', ROM1_max= '"+FESM1+"', ROM2_min= '"+AASm1+"', ROM2_max= '"+AASM1+"', ROM3_min= '"+RIESm1+"', ROM3_max= '"+RIESM1+"', ROM4_min= '"+Gm1+"', ROM4_max= '"+GM1+"', ROM5_min = '"+Pm1+"', ROM5_max= '"+PM1+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    qry9.exec();
    if (qry9.exec())
        {
         QMessageBox ::information(this,tr("Salvato"),tr("Parametri Salvati"));
         ui->tabWidget_2->setCurrentWidget(ui->tab_controllo);
        // aggiungo questo:

//pubblico che ho salvato i rom sul chatter
         ss << "ho salvato i rom " ; // al posto di questa devo leggere qnode.variabile da dove l'ho modificata
         msg.data = ss.str();
       chatter_publisher.publish(msg);

         //agree_gui::QNode status << "ho salvato la configurazione dedi rom";
       }
       else {
          QMessageBox ::critical(this,tr("Errore"),tr("bo3"));
        }
//        if (flag==4)
//        {  ui->tabWidget_2->setCurrentWidget(ui->tab_controllo);
//          if(dati::lato_prec == "0") ui->checkBox_sinistro->setChecked(true);
//          else if (dati::lato_prec == "1") ui->checkBox_destro->setChecked(true);

//          if(dati::modulo_spalla_prec=="1" && dati::modulo_gomito_prec=="0" && dati::modulo_polso_prec=="0")
//          {
//            dati::modulo_prec1= "Spalla";

//            ui->checkBox_spalla->setChecked(true);
//          }
//          if (dati::modulo_gomito_prec== "1" && dati::modulo_polso_prec =="0") {
//            dati::modulo_prec1 = "Spalla e Gomito";

//            ui-> checkBox_gomito ->setChecked(true);
//          }
//          if (dati::modulo_polso_prec=="1") {
//            dati::modulo_prec1 = "Spalla, Gomito e Polso";

//            ui->checkBox_polso->setChecked(true);
//          }

//                   if (dati::modulo_emg_prec=="1")
//                   {
//                     ui->checkBox_emg_2->setChecked(true);
//                   }
//                   else if(dati::modulo_eeg_prec=="1")
//                   {
//                     ui->checkBox_eeg_2->setChecked(true);
//                   }
//                   else {
//                     ui->checkBox_eeg_2->setChecked(false);
//                     ui->checkBox_emg_2->setChecked(false);
//                   }
//                   if(!(dati::l_m_p==0))
//                   {
//                     ui->checkBox_MAP_2->setChecked(true);
//                     prova= 5;
//                   }
//                   else {
//                     ui->checkBox_MAP_2->setChecked(false);
//                   }
//                   if(!(dati::l_oi_p==0))
//                   {
//                     ui->checkBox_oi_2->setChecked(true);
//                   }
//                   else {
//                     ui->checkBox_oi_2->setChecked(false);
//                   }

//        }
}

void paginaprincipale::on_pushButton_cerca_3_clicked()
{
    QString Ricerca;
    Ricerca= ui->lineEdit_cercapaziente_3->text();

    QSqlQueryModel *model1 = new QSqlQueryModel();
     QSqlQuery * qry10 = new QSqlQuery(mydb2);
      qry10->prepare("Select * from Pazienti where Cognome= '"+Ricerca+"'");
     qry10 -> exec();
     model1 -> setQuery(*qry10);
     ui->tableView_database->setModel(model1);
     qDebug() << (model1->rowCount());
}

//void paginaprincipale::on_pushButton_save_clicked()
//{
//    if(ui->checkBox_eeg->isChecked())
//    {
//      dati::modulo_extra= "1";
//      QSqlQuery moduli;
//      moduli.prepare("update Parametri_Paziente set EEG='"+dati::modulo_extra+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");

//     moduli.exec();

//            if (moduli.exec())
//            {

//           QMessageBox ::information(this,tr("Salvato"),tr("Configurazione del Modulo Extra EEG salvata"));
//           ui->checkBox_eeg->setChecked(false);

//           }
//           else {
//              QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
//            }

//    }
//    if(ui->checkBox_emg->isChecked())
//    {
//      dati::modulo_extra= "1";
//      QSqlQuery moduli;
//      moduli.prepare("update Parametri_Paziente set EMG='"+dati::modulo_extra+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");

//     moduli.exec();

//            if (moduli.exec())
//            {

//             QMessageBox ::information(this,tr("Salvato"),tr("Configurazione del Modulo Extra EMG salvata"));
//              ui->checkBox_emg->setChecked(false);
//           }
//           else {
//              QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
//            }
//    }
//    if(ui->checkBox_MAP->isChecked() ||  (prova == 5))
//    {
//      //|| (dati::modulo_prec== "S-P-G")
//      if(dati::modulo_polso == "1")
//      {
//      dati::mano = "1";
//     QSqlQuery moduli;
//      moduli.prepare("update Parametri_Paziente set Mano='"+dati::mano+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");

//     moduli.exec();

//            if (moduli.exec())
//            {

//            QMessageBox ::information(this,tr("Salvato"),tr("Configurazione del Modulo Extra MAP salvata"));
//            ui->checkBox_MAP->setChecked(false);
//           }
//           else {
//              QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
//            }
//      }
// //|| (dati::modulo_prec== "S-G") || (dati::modulo_prec=="S")

//      else if (dati::modulo_polso == "0" ) {
//        qDebug()<< "qui";
//        QMessageBox::StandardButton risposta= QMessageBox::question(this,tr("Attenzione"), tr("Il modulo extra: Mano non può essere attivato se la configurazione dei moduli moduli meccanici non comprende anche il Modulo : Polso. Si desidera modificare la configurazione dei Moduli Meccanici? "));
//        if (risposta==QMessageBox::Yes)
//        {
//            flag=6;
//           // ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);
//      }
//        else if (risposta==QMessageBox::No) {
//          ui->checkBox_MAP->setChecked(false);
//        }
//      }

//    }
//    if(ui->checkBox_oi->isChecked())
//    {
//      dati::oi = "1";

//      QSqlQuery moduli;
//      moduli.prepare("update Parametri_Paziente set Oggetti_int='"+dati::oi+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");

//     moduli.exec();

//            if (moduli.exec())
//            {

//            QMessageBox ::information(this,tr("Salvato"),tr("Configurazione del Modulo Extra: Oggetti Interattattivi salvata"));
//             ui->checkBox_oi->setChecked(false);
//           }
//           else {
//              QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
//            }
//    }
//    if (flag==6)
//   {
//       ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);


//    }
//    else {

//   ui->tabWidget_2->setCurrentWidget(ui->tab_tutorial);
//    }
//}

void paginaprincipale::on_pushButton_continua_clicked()
{   qDebug() << flag;
    ui->tabWidget_2->setCurrentWidget(ui->tab_vestizione);
    if (flag==4) //day N
    {
        if(dati::mood_prec=="Trigger")
         {
           ui->radioButton_trigger->setChecked(true);
         }
        else {
          {
            ui->radioButton_trigger->setChecked(false);
          }
        }
          if(dati::mood_prec== "Mobilizzazione Passiva" )
         {
           ui->radioButton_pass->setChecked(true);
         }
          else
          {
            ui->radioButton_pass-> setChecked(false);
          }
          if(dati::mood_prec=="Assisted as needed")
         {
           ui->radioButton_aan->setChecked(true);
         }
          else {
            ui->radioButton_aan->setChecked(false);
          }
         if (dati::mood_prec=="Anti-g")
         {
           ui->radioButton_ag->setChecked(true);
         }
         else
         {
           ui->radioButton_ag->setChecked(false);
         }
          if(dati::mood_prec=="Challenging")
         {
           ui->radioButton_chall->setChecked(true);
         }
          else
          {
            ui->radioButton_chall->setChecked(false);
          }


    }
   // day0
    else {
ui->tabWidget_2->setCurrentWidget(ui->tab_vestizione);

    }

}
void paginaprincipale::enable_combo() {
  ui->comboBox_oi_es1->setEnabled(false);
  ui->comboBox_oi_es2->setEnabled(false);
  ui->comboBox_oi_es3->setEnabled(false);
  ui->comboBox_oi_es4->setEnabled(false);
  ui->comboBox_oi_es5->setEnabled(false);
  ui->comboBox_oi_es6->setEnabled(false);
  ui->comboBox_oi_es7->setEnabled(false);


  es2 = "Raggiungimento anteriore di target su un piano con oggetti";
  es4 = "Raggiungimento anteriore di target su un piano nello spazio con oggetti";
  es7 = "Mano alla bocca con oggetto";

  qDebug()<< "sono nella funzione enable_combo";
  if(ui->comboBox_ex1->currentText()==es2 || ui->comboBox_ex1->currentText()== es4 || ui->comboBox_ex1->currentText()== es7) {
    ui->comboBox_oi_es1->setEnabled(true);

  }
  if(ui->comboBox_ex2->currentText()==es2 || ui->comboBox_ex2->currentText()== es4 || ui->comboBox_ex2->currentText()== es7) {
    ui->comboBox_oi_es2->setEnabled(true);

  }
  if(ui->comboBox_ex3->currentText()==es2 || ui->comboBox_ex3->currentText()== es4 || ui->comboBox_ex3->currentText()== es7) {
    ui->comboBox_oi_es3->setEnabled(true);

  }
  if(ui->comboBox_ex4->currentText()==es2 || ui->comboBox_ex4->currentText()== es4 || ui->comboBox_ex4->currentText()== es7) {
    ui->comboBox_oi_es4->setEnabled(true);

  }
  if(ui->comboBox_ex5->currentText()==es2 || ui->comboBox_ex5->currentText()== es4 || ui->comboBox_ex5->currentText()== es7) {
    ui->comboBox_oi_es5->setEnabled(true);

  }
  if(ui->comboBox_ex6->currentText()==es2 || ui->comboBox_ex6->currentText()== es4 || ui->comboBox_ex6->currentText()== es7) {
    ui->comboBox_oi_es6->setEnabled(true);

  }
  if(ui->comboBox_ex7->currentText()==es2 || ui->comboBox_ex7->currentText()== es4 || ui->comboBox_ex7->currentText()== es7) {
    ui->comboBox_oi_es7->setEnabled(true);

  }

}
void paginaprincipale::update_tempo_terapia(){
  QString t;
    qDebug()<< "sono nella funzione update_tempo_terapia";
  es1 = "Raggiungimento anteriore di target su un piano senza oggetti";
  es2 = "Raggiungimento anteriore di target su un piano con oggetti";
  es3 = "Raggiungimento anteriore di target su un piano nello spazio senza oggetti";
  es4 = "Raggiungimento anteriore di target su un piano nello spazio con oggetti ";
  es5 = "Elevazione laterale su un piano frontale";
  es6 = "Mano alla bocca senza oggetto";
  es7 = "Mano alla bocca con oggetto";


  if (ui->comboBox_ex1->currentText()== es1 || ui->comboBox_ex1->currentText()==es3 || ui->comboBox_ex1->currentText() == es5 || ui->comboBox_ex1->currentText()== es6){
    t_es1 = 1;
     ripe1 = ui->lineEdit_ex1->text().toInt();
    //ripe1 = dati::rip1.toInt();
   t_es1 = t_es1*ripe1;
   qDebug() << "es 1";
   qDebug() << t_es1;

  }
  else if ( ui->comboBox_ex1->currentText() == es2 || ui->comboBox_ex1->currentText()== es7) {
    t_es1 = 2;
     ripe1 = ui->lineEdit_ex1->text().toInt();
    t_es1 = t_es1* ripe1;
    qDebug() << "es 1";
    qDebug() << t_es1;
  }
  if (ui->comboBox_ex2->currentText()== es1 || ui->comboBox_ex2->currentText()==es3 || ui->comboBox_ex2->currentText() == es5 || ui->comboBox_ex2->currentText()== es6){
    t_es2 = 1;
ripe2 = ui->lineEdit_ex2->text().toInt();
   t_es2 = t_es2*ripe2;
   qDebug() << "es2";
   qDebug() << t_es2;

  }
  else if ( ui->comboBox_ex2->currentText() == es2 || ui->comboBox_ex2->currentText()== es7) {
    t_es2 = 2;
    ripe2 = ui->lineEdit_ex2->text().toInt();
    t_es2 = t_es2* ripe2;
     qDebug() << "es2";
    qDebug() << t_es2;
  }
  if (ui->comboBox_ex3->currentText()== es1 || ui->comboBox_ex3->currentText()==es3 || ui->comboBox_ex3->currentText() == es5 || ui->comboBox_ex3->currentText()== es6){
    t_es3 = 1;
ripe3 = ui->lineEdit_ex3->text().toInt();
   t_es3 = t_es3*ripe3;
    qDebug() << "es3";
   qDebug() << t_es3;

  }
  else if ( ui->comboBox_ex3->currentText() == es2 || ui->comboBox_ex3->currentText()== es7) {
    t_es3 = 2;
    ripe3 = ui->lineEdit_ex3->text().toInt();
    t_es3 = t_es3* ripe3;
     qDebug() << "es3";
    qDebug() << t_es3;
  }
  if (ui->comboBox_ex4->currentText()== es1 || ui->comboBox_ex4->currentText()==es3 || ui->comboBox_ex4->currentText() == es5 || ui->comboBox_ex4->currentText()== es6){
    t_es4 = 1;
ripe4 = ui->lineEdit_ex4->text().toInt();
   t_es4 = t_es4*ripe4;

  }
  else if ( ui->comboBox_ex4->currentText() == es2 || ui->comboBox_ex4->currentText()== es7) {
    t_es4 = 2;
    ripe4 = ui->lineEdit_ex4->text().toInt();
    t_es4 = t_es4* ripe4;
  }
  if (ui->comboBox_ex5->currentText()== es1 || ui->comboBox_ex5->currentText()==es3 || ui->comboBox_ex5->currentText() == es5 || ui->comboBox_ex5->currentText()== es6){
    t_es5 = 1;
ripe5 = ui->lineEdit_ex5->text().toInt();
   t_es5 = t_es5*ripe5;

  }
  else if ( ui->comboBox_ex5->currentText() == es2 || ui->comboBox_ex5->currentText()== es7) {
    t_es5 = 2;
    ripe5 = ui->lineEdit_ex5->text().toInt();
    t_es5 = t_es5* ripe5;
  }

  if (ui->comboBox_ex6->currentText()== es1 || ui->comboBox_ex6->currentText()==es3 || ui->comboBox_ex6->currentText() == es5 || ui->comboBox_ex6->currentText()== es6){
    t_es6 = 1;
ripe6 = ui->lineEdit_ex6->text().toInt();
   t_es6 = t_es6*ripe6;

  }
  else if ( ui->comboBox_ex6->currentText() == es2 || ui->comboBox_ex6->currentText()== es7) {
    t_es6 = 2;
    ripe6 = ui->lineEdit_ex6->text().toInt();
    t_es6 = t_es6* ripe6;
  }

  if (ui->comboBox_ex7->currentText()== es1 || ui->comboBox_ex7->currentText()==es3 || ui->comboBox_ex7->currentText() == es5 || ui->comboBox_ex7->currentText()== es6){
    t_es7 = 1;
ripe7 = ui->lineEdit_ex7->text().toInt();
   t_es7 = t_es7*ripe7;

  }
  else if ( ui->comboBox_ex7->currentText() == es2 || ui->comboBox_ex7->currentText()== es7) {
    t_es7 = 2;
    ripe7 = ui->lineEdit_ex7->text().toInt();
    t_es7 = t_es7* ripe7;
  }
  if(ui->checkBox_ex1->isChecked()) {
    temp_tot = t_es1;
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_ex2->isChecked()) {
    temp_tot += t_es2;
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_ex3->isChecked()) {
    temp_tot += t_es3;
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_ex4->isChecked()) {
    temp_tot += t_es4;
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_ex5->isChecked()) {
    temp_tot += t_es5;
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_ex6->isChecked()) {
    temp_tot += t_es6;
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_7->isChecked()) {
    temp_tot += t_es7;
    temp_string = QString::number(temp_tot);
  }


 qDebug()<< temp_tot;
 qDebug()<< temp_string;

 QString test = QString("Tempo Stimato per la Terapia : %1 minuti").arg(temp_string);

 ui->label_tempo->setText(test);

}
void paginaprincipale::enable_combo_ex() {
  ui->comboBox_ex1->setEnabled(false);
  ui->comboBox_ex2->setEnabled(false);
  ui->comboBox_ex3->setEnabled(false);
  ui->comboBox_ex4->setEnabled(false);
  ui->comboBox_ex5->setEnabled(false);
  ui->comboBox_ex6->setEnabled(false);
  ui->comboBox_ex7->setEnabled(false);

  if(ui->checkBox_ex1->isChecked()) {
    ui->comboBox_ex1->setEnabled(true);
  }
  if(ui->checkBox_ex2->isChecked()) {
    ui->comboBox_ex2->setEnabled(true);
  }
  if(ui->checkBox_ex3->isChecked()) {
    ui->comboBox_ex3->setEnabled(true);
  }
  if(ui->checkBox_ex4->isChecked()) {
    ui->comboBox_ex4->setEnabled(true);
  }
  if(ui->checkBox_ex5->isChecked()) {
    ui->comboBox_ex5->setEnabled(true);
  }
  if(ui->checkBox_ex6->isChecked()) {
    ui->comboBox_ex6->setEnabled(true);
  }
  if(ui->checkBox_7->isChecked()) {
    ui->comboBox_ex7->setEnabled(true);
  }

}
void paginaprincipale::on_pushButton_salvaex_clicked()
{    QString bicchiere, forchetta, libro;
     bicchiere = "Bicchiere";
     forchetta = "Forchetta";
     libro = "Libro";

 if(ui->checkBox_ex1->isChecked())
 {  check_ex1=1;
   dati::ex1 = ui->comboBox_ex1->currentText();

   dati::rip1= ui->lineEdit_ex1->text();
   if(ui->comboBox_oi_es1->isEnabled()) {
   if(ui->comboBox_oi_es1->currentText()== bicchiere ) {oggetto_es1= "1"; ros_ogg1=1;}
   else if (ui->comboBox_oi_es1->currentText()==forchetta) {oggetto_es1= "2"; ros_ogg1=2;}
   else if(ui->comboBox_oi_es1 ->currentText()==libro) {oggetto_es1= "3"; ros_ogg1=3;} }
   else if (!(ui->comboBox_oi_es1->isEnabled())) {
     oggetto_es1="0";
     ros_ogg1 = 0;
   }
   qDebug()<< oggetto_es1;
   QSqlQuery selezione1;
   selezione1.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex1+"'");
   selezione1.exec();
   if (selezione1.exec()) {
     while(selezione1.next())
     {
     dati::num_ex1 = selezione1.value(0).toString();

       }
     if(dati::rip1.toInt()< 30) {
//     QSqlQuery es1;
//     es1.prepare("update Parametri_Paziente set ex1 = '"+dati::num_ex1+"' , rip1 = '"+dati::rip1+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
//     es1.exec();
//     if(es1.exec())
//     {
//       QMessageBox ::information(this,tr("Salvato"),tr("esercizio salvato"));
//     }
//     else {
//       QMessageBox ::critical(this,tr("Errore"),tr("errore"));
//     }
     }
     else if(dati::rip1.toInt()>30)
     {
       QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni del primo esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));


          }
   }

if(!(dati::num_ex1.toInt()==2 || dati::num_ex1.toInt()==4 || dati::num_ex1.toInt()==7) ) {

  ui->comboBox_oi_es1->setEnabled(false);
}

 }
 if(ui->checkBox_ex2->isChecked())
 {
   dati::ex2 = ui->comboBox_ex2->currentText();

   dati::rip2= ui->lineEdit_ex2->text();
   if(ui->comboBox_oi_es2->isEnabled()) {
   if(ui->comboBox_oi_es2->currentText()== bicchiere ) {oggetto_es2= "1"; ros_ogg2=1;}
   else if (ui->comboBox_oi_es2->currentText()==forchetta) {oggetto_es2 = "2"; ros_ogg2= 2;}
   else if(ui->comboBox_oi_es2 ->currentText()==libro) {oggetto_es2= "3"; ros_ogg2= 3;} }
   else if (!(ui->comboBox_oi_es2->isEnabled())) {
     oggetto_es2 = "0";
     ros_ogg2 = 0;
   }
   QSqlQuery selezione2;
   selezione2.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex2+"'");
   selezione2.exec();
   if (selezione2.exec()) {
     while(selezione2.next())
     {
     dati::num_ex2 = selezione2.value(0).toString();


       }
     if(dati::rip2.toInt()<30) {
//     QSqlQuery es2;
//     es2.prepare("update Parametri_Paziente set ex2 = '"+dati::num_ex2+"' , rip2 = '"+dati::rip2+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
//     es2.exec();
//     if(es2.exec())
//     {
//       QMessageBox ::information(this,tr("Salvato"),tr("esercizio salvato"));
//     }
//     else {
//       QMessageBox ::critical(this,tr("Errore"),tr("errore"));
//     }
     }
     else if (dati::rip2.toInt()>30)
     {
       QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
     }
   }

 }
 if(ui->checkBox_ex3->isChecked())
 {
   dati::ex3 = ui->comboBox_ex3->currentText();

   dati::rip3= ui->lineEdit_ex3->text();
   if(ui->comboBox_oi_es3->isEnabled()) {
   if(ui->comboBox_oi_es3->currentText()== bicchiere ) {oggetto_es3= "1"; ros_ogg3=1;}
   else if (ui->comboBox_oi_es3->currentText()==forchetta) {oggetto_es3= "2"; ros_ogg3=3;}
   else if(ui->comboBox_oi_es3 ->currentText()==libro) {oggetto_es3= "3"; ros_ogg3=3;} }
   else if(!(ui->comboBox_oi_es3->isEnabled())) {
     oggetto_es3 = "0";
     ros_ogg3 = 0;
   }
   QSqlQuery selezione3;
   selezione3.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex3+"'");
   selezione3.exec();
   if (selezione3.exec()) {
     while(selezione3.next())
     {
     dati::num_ex3 = selezione3.value(0).toString();


       }
     if(dati::rip3.toInt()<30) {
//     QSqlQuery es3;
//     es3.prepare("update Parametri_Paziente set ex3 = '"+dati::num_ex3+"' , rip3 = '"+dati::rip3+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
//     es3.exec();
//     if(es3.exec())
//     {
//       QMessageBox ::information(this,tr("Salvato"),tr("esercizio salvato"));
//     }
//     else {
//       QMessageBox ::critical(this,tr("Errore"),tr("errore"));
//     }
     }
     else if (dati::rip3.toInt()>30) {
       QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
     }
   }

 }
if(ui->checkBox_ex4->isChecked())
{
  dati::ex4 = ui->comboBox_ex4->currentText();

  dati::rip4= ui->lineEdit_ex4->text();
  if(ui->comboBox_oi_es4->isEnabled()) {
  if(ui->comboBox_oi_es4->currentText()== bicchiere ) {oggetto_es4= "1"; ros_ogg4=1;}
  else if (ui->comboBox_oi_es4->currentText()==forchetta) {oggetto_es4= "2"; ros_ogg4=3;}
  else if(ui->comboBox_oi_es4 ->currentText()==libro) {oggetto_es4= "3"; ros_ogg4=3;} }
  else if (!(ui->comboBox_oi_es4->isEnabled())) {
    oggetto_es4 = "0";
    ros_ogg4 = 0;
  }
  QSqlQuery selezione4;
  selezione4.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex4+"'");
  selezione4.exec();
  if (selezione4.exec()) {
    while(selezione4.next())
    {
    dati::num_ex4 = selezione4.value(0).toString();


      }
    if (dati::rip4.toInt()<30) {
//    QSqlQuery es4;
//    es4.prepare("update Parametri_Paziente set ex4 = '"+dati::num_ex4+"' , rip4 = '"+dati::rip4+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
//    es4.exec();
//    if(es4.exec())
//    {
//      QMessageBox ::information(this,tr("Salvato"),tr("esercizio salvato"));
//    }
//    else {
//      QMessageBox ::critical(this,tr("Errore"),tr("errore"));
//    }
    }
    else if (dati::rip4.toInt()>30)
    {
      QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
    }
  }

}
if(ui->checkBox_ex5->isChecked())
{
  dati::ex5 = ui->comboBox_ex5->currentText();

  dati::rip5= ui->lineEdit_ex5->text();
  if(ui->comboBox_oi_es5->isEnabled()) {
  if(ui->comboBox_oi_es5->currentText()== bicchiere ) {oggetto_es5= "1"; ros_ogg5=1;}
  else if (ui->comboBox_oi_es5->currentText()==forchetta) {oggetto_es5= "2"; ros_ogg5=2;}
  else if(ui->comboBox_oi_es5->currentText()==libro) {oggetto_es5= "3"; ros_ogg5=3;} }
  else if (!(ui->comboBox_oi_es5->isEnabled())) {
    oggetto_es5 = "0";
    ros_ogg5 = 0;

  }
  QSqlQuery selezione5;
  selezione5.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex5+"'");
  selezione5.exec();
  if (selezione5.exec()) {
    while(selezione5.next())
    {
    dati::num_ex5 = selezione5.value(0).toString();


      }
    if(dati::rip5.toInt()<30) {
//    QSqlQuery es5;
//    es5.prepare("update Parametri_Paziente set ex5 = '"+dati::num_ex5+"' , rip5 = '"+dati::rip5+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
//    es5.exec();
//    if(es5.exec())
//    {
//      QMessageBox ::information(this,tr("Salvato"),tr("esercizio salvato"));
//    }
//    else {
//      QMessageBox ::critical(this,tr("Errore"),tr("errore"));
//    }
    }
    else if(dati::rip5.toInt()>30) {
      QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
    }

  }

}
if(ui->checkBox_ex6->isChecked())
{
  dati::ex6 = ui->comboBox_ex6->currentText();

  dati::rip6= ui->lineEdit_ex6->text();
  if(ui->comboBox_oi_es6->isEnabled()) {
  if(ui->comboBox_oi_es6->currentText()== bicchiere ) {oggetto_es6= "1"; ros_ogg6=1;}
  else if (ui->comboBox_oi_es6->currentText()==forchetta) {oggetto_es6= "2"; ros_ogg6=2;}
  else if(ui->comboBox_oi_es6 ->currentText()==libro) {oggetto_es6= "3"; ros_ogg6=3;} }
  else if(!(ui->comboBox_oi_es6->isEnabled()))  {
    oggetto_es6 = "0";
    ros_ogg6 = 0;
  }
  QSqlQuery selezione6;
  selezione6.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex6+"'");
  selezione6.exec();
  if (selezione6.exec()) {
    while(selezione6.next())
    {
    dati::num_ex6 = selezione6.value(0).toString();


      }
    if(dati::rip6.toInt()<30) {
//    QSqlQuery es6;
//    es6.prepare("update Parametri_Paziente set ex6 = '"+dati::num_ex6+"' , rip6 = '"+dati::rip6+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
//    es6.exec();
//    if(es6.exec())
//    {
//      QMessageBox ::information(this,tr("Salvato"),tr("esercizio salvato"));
//    }
//    else {
//      QMessageBox ::critical(this,tr("Errore"),tr("errore"));
//    }
    }
    else if(dati::rip6.toInt()>30)
    {
      QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
    }
  }


}
if(ui->checkBox_7->isChecked())
{
  dati::ex7 = ui->comboBox_ex7->currentText();

  dati::rip7= ui->lineEdit_ex7->text();
  if(ui->comboBox_oi_es7->isEnabled()) {
  if(ui->comboBox_oi_es7->currentText()== bicchiere ) {oggetto_es7= "1"; ros_ogg7=1;}
  else if (ui->comboBox_oi_es7->currentText()==forchetta) {oggetto_es7= "2"; ros_ogg7=2;}
  else if(ui->comboBox_oi_es7 ->currentText()==libro) {oggetto_es7= "3"; ros_ogg7=3;} }
  else if(!(ui->comboBox_oi_es7 ->isEnabled())) {
    oggetto_es7 = "0";
    ros_ogg7 = 0;
  }
  QSqlQuery selezione7;
  selezione7.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex7+"'");
  selezione7.exec();
  if (selezione7.exec()) {
    while(selezione7.next())
    {
    dati::num_ex7 = selezione7.value(0).toString();


      }
    if(dati::rip7.toInt()<30) {
//    QSqlQuery es7;
//    es7.prepare("update Parametri_Paziente set ex7 = '"+dati::num_ex7+"' , rip7 = '"+dati::rip7+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
//    es7.exec();
//    if(es7.exec())
//    {
//      QMessageBox ::information(this,tr("Salvato"),tr("esercizio salvato"));
//    }
//    else {
//      QMessageBox ::critical(this,tr("Errore"),tr("errore"));
//    }
    }
    else if(dati::rip7.toInt()>30)
    {
      QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
    }
  }

}
qDebug()<< dati::ind;
QSqlQuery selezione;
selezione.prepare("update Parametri_Paziente set ex1 = '"+dati::num_ex1+"', rip1 = '"+dati::rip1+"', ogg_es1 = '"+oggetto_es1+"', ex2 = '"+dati::num_ex2+"', rip2 = '"+dati::rip2+"',ogg_es2 = '"+oggetto_es2+"', ex3 = '"+dati::num_ex3+"', rip3 = '"+dati::rip3+"', ogg_es3 = '"+oggetto_es3+"',ex4 = '"+dati::num_ex4+"', rip4 = '"+dati::rip4+"', ogg_es4 = '"+oggetto_es4+"',ex5 = '"+dati::num_ex5+"', rip5 = '"+dati::rip5+"',ogg_es5 = '"+oggetto_es5+"',ex6 = '"+dati::num_ex6+"', rip6 = '"+dati::rip6+"', ogg_es6 = '"+oggetto_es6+"',ex7 = '"+dati::num_ex7+"', rip7 = '"+dati::rip7+"', ogg_es7 = '"+oggetto_es7+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' ");
selezione.exec();
if (selezione.exec())
{
  QMessageBox ::information(this,tr("Salvato"),tr("Set di esercizi salvati"));
  // mando messaggio che ho salvato esercizi
  ss3 << "ho salvato il set di esercizi  " ; // al posto di questa devo leggere qnode.variabile da dove l'ho modificata
  msg.data = ss3.str();
chatter_publisher.publish(msg);
ROS_INFO_STREAM(msg);

}
else {
  QMessageBox ::critical(this,tr("Errore"),tr("errore"));
  qDebug()<< selezione.lastError();
}

QSqlQuery esercizi;
esercizi.prepare("select ex1,rip1,ex2,rip2,ex3,rip3,ex4,rip4,ex5,rip5,ex6,rip6,ex7,rip7 from Parametri_Paziente where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
if(esercizi.exec()){
while(esercizi.next())
{ ExInfo cur;
  QString EX1 = esercizi.value(0).toString();
  int RIP1 = esercizi.value(1).toInt();

  if ( ! EX1.isEmpty() ){
  // FILL IT
  cur.EX = EX1; // fill it
  cur.REP = RIP1;
  cur.images = GetImages(EX1);
  ExInfoMap[EX1] = cur; //  add it
  qDebug()<<cur.images.size();
  sel_ex.append(EX1);
   qDebug()<< "sel:" << sel_ex;
           qDebug()<< " size:" << sel_ex.size();
  }
  else {
   QString es = "01";
   QString es2 = "02";
   QString es3 = "03";
   QString es4 = "04";
   if(ExInfoMap.find(es) !=ExInfoMap.end() || (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
   ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);

   }
   else ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);  }

  QString EX2 = esercizi.value(2).toString();
  int RIP2 = esercizi.value(3).toInt();
  if(!EX2.isEmpty()) {
  // FILL IT
  cur.EX = EX2; // fill it
  cur.REP = RIP2;
  cur.images = GetImages(EX2);  // use ID to get images  /////////////////////////////////////////////// IMAGES
  ExInfoMap[EX2] = cur; //  add it
  sel_ex.append(EX2);
  qDebug()<< "sel:" << sel_ex;
          qDebug()<< " size:" << sel_ex.size();

  }
  else {

    QString es = "01";
    QString es2 = "02";
    QString es3 = "03";
    QString es4 = "04";
    if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
    ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
    std::cout<< "Key found";


    }
    else {ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
    std::cout<< "key not found";}
  }

  QString EX3 = esercizi.value(4).toString();
  int RIP3 = esercizi.value(5).toInt();
  if(!EX3.isEmpty()) {
  // FILL IT
  cur.EX = EX3; // fill it
  cur.REP = RIP3;
   cur.images = GetImages(EX3);
  ExInfoMap[EX3] = cur; //  add it
   sel_ex.append(EX3);
   qDebug()<< "sel:" << sel_ex;
           qDebug()<< " size:" << sel_ex.size();

  }
  else {

    QString es = "01";
    QString es2 = "02";
    QString es3 = "03";
    QString es4 = "04";
    if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
    ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
    std::cout<< "Key found";


    }
    else {ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
    std::cout<< "key not found";}
  }
  QString EX4 = esercizi.value(6).toString();
  int RIP4 = esercizi.value(7).toInt();
  if(!EX4.isEmpty()) {
  // FILL IT
  cur.EX = EX4; // fill it
  cur.REP = RIP4;
  cur.images = GetImages(EX4);
  ExInfoMap[EX4] = cur; //  add it
   sel_ex.append(EX4);
   qDebug()<< "sel:" << sel_ex;
           qDebug()<< " size:" << sel_ex.size();




  }
  else {

    QString es = "01";
    QString es2 = "02";
    QString es3 = "03";
    QString es4 = "04";
    if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
    ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
    std::cout<< "Key found";


    }
    else {ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
    std::cout<< "key not found";}
  }
  QString EX5 = esercizi.value(8).toString();
  int RIP5 = esercizi.value(9).toInt();
  if(!EX5.isEmpty()){
  // FILL IT
  cur.EX = EX5; // fill it
  cur.REP = RIP5;
   cur.images = GetImages(EX5);
  ExInfoMap[EX5] = cur; //  add it
   sel_ex.append(EX5);
   qDebug()<< "sel:" << sel_ex;
           qDebug()<< " size:" << sel_ex.size();




  }
  else {

    QString es = "01";
    QString es2 = "02";
    QString es3 = "03";
    QString es4 = "04";
    if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
    ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
    std::cout<< "Key found";


    }
    else {ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
    std::cout<< "key not found";}
  }
  QString EX6 = esercizi.value(10).toString();
  int RIP6 = esercizi.value(11).toInt();
  if(!EX6.isEmpty()) {
  // FILL IT
  cur.EX = EX6; // fill it
  cur.REP = RIP6;
  cur.images = GetImages(EX6);
  ExInfoMap[EX6] = cur; //  add it
   sel_ex.append(EX6);
   qDebug()<< "sel:" << sel_ex;
           qDebug()<< " size:" << sel_ex.size();




  }
  else {

    QString es = "01";
    QString es2 = "02";
    QString es3 = "03";
    QString es4 = "04";
    if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
    ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
    std::cout<< "Key found";


    }
    else {ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
    std::cout<< "key not found";}
  }
  QString EX7 = esercizi.value(12).toString();
  int RIP7 = esercizi.value(13).toInt();
  if(!EX7.isEmpty()) {
  // FILL IT
  cur.EX = EX7; // fill it
  cur.REP = RIP7;
  cur.images = GetImages(EX7);
  ExInfoMap[EX7] = cur; //  add it
   sel_ex.append(EX7);
   qDebug()<< "sel:" << sel_ex;
           qDebug()<< " size:" << sel_ex.size();


  }
  else {

    QString es = "01";
    QString es2 = "02";
    QString es3 = "03";
    QString es4 = "04";
    if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
    ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
    std::cout<< "Key found";


    }
    else {ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
    std::cout<< "key not found";}
  }
}

}
//QSqlQuery ins_val;
//   ins_val.prepare("insert into Valutazioni (Codice_ID, Data_acquisizione) values('"+dati::ind+"', '"+dati::data1+"') ");

//         if (ins_val.exec()) {
//           qDebug()<< "fatto";
//         }
//         else qDebug()<< ins_val.lastError();
}

void paginaprincipale::on_pushButton_controllo_clicked()

{

  if(ui->radioButton_trigger->isChecked()) {
    dati::mood = "Trigger";
    QSqlQuery modalita;
    modalita.prepare("update Parametri_Paziente set Modalita_utilizzo = '"+dati::mood+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    modalita.exec();
        if (modalita.exec())
        {

         QMessageBox ::information(this,tr("Salvato"),tr("Configurazione della modalità salvata: Mobilizzazione Passiva con Trigger"));
//         ss << "ho salvato la configurazione " ; // al posto di questa devo leggere qnode.variabile da dove l'ho modificata
//         msg.data = ss.str();
//       chatter_publisher.publish(msg);




       }
       else {
          QMessageBox ::critical(this,tr("Errore"),tr("modalità"));
        }

  }

  if (ui->radioButton_pass->isChecked())
  {
    dati::mood = "Mobilizzazione Passiva";
    QSqlQuery modalita;
    modalita.prepare("update Parametri_Paziente set Modalita_utilizzo = '"+dati::mood+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    modalita.exec();
        if (modalita.exec())
        {

         QMessageBox ::information(this,tr("Salvato"),tr("Configurazione della modalità salvata: Mobilizzazione Passiva"));





       }
       else {
          QMessageBox ::critical(this,tr("Errore"),tr("modalità"));
        }
    }

  if(ui->radioButton_aan->isChecked())
  {
    dati::mood = "Assisted as needed";
    QSqlQuery modalita;
    modalita.prepare("update Parametri_Paziente set Modalita_utilizzo = '"+dati::mood+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    modalita.exec();
        if (modalita.exec())
        {

         QMessageBox ::information(this,tr("Salvato"),tr("Configurazione della modalità salvata: Assisted As Needed"));





       }
       else {
          QMessageBox ::critical(this,tr("Errore"),tr("modalità"));
        }
  }

  if (ui->radioButton_ag->isChecked())
  {
    dati::mood = "Anti-g";
    QSqlQuery modalita;
    modalita.prepare("update Parametri_Paziente set Modalita_utilizzo = '"+dati::mood+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    modalita.exec();
        if (modalita.exec())
        {

         QMessageBox ::information(this,tr("Salvato"),tr("Configurazione della modalità salvata: Anti Gravitario"));




       }
       else {
          QMessageBox ::critical(this,tr("Errore"),tr("modalità"));
        }
  }

  if (ui->radioButton_chall->isChecked())
  {
    dati::mood = "Challenging";
    QSqlQuery modalita;
    modalita.prepare("update Parametri_Paziente set Modalita_utilizzo = '"+dati::mood+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    modalita.exec();
        if (modalita.exec())
        {

         QMessageBox ::information(this,tr("Salvato"),tr("Configurazione della modalità salvata: Challenging"));





       }
       else {
          QMessageBox ::critical(this,tr("Errore"),tr("modalità"));
        }
  }


         QString r1, r2,r3,r4,r5,r6,r7;
         r1 = ui->lineEdit_ex1->placeholderText();
         r2 = ui->lineEdit_ex2->placeholderText();
         r3 = ui->lineEdit_ex3->placeholderText();
         r4 = ui->lineEdit_ex4->placeholderText();
         r5 = ui->lineEdit_ex5->placeholderText();
         r6 = ui->lineEdit_ex6->placeholderText();
         r7= ui->lineEdit_ex7->placeholderText();
//         ui->lineEdit_ex1->setText(r1);
//         ui->lineEdit_ex2->setText(r2);
//         ui->lineEdit_ex3->setText(r3);
//         ui->lineEdit_ex4->setText(r4);
//         ui->lineEdit_ex5->setText(r5);
//         ui->lineEdit_ex6->setText(r6);
//         ui->lineEdit_ex7->setText(r7);

// modalità
    ss1 << "ho salvato la configurazione" ; // al posto di questa devo leggere qnode.variabile da dove l'ho modificata
    msg.data = ss1.str();
  chatter_publisher.publish(msg);
  ROS_INFO_STREAM(msg);


                     if (flag==4) {
                        ui->tabWidget_2->setCurrentWidget(ui->tab_ex);

                       qDebug()<< "qui";
                      if(!(dati::lex1==0))
                      {
                        ui->checkBox_ex1->setChecked(true);
                        QSqlQuery selezione1;
                        selezione1.prepare("select Ex from Esercizi where Num_ex ='"+dati::ex1_prec+"'");
                        selezione1.exec();
                        if (selezione1.exec()) {

                          while(selezione1.next())
                        { ui->comboBox_ex1->setCurrentText(selezione1.value(0).toString());
                            QString ex1;
                            ex1 = selezione1.value(0).toString();
                            qDebug()<< ex1;

                            }



                        r1 = dati::rip1_prec;
                        ui->lineEdit_ex1->setText(r1);
                        qDebug()<< r1;
                        if(dati::ogg1_prec =="1") {
                          ui->comboBox_oi_es1->setCurrentText("Bicchiere");
                        }
                        else if(dati::ogg1_prec == "2") {
                          ui->comboBox_oi_es1->setCurrentText("Forchetta");
                        }
                        else if(dati::ogg1_prec == "3") {
                          ui->comboBox_oi_es1->setCurrentText("Libro");
                        }


                        }

                          }
                      else {
                        ui->checkBox_ex1->setChecked(false);
                      }
                      if(!(dati::lex2==0))
                      {
                        ui->checkBox_ex2->setChecked(true);
                        QSqlQuery selezione2;
                        selezione2.prepare("select Ex from Esercizi where Num_ex ='"+dati::ex2_prec+"'");
                        selezione2.exec();
                        if (selezione2.exec()) {

                          while(selezione2.next())
                        { ui->comboBox_ex2->setCurrentText(selezione2.value(0).toString());
                            QString ex2;
                            ex2 = selezione2.value(0).toString();
                            qDebug()<< ex2;
                            }


                        r2 = dati::rip2_prec;
                        ui->lineEdit_ex2->setText(r2);
                        qDebug()<<r2;
                        if(dati::ogg2_prec =="1") {
                          ui->comboBox_oi_es2->setCurrentText("Bicchiere");
                        }
                        else if(dati::ogg2_prec == "2") {
                          ui->comboBox_oi_es2->setCurrentText("Forchetta");
                        }
                        else if(dati::ogg2_prec == "3") {
                          ui->comboBox_oi_es2->setCurrentText("Libro");
                        }

                      }
                      }
                      else {
                        ui->checkBox_ex2->setChecked(false);
                      }

                      if(!(dati::lex3==0))
                      {
                        ui->checkBox_ex3->setChecked(true);
                        QSqlQuery selezione3;
                        selezione3.prepare("select Ex from Esercizi where Num_ex ='"+dati::ex3_prec+"'");
                        selezione3.exec();
                        if (selezione3.exec()) {

                          while(selezione3.next())
                        { ui->comboBox_ex3->setCurrentText(selezione3.value(0).toString());
                            QString ex3;
                            ex3 = selezione3.value(0).toString();
                            qDebug()<< ex3;
                            }


                        r3 = dati::rip3_prec;
                        qDebug()<<r3;
                        if(dati::ogg3_prec =="1") {
                          ui->comboBox_oi_es3->setCurrentText("Bicchiere");
                        }
                        else if(dati::ogg3_prec == "2") {
                          ui->comboBox_oi_es3->setCurrentText("Forchetta");
                        }
                        else if(dati::ogg3_prec == "3") {
                          ui->comboBox_oi_es3->setCurrentText("Libro");
                        }


                       ui->lineEdit_ex3->setText(r3);

                      }
                      }
                      else {
                        ui->checkBox_ex3->setChecked(false);
                      }
                      if(!(dati::lex4==0))
                      {
                        ui->checkBox_ex4->setChecked(true);
                        QSqlQuery selezione4;
                        selezione4.prepare("select Ex from Esercizi where Num_ex ='"+dati::ex4_prec+"'");
                        selezione4.exec();
                        if (selezione4.exec()){

                          while(selezione4.next())
                        { ui->comboBox_ex4->setCurrentText(selezione4.value(0).toString());
                            QString ex4;
                            ex4 = selezione4.value(0).toString();
                            qDebug()<< ex4;
                            }


                        r4 = dati::rip4_prec;
                        ui->lineEdit_ex4->setText(r4);
                        qDebug()<< r4;
                        if(dati::ogg4_prec =="1") {
                          ui->comboBox_oi_es4->setCurrentText("Bicchiere");
                        }
                        else if(dati::ogg4_prec == "2") {
                          ui->comboBox_oi_es4->setCurrentText("Forchetta");
                        }
                        else if(dati::ogg4_prec == "3") {
                          ui->comboBox_oi_es4->setCurrentText("Libro");
                        }


                      }
                      }
                      else {
                        ui->checkBox_ex4->setChecked(false);
                      }
                      if(!(dati::lex5==0))
                      {
                        ui->checkBox_ex5->setChecked(true);
                        QSqlQuery selezione5;
                        selezione5.prepare("select Ex from Esercizi where Num_ex ='"+dati::ex5_prec+"'");
                        selezione5.exec();
                        if (selezione5.exec()) {

                          while(selezione5.next())
                        { ui->comboBox_ex5->setCurrentText(selezione5.value(0).toString());
                            QString ex5;
                            ex5 = selezione5.value(0).toString();
                            qDebug()<< ex5;
                            }


                        r5 = dati::rip5_prec;
                        ui->lineEdit_ex5->setText(r5);
                        qDebug()<< r5;
                        if(dati::ogg5_prec =="1") {
                          ui->comboBox_oi_es5->setCurrentText("Bicchiere");
                        }
                        else if(dati::ogg5_prec == "2") {
                          ui->comboBox_oi_es5->setCurrentText("Forchetta");
                        }
                        else if(dati::ogg5_prec == "3") {
                          ui->comboBox_oi_es5->setCurrentText("Libro");
                        }


                      }
                      }
                      else {
                        ui->checkBox_ex5->setChecked(false);
                      }
                      if(!(dati::lex6==0))
                      {
                        ui->checkBox_ex6->setChecked(true);
                        QSqlQuery selezione6;
                        selezione6.prepare("select Ex from Esercizi where Num_ex ='"+dati::ex6_prec+"'");
                        selezione6.exec();
                        if (selezione6.exec()){

                          while(selezione6.next())
                        { ui->comboBox_ex6->setCurrentText(selezione6.value(0).toString());
                            QString ex6;
                            ex6 = selezione6.value(0).toString();
                            qDebug()<< ex6;

                            }

                        r6 = dati::rip6_prec;
                       ui->lineEdit_ex6->setText(r6);
                       qDebug()<< r6;
                       if(dati::ogg6_prec =="1") {
                         ui->comboBox_oi_es6->setCurrentText("Bicchiere");
                       }
                       else if(dati::ogg6_prec == "2") {
                         ui->comboBox_oi_es6->setCurrentText("Forchetta");
                       }
                       else if(dati::ogg6_prec == "3") {
                         ui->comboBox_oi_es6->setCurrentText("Libro");
                       }


                      }
                      }
                      else {
                        ui->checkBox_ex6->setChecked(false);
                      }
                      if(!(dati::lex7==0))
                      {
                        ui->checkBox_7->setChecked(true);
                        QSqlQuery selezione7;
                        selezione7.prepare("select Ex from Esercizi where Num_ex ='"+dati::ex7_prec+"'");
                        selezione7.exec();
                        if (selezione7.exec()) {

                          while(selezione7.next())
                        { ui->comboBox_ex7->setCurrentText(selezione7.value(0).toString());
                            QString ex7;
                            ex7 = selezione7.value(0).toString();
                            qDebug()<< ex7;

                            }



                        r7 = dati::rip7_prec;
                        ui->lineEdit_ex7->setText(r7);
                        qDebug()<< r7;
                        if(dati::ogg7_prec =="1") {
                          ui->comboBox_oi_es7->setCurrentText("Bicchiere");
                        }
                        else if(dati::ogg7_prec == "2") {
                          ui->comboBox_oi_es7->setCurrentText("Forchetta");
                        }
                        else if(dati::ogg7_prec == "3") {
                          ui->comboBox_oi_es7->setCurrentText("Libro");
                        }



                      }
                      }
                      else {
                        ui->checkBox_7->setChecked(false);
                      }
                      qDebug()<<r1;
                      qDebug()<< r2;
                      qDebug()<< r3;
                      qDebug()<< r4;
                      qDebug()<< r5;
                      qDebug()<< r6;
                      qDebug()<< r7;
                      ui->lineEdit_ex1->setText(r1);
                      ui->lineEdit_ex2->setText(r2);
                      ui->lineEdit_ex3->setText(r3);
                      ui->lineEdit_ex4->setText(r4);
                      ui->lineEdit_ex5->setText(r5);
                      ui->lineEdit_ex6->setText(r6);
                      ui->lineEdit_ex7->setText(r7);
                     }

                     else {
                       ui->tabWidget_2->setCurrentWidget(ui->tab_ex);
                       qDebug()<< "fino qui ok";
                     r1 = ui->lineEdit_ex1->placeholderText();
                     r2 = ui->lineEdit_ex2->placeholderText();
                     r3 = ui->lineEdit_ex3->placeholderText();
                     r4 = ui->lineEdit_ex4->placeholderText();
                     r5 = ui->lineEdit_ex5->placeholderText();
                     r6 = ui->lineEdit_ex6->placeholderText();
                     r7= ui->lineEdit_ex7->placeholderText();
                     ui->lineEdit_ex1->setText(r1);
                     ui->lineEdit_ex2->setText(r2);
                     ui->lineEdit_ex3->setText(r3);
                     ui->lineEdit_ex4->setText(r4);
                     ui->lineEdit_ex5->setText(r5);
                     ui->lineEdit_ex6->setText(r6);
                     ui->lineEdit_ex7->setText(r7);
                     }

      enable_combo();
      update_tempo_terapia();
      enable_combo_ex();
      QSqlQuery ins_val;
         ins_val.prepare("insert into Valutazioni (Codice_ID, Data_acquisizione) values('"+dati::ind+"', '"+dati::data1+"') ");

               if (ins_val.exec()) {
                 qDebug()<< "fatto";
               }
               else qDebug()<< ins_val.lastError();
      rand1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      QString rands1 = QString::number(rand1);
      rand2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      QString rands2 = QString::number(rand2);
      rand3= static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
       QString rands3 = QString::number(rand3);
      rand4= static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      QString rands4 = QString::number(rand4);
      rand5= static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      QString rands5 = QString::number(rand5);
      rand10 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      QString rands10 = QString::number(rand10);
      arr7_1 =  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      QString arrs7_1 = QString::number(arr7_1);
      arr7_2 =  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      QString arrs7_2 = QString::number(arr7_2);
      arr7_3 =  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      QString arrs7_3 = QString::number(arr7_3);
      arr7_4 =  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      QString arrs7_4 = QString::number(arr7_4);
      arr7_5 =  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      QString arrs7_5 = QString::number(arr7_5);
      val.append(arr7_1);
      val.append(arr7_2);
      val.append(arr7_3);
      val.append(arr7_4);
      val.append(arr7_5);
      vals << arrs7_1 << arrs7_2 << arrs7_3 << arrs7_4 << arrs7_5;
      QString valss = vals.join(",");

      arr9_1 =  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      QString arrs9_1 = QString::number(arr9_1);
      arr9_2 =  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      QString arrs9_2 = QString::number(arr9_2);
      arr9_3 =  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      QString arrs9_3 = QString::number(arr9_3);
      arr9_4 =  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      QString arrs9_4 = QString::number(arr9_4);
      arr9_5 =  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      QString arrs9_5 = QString::number(arr9_5);
      val2.append(arr9_1);
      val2.append(arr9_2);
      val2.append(arr9_3);
      val2.append(arr9_4);
      val2.append(arr9_5);
      vals2 << arrs9_1 << arrs9_2 << arrs9_3 <<arrs9_4 << arrs9_5;
      QString valss2 = vals2.join(",");
      val8.append(arr7_1);
      val8.append(arr7_2);
      val8.append(arr7_3);
      val8.append(arr7_4);
      val8.append(arr7_5);
      val8.append(arr9_1);
      val8.append(arr9_2);
      val8.append(arr9_3);
      val8.append(arr9_4);
      val8.append(arr9_5);
      vals8 << arrs7_1 << arrs7_2 << arrs7_3 << arrs7_4 << arrs7_5 << arrs9_1 << arrs9_2 << arrs9_3 <<arrs9_4 << arrs9_5;
      QString valss8 = vals8.join(",");
      qDebug() << val;
      qDebug() << val2;
      qDebug ()<< val8;
      //creo la matrice fittizia 5x19







      if (dati::mood == "Assisted as needed" || dati::mood == "Anti-g" || dati::mood == "Challenging") {
        QSqlQuery val_data;
        val_data.prepare ("update Valutazioni set Intrajoint_coordination = '"+rands1+"', Normalized_jerk = '"+rands2+"', Movement_arrest_period_ratio ='"+rands3+"', Peak_speed_ratio = '"+rands4+"', Acceleration_metric = '"+rands5+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");

       if( val_data.exec()) qDebug() << "fattoo";
       else qDebug()<< val_data.lastError();

      }
      if (dati::mood == "Assisted as needed") {
       QSqlQuery val_data1;
       val_data1.prepare("update Valutazioni set Active_movement_Idex = '"+rands10+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
       val_data1.exec();
      }
      if( dati::mood == "Assisted as needed" || dati::mood == "Anti-g" || dati::mood == "Challenging" || dati::mood == "Trigger" || dati::mood == "Mobilizzazione Passiva") {
       QSqlQuery val_data2;
       val_data2.prepare("update Valutazioni set Per_corretta_attivazione_muscolare = '"+valss+"', Normalized_EMG_action_level = '"+valss8+"', Indice_co_contrazione = '"+valss2+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' ");
       val_data2.exec();
      }
      if (dati::mood == "Trigger") {
       //matrice
      }




qDebug()<< rand1;








}

void paginaprincipale::on_pushButton_salvamoduli_clicked()

{
  dati::modulo_spalla= "0";
  dati::modulo_gomito = "0";
  dati::modulo_polso="0";
  dati::modulo_eeg = "0";
  dati::modulo_emg= "0";
  dati::mano = "0";
  dati::oi = "0";

  if(ui->checkBox_sinistro->isChecked())
  {dati::lato="0" ;
  }
 if(ui->checkBox_destro->isChecked())
 { dati::lato = "1";

 }
//if(ui->checkBox_spalla->isChecked())
//  {
//   // dati::modulo_spalla= "1";


//  }

  if (ui->checkBox_gomito->isChecked())
  {
    dati::modulo_gomito = "1";
    dati::modulo_spalla = "1";
    dati::oi = "1";

  }

  if (ui->checkBox_polso->isChecked())
  { dati::modulo_spalla = "1";
    dati::modulo_polso= "1";
    dati::modulo_gomito = "1";
    dati::oi = "1";


  }

  if(ui->checkBox_eeg_2->isChecked())
  {
    dati::modulo_eeg= "1";


  }
  if(ui->checkBox_emg_2->isChecked())
  {
    dati::modulo_emg= "1";

  }
  if(ui->checkBox_MAP_2->isChecked() ||  (prova == 5))
  {

    if(dati::modulo_polso == "1")
    {
    dati::mano = "1";

    }


    else if (dati::modulo_polso == "0" ) {
      qDebug()<< "qui";
      QMessageBox::StandardButton risposta= QMessageBox::question(this,tr("Attenzione"), tr("Il modulo extra: Mano non può essere attivato se la configurazione dei moduli moduli meccanici non comprende anche il Modulo : Polso. Si desidera modificare la configurazione dei Moduli Meccanici? "));
      if (risposta==QMessageBox::Yes)
      {
        //  flag=6;
         // ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);
        ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);
    }
      else if (risposta==QMessageBox::No) {
        ui->checkBox_MAP_2->setChecked(false);
      }
    }

  }
//  if(ui->checkBox_oi_2->isChecked())
//  {
//    dati::oi = "1";

//  }
  QSqlQuery moduli;
  moduli.prepare("update Parametri_Paziente set Lato = '"+dati::lato+"', Modulo_Spalla= '"+dati::modulo_spalla+"', Modulo_gomito = '"+dati::modulo_gomito+"', Modulo_polso = '"+dati::modulo_polso+"',EEG='"+dati::modulo_eeg+"', Oggetti_int='"+dati::oi+"', Mano='"+dati::mano+"', EMG='"+dati::modulo_emg+"' where Codice_ID= '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
 moduli.exec();
 if (moduli.exec())
 { QMessageBox ::information(this,tr("Salvato"),tr("Configurazione dei Moduli Meccanici ed Extra salvata"));
 }
 else {
   QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
   qDebug()<< moduli.lastError();
 }

  //  if (flag==6)
// {
//     ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);


//  }
//  else {
 //salvo i moduli
  ss2 << "ho salvato i moduli " ; // al posto di questa devo leggere qnode.variabile da dove l'ho modificata
  msg.data = ss2.str();
chatter_publisher.publish(msg);
ROS_INFO_STREAM(msg);
ui->tabWidget_2->setCurrentWidget(ui->tab_tutorial);

//recupero dati salvati
QSqlQuery conf_moduli;
conf_moduli.prepare("select Modulo_Spalla, Modulo_gomito, Modulo_polso, EEG, EMG, Mano from Parametri_Paziente where  Codice_ID= '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' ");
if(conf_moduli.exec()){
  qDebug()<< "ho eseguito la query";

while(conf_moduli.next()) {
  TutInfo curr;
  QString spalla, gomito, polso, EEG, EMG, Mano;

  spalla = conf_moduli.value(0).toString();
  gomito = conf_moduli.value(1).toString();
  polso = conf_moduli.value(2).toString();
  EEG = conf_moduli.value(3).toString();
  EMG = conf_moduli.value(4).toString();
  Mano = conf_moduli.value(5).toString();

  if (spalla == "1" && gomito == "1" && polso == "1") {
   QString tut1 = "mecc1";
   curr.tut = tut1;
   curr.img = GetImages2(tut1);
   TutInfoMap[tut1] = curr;
   qDebug()<<curr.img.size();
   sel_tut.append(tut1);
   qDebug()<<"sel : " <<sel_tut;
   qDebug()<<"size:" << sel_tut.size();
  }
  else if (spalla =="1" && gomito == "1" && polso == "0") {
   QString tut2 = "mecc";
   curr.tut = tut2;
   curr.img = GetImages2(tut2);
   TutInfoMap[tut2] = curr;
   qDebug()<<curr.img.size();
   sel_tut.append(tut2);
   qDebug()<<"sel : " <<sel_tut;
   qDebug()<<"size:" << sel_tut.size();

  }
  if(EEG == "1") {
    QString tut3 = "eeg";
    curr.tut = tut3;
    curr.img = GetImages2(tut3);
    TutInfoMap[tut3] = curr;
    qDebug()<<curr.img.size();
    sel_tut.append(tut3);
    qDebug()<<"sel : " <<sel_tut;
    qDebug()<<"size:" << sel_tut.size();

  }
  if (EMG == "1") {
    QString tut4 = "emg";
    curr.tut = tut4;
    curr.img = GetImages2(tut4);
    TutInfoMap[tut4] = curr;
    qDebug()<<curr.img.size();
    sel_tut.append(tut4);
    qDebug()<<"sel : " <<sel_tut;
    qDebug()<<"size:" << sel_tut.size();
  }
  if(Mano == "1") {
    QString tut5 = "map";
    curr.tut = tut5;
    curr.img = GetImages2(tut5);
    TutInfoMap[tut5] = curr;
    qDebug()<<curr.img.size();
    sel_tut.append(tut5);
    qDebug()<<"sel : " <<sel_tut;
    qDebug()<<"size:" << sel_tut.size();
  }


}
}


}
 // }

 // ui->tabWidget_2->setCurrentWidget(ui->tab_m_extra);

//  if (flag==6)
//  {
//    if (dati::modulo_emg_prec=="1")
//    {
//      ui->checkBox_emg_2->setChecked(true);
//    }
//    else if(dati::modulo_eeg_prec=="1")
//    {
//      ui->checkBox_eeg_2->setChecked(true);
//    }
//    else {
//      ui->checkBox_eeg_2->setChecked(false);
//      ui->checkBox_emg_2->setChecked(false);
//    }
//    if(!(dati::l_m_p==0))
//    {
//      ui->checkBox_MAP_2->setChecked(true);
//      flag= 5;
//    }
//    else {
//      ui->checkBox_MAP_2->setChecked(false);
//    }
//    if(!(dati::l_oi_p==0))
//    {
//      ui->checkBox_oi->setChecked(true);
//    }
//    else {
//      ui->checkBox_oi_2->setChecked(false);
//    }
//  }
//}


QList<QPixmap>GetImages(QString exID) {
  QList<QPixmap> mylist;
//auto folder("/home/alice/catkin_ws/src/agree_gui/resources/ex_img/" + exID);
auto folder ("/home/alice/Desktop/ex_img1/" + exID);
QDir directory(folder);
QStringList images = directory.entryList(QStringList() << "*.jpg" <<"*.JPG" ,QDir::Files);
qDebug() << directory;
qDebug() << "i found" << images.size();
foreach(QString filename, images) {
QPixmap pix(folder+ QString("/") + filename);
mylist.append(pix);
qDebug()<<mylist;

}
return mylist;


}

QList<QPixmap>GetImages2(QString tutID) {
  QList<QPixmap> mylist2;
  auto folder2("/home/alice/Desktop/tutorial/" +tutID);
  QDir directory2(folder2);
  QStringList img = directory2.entryList(QStringList() << "*.jpg" << "*.JPG" <<"*.png" << "*.PNG", QDir::Files );
  qDebug()<<directory2;
  qDebug() <<"i found" << img.size();
  foreach (QString filename, img) {
    QPixmap pix2(folder2 + QString("/") + filename);
    mylist2.append(pix2);
    qDebug()<< mylist2;
  }
  return mylist2;
}

void paginaprincipale::on_pushButton_salvatapp_clicked()
{

QVector<QPoint> mylocalList =matrix->getPosition();
// mando il massaggio che ho salvato i punti sul tappetino
ss4 << "ho salvato i punti sul tappetino" ; // al posto di questa devo leggere qnode.variabile da dove l'ho modificata
msg.data = ss4.str();
chatter_publisher.publish(msg);
ROS_INFO_STREAM(msg);
ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);


}

//void paginaprincipale::on_pushButton_goon_clicked()
//{
//  if(curEx<sel_ex.size()) {
//    key= sel_ex.at(curEx);
//  if (ExInfoMap.find(key) != ExInfoMap.end() ) {
//  ExInfo & one = ExInfoMap[key];
//  if (one.images.size() > 0)
//    ui->label_img->setPixmap(one.images.first());
//    else
//    qDebug() << "no images for key";
//  } else
//  qDebug() << "key is not valid";
//curEx++;
//}

//  if(curEx==sel_ex.size())
//  {
//    curEx=0;
//    return;
//  }
//}

void paginaprincipale::on_pushButton_next_clicked()
{ //qDebug()<<sel_ex;
  timer->start(1000);
  // next_img();
//  if(dati::next_img=="a"){
//  if(curEx<sel_ex.size()) {
//    key= sel_ex.at(curEx);
//    qDebug()<<key;
//      if (ExInfoMap.find(key) != ExInfoMap.end() ) {

//          ExInfo &one = ExInfoMap[key];

//          qDebug() << one.REP;

//  if(rep<one.REP) {
//          if (curImage < one.images.size()) {
//              ui->label_img->setPixmap(one.images.at(curImage));
//              curImage++;
//              ui->label_fine_ex->setText("");
//          }

//          if ( curImage == one.images.size() ) { // -1 we start in zero
//              curImage = 0;
//              rep++;
//              ui->label_fine_ex->setText("");
//          }
//  }
//          if ( rep == one.REP ) {
//              rep=0;
//              ui->label_fine_ex->setText("Congratulazioni hai completato correttamente l'esercizio, continua cosi!");
//              QPixmap smile("/home/alice/Desktop/smile.jpeg");
//              ui->label_img->setPixmap(smile);
//               curEx++;
//              // now take next EX
//          }
//      }


//      if(curEx==sel_ex.size())
//      {
//        curEx=0;
//        return;
//      }
 // }
//  if (curEx==sel_ex.size()) {
//    ui->tabWidget_2->setCurrentWidget(ui->tab_valutazione);
//    //carico la tabella dei pazienti
//        QSqlQueryModel *model1 = new QSqlQueryModel();
//        QSqlQuery * qry_val = new QSqlQuery(mydb2);
//        qry_val -> prepare("select * from Valutazioni where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' ");
//        qry_val -> exec();
//        if(qry_val->exec()) {
//        model1 -> setQuery(*qry_val);
//        ui->tableView_valutazioni->setModel(model1);
//        ui->tableView_valutazioni->resizeColumnsToContents();
//      //  qDebug() << (model->rowCount());
//        }
//        else qDebug()<<qry_val->lastError();
//  }
 // dati::next_img ="b";
//  }

}
void paginaprincipale::next_img() {
  qDebug()<< "sono nella funzione next_img";
  if(dati::next_img=="a"){
  if(curEx<sel_ex.size()) {
    key= sel_ex.at(curEx);
    qDebug()<<key;
      if (ExInfoMap.find(key) != ExInfoMap.end() ) {

          ExInfo &one = ExInfoMap[key];

          qDebug() << one.REP;

  if(rep<one.REP) {
          if (curImage < one.images.size()) {
              ui->label_img->setPixmap(one.images.at(curImage));
              curImage++;
              ui->label_fine_ex->setText("");
          }

          if ( curImage == one.images.size() ) { // -1 we start in zero
              curImage = 0;
              rep++;
              ui->label_fine_ex->setText("");
          }
  }
          if ( rep == one.REP ) {
              rep=0;
              ui->label_fine_ex->setText("Congratulazioni hai completato correttamente l'esercizio, continua cosi!");
              QPixmap smile("/home/alice/Desktop/smile.jpeg");
              ui->label_img->setPixmap(smile);
               curEx++;
              // now take next EX
          }
      }


//      if(curEx==sel_ex.size())
//      {
//        curEx=0;
//        return;
//      }
  }
  if (curEx==sel_ex.size()) {
    ui->tabWidget_2->setCurrentWidget(ui->tab_valutazione);
    timer->stop();
    //carico la tabella dei pazienti
        QSqlQueryModel *model1 = new QSqlQueryModel();
        QSqlQuery * qry_val = new QSqlQuery(mydb2);
        qry_val -> prepare("select * from Valutazioni where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' ");
        qry_val -> exec();
        if(qry_val->exec()) {
        model1 -> setQuery(*qry_val);
        ui->tableView_valutazioni->setModel(model1);
        ui->tableView_valutazioni->resizeColumnsToContents();
      //  qDebug() << (model->rowCount());
        }
        else qDebug()<<qry_val->lastError();
  }

dati::next_img = "b";

  }
}

void paginaprincipale::on_pushButton_associa_clicked()
{   QString user_doc_string;
    QSqlQuery seleziona_iddoc;
    seleziona_iddoc.prepare("Select UsernameDoc from Pazienti where Codice_ID = '"+dati::ind+"'");
    seleziona_iddoc.exec();
    while(seleziona_iddoc.next()) {
      user_doc_string = seleziona_iddoc.value(0).toString();
    }
     associa_user << user_doc_string;
     associa_user << dati::username;
       qDebug()<< associa_user;
      // devo creare una string list in cui aggiungo usernamedoc selezionato da query e username doc corrente,
      //poi salvo nel db (e se crea problemi converto in stringa ma non dovrebbe) e poi capisco come rifermi a un elemento della stringa
      //quando poi devo selezionare i dati
      user_doc_string += " " + dati::username;
        QSqlQuery update;
          //vai avanti da qui
          update.prepare("Update Pazienti set UsernameDoc = '"+user_doc_string+"' where Codice_ID = '"+dati::ind+"'");
            update.exec();
              if (update.exec())
                { QMessageBox ::information(this,tr("Salvato"),tr("Paziente associato al corrente username"));
                }
                else {
                  QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
                  qDebug()<< update.lastError();
              }

      qDebug()<< user_doc_string;
}



void paginaprincipale::on_pushButton_indietro_2_clicked()
{ qDebug()<< curTut;
  qDebug()<< curImg;
  if(curImg != 0) {
    curImg --;
    qDebug()<<curImg;


    key2 = sel_tut.at(curTut);
     qDebug() << key2;
     if(TutInfoMap.find(key2) != TutInfoMap.end()) {
    TutInfo &one2 = TutInfoMap[key2];

    if(curImg <  one2.img.size()){
             ui->label_img_tut -> setPixmap(one2.img.at(curImg));

    qDebug() <<curTut;} }

  }

  else if(curImg ==0 && curTut != 0)
  {curTut --;

  key2 = sel_tut.at(curTut);
   qDebug() << key2;
   if(TutInfoMap.find(key2) != TutInfoMap.end()) {
  TutInfo &one2 = TutInfoMap[key2];

  if(curImg < one2.img.size()){
           ui->label_img_tut -> setPixmap(one2.img.at(curImg));

  qDebug() <<curTut;} }

   }
  else {
   qDebug()<< "stop";
  }



}


void paginaprincipale::on_pushButton_prosegui_clicked()
{
    ui->tabWidget_2->setCurrentWidget(ui->tab_init);
}

void paginaprincipale::on_pushButton_go_clicked()
{
    ui->tabWidget_2->setCurrentWidget(ui->tab_parametri);
}

