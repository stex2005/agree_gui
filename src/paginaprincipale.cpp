#include "../include/agree_gui/paginaprincipale.h"
#include "ui_paginaprincipale.h"
#include "../include/agree_gui/login.h"
#include "../include/agree_gui/main_window.hpp"
//#include "../include/agree_gui/sc_assistivo.h"
#include <QMessageBox>
#include <QPixmap>



#include <iostream>
#include <map>
#include <string>
#include <iterator>


int flag;
int prova;
QString dati::codice_id;
QString dati::ind;
QString dati::NomeP, dati::CognomeP, dati::data1;
QString dati::uservecchio;
QString dati::count_act;
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
QString dati::mood;
QString dati::mood_prec;
QString dati::ex1, dati::ex2, dati::ex3, dati::ex4, dati::ex5, dati::ex6, dati::ex7;
QString dati::num_ex1, dati::num_ex2, dati::num_ex3, dati::num_ex4, dati::num_ex5, dati::num_ex6, dati::num_ex7;

QString dati::rip1, dati::rip2, dati::rip3, dati::rip4, dati::rip5, dati::rip6, dati::rip7;
paginaprincipale::paginaprincipale(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::paginaprincipale)
{
  ui->setupUi(this);
  ui->tabWidget->setCurrentWidget(ui->tab);
  ui->stackedWidget->setCurrentWidget(ui->page_3);





  // prova immagini
  QPixmap pic1("/home/alice/catkin_ws/src/agree_gui/resources/images/img/sedia/sedia1.png");
  ui->label_spalla->setPixmap(pic1);


  //creo la data
  QDate data;
data= QDate::currentDate();
 dati::data1= data.toString(Qt::ISODate);
ui->label_date->setText(data.toString());


//  QSqlDatabase mydb2 = QSqlDatabase::database();
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
      QMessageBox ::information(this,tr("Save"),tr("Salvato"));
      ui->stackedWidget->setCurrentWidget(ui->page_3);
      QSqlQuery qryc;
      qryc.prepare("insert into Count (username,cont) values('"+dati::codice_id+"', '"+dati::count+"')");
      qryc.exec();
      }
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
   }
 if (flag==2) {
   qDebug()<<dati::count_act;
  dati::codice_id= dati::NomeP+ dati::CognomeP+ dati::sigla+ dati::count_act;
  qDebug()<<dati::codice_id;

      QSqlQuery qry6;
      qry6.prepare("update Pazienti set Codice_ID= '"+dati::codice_id+"', NomePaziente ='"+dati::NomeP+"', Cognome= '"+dati::CognomeP+"', DatadiNascita= '"+Data+"',  Patologia = '"+Patologia+"', Sesso='"+Sesso+"', Lato_paretico = '"+Lato+"', StoriaClinica = '"+storiaclinica+"', LunghezzaBraccio ='"+Lunghezza_braccio+"', LunghezzaAvambraccio = '"+Lunghezza_avambraccio+"' where Codice_ID = '"+dati::ind+"'");
      if (qry6.exec())
      {
        QMessageBox ::information(this,tr("Modifica"),tr("Modificato Correttamente"));
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
{
  //carico la tabella dei pazienti
      QSqlQueryModel *model = new QSqlQueryModel();
      QSqlQuery * qry1 = new QSqlQuery(mydb2);
      qry1 -> prepare("select Codice_ID, NomePaziente, Cognome, DatadiNascita, Patologia, Sesso, Lato_paretico, LunghezzaBraccio, LunghezzaAvambraccio, StoriaClinica from Pazienti where UsernameDOC = '"+dati::username+"' order by Cognome  asc");
      qry1 -> exec();
      model -> setQuery(*qry1);
      ui->tableView_database->setModel(model);
    //  qDebug() << (model->rowCount());
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
      QMessageBox::StandardButton risposta= QMessageBox::question(this,tr("Conferma"), tr("Si è scelto eliminare i dati relativi al paziente : %1 %2") .arg(dati::NomeP).arg(dati::CognomeP), QMessageBox::Yes | QMessageBox::No);
      if (risposta==QMessageBox::Yes)
      {
        QSqlQuery qry4;
        qry4.prepare("delete from Pazienti where Codice_ID ='"+dati::ind+"'");
        qry4.exec();

        QSqlQuery qry5;
        qry5.prepare("delete from Parametri_Paziente where Codice_ID ='"+dati::ind+"'");
        qry5.exec();
        QMessageBox ::information(this,tr("Eliminato"),tr("Eliminato"));
        QMessageBox::information(this, tr("Information"), tr("Premere Elenco Pazienti per aggiornare il database dei Pazienti"));

      }
      else if(risposta==QMessageBox::No)
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
    QMessageBox ::information(this,tr("Modifica"),tr("Modificato Correttamente"));
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
      ui->label_status2->setText(qry7.value(0).toString()+ " "+ qry7.value(1).toString());
      QMessageBox::StandardButton risposta= QMessageBox::question(this,tr("Conferma"), tr("Si è scelto di iniziare la sessione di terapia del paziente : %1 %2") .arg(dati::NomeP).arg(dati::CognomeP), QMessageBox::Yes | QMessageBox::No);
      if (risposta==QMessageBox::Yes)
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
            dati::modulo_spalla_prec = selezione.value(13).toString();
            dati::modulo_gomito_prec = selezione.value(14).toString();
            dati::modulo_polso_prec = selezione.value(15).toString();
            dati::modulo_eeg_prec = selezione.value(16).toString();
            dati::modulo_emg_prec = selezione.value(17).toString();
            dati::mano_prec = selezione.value(18).toString();
            dati::oi_prec = selezione.value(19).toString();
            dati::mood_prec = selezione.value(20).toString();
            dati::l_eeg_p = dati::modulo_eeg_prec.length();
            dati::l_emg_p = dati::modulo_emg_prec.length();
            dati::l_m_p = dati::mano_prec.length();
            dati::l_oi_p = dati::oi_prec.length();
            dati::ex1_prec= selezione.value(21).toString();
            dati::rip1_prec = selezione.value(22).toString();
            dati::ex2_prec = selezione.value(23).toString();
            dati::rip2_prec = selezione.value(24).toString();
            dati::ex3_prec= selezione.value(25).toString();
            dati::rip3_prec = selezione.value(26).toString();
            dati::ex4_prec = selezione.value(27).toString();
            dati::rip4_prec = selezione.value(28).toString();
            dati::ex5_prec= selezione.value(29).toString();
            dati::rip5_prec = selezione.value(30).toString();
            dati::ex6_prec = selezione.value(31).toString();
            dati::rip6_prec = selezione.value(32).toString();
            dati::ex7_prec= selezione.value(33).toString();
            dati::rip7_prec = selezione.value(34).toString();
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
                  ui->tabWidget_2->setCurrentWidget(ui->tab_parametri);
                }
             }
        }
 if (flag==4)
 {

     QSqlQuery insert;
     insert.prepare("insert into Parametri_Paziente (Codice_ID, UsernameDoc, Data_acquisizione) values ('"+dati::ind+"', '"+dati::username+"', '"+dati::data1+"')");

     if (insert.exec())
     {
       ui->tabWidget->setCurrentWidget(ui->tab_2);
       ui->tabWidget_2->setCurrentWidget(ui->tab_parametri);
     }


      else if(risposta==QMessageBox::No){
        ui->tabWidget->setCurrentWidget(ui->tab);
        ui->stackedWidget->setCurrentWidget(ui->page_3);
      }
    }
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
{
    ui->tabWidget_2->setCurrentWidget(ui->tab_init);
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
         ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);
       }
       else {
          QMessageBox ::critical(this,tr("Errore"),tr("bo3"));
        }
        if (flag==4)
        {  ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);

          if(dati::modulo_spalla_prec=="1")
          {
            dati::modulo_prec1= "Spalla";

            ui->checkBox_spalla->setChecked(true);
          }
          if (dati::modulo_gomito_prec== "1") {
            dati::modulo_prec1 = "Spalla e Gomito";

            ui-> checkBox_gomito ->setChecked(true);
          }
          if (dati::modulo_polso_prec=="1") {
            dati::modulo_prec1 = "Spalla, Gomito e Polso";

            ui->checkBox_polso->setChecked(true);
          }

                   if (dati::modulo_emg_prec=="EMG")
                   {
                     ui->checkBox_emg->setChecked(true);
                   }
                   else if(dati::modulo_eeg_prec=="EEG")
                   {
                     ui->checkBox_eeg->setChecked(true);
                   }
                   else {
                     ui->checkBox_eeg->setChecked(false);
                     ui->checkBox_emg->setChecked(false);
                   }
                   if(!(dati::l_m_p==0))
                   {
                     ui->checkBox_MAP->setChecked(true);
                     prova= 5;
                   }
                   else {
                     ui->checkBox_MAP->setChecked(false);
                   }
                   if(!(dati::l_oi_p==0))
                   {
                     ui->checkBox_oi->setChecked(true);
                   }
                   else {
                     ui->checkBox_oi->setChecked(false);
                   }

        }
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

void paginaprincipale::on_pushButton_save_clicked()
{
    if(ui->checkBox_eeg->isChecked())
    {
      dati::modulo_extra= "EEG";
      QSqlQuery moduli;
      moduli.prepare("update Parametri_Paziente set EEG='"+dati::modulo_extra+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");

     moduli.exec();

            if (moduli.exec())
            {

           QMessageBox ::information(this,tr("Salvato"),tr("Configurazione del Modulo Extra EEG salvata"));
           ui->checkBox_eeg->setChecked(false);

           }
           else {
              QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
            }

    }
    if(ui->checkBox_emg->isChecked())
    {
      dati::modulo_extra= "EMG";
      QSqlQuery moduli;
      moduli.prepare("update Parametri_Paziente set EMG='"+dati::modulo_extra+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");

     moduli.exec();

            if (moduli.exec())
            {

             QMessageBox ::information(this,tr("Salvato"),tr("Configurazione del Modulo Extra EMG salvata"));
              ui->checkBox_emg->setChecked(false);
           }
           else {
              QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
            }
    }
    if(ui->checkBox_MAP->isChecked() ||  (prova == 5))
    {
      //|| (dati::modulo_prec== "S-P-G")
      if(dati::modulo_polso == "1")
      {
      dati::mano = "mano";
     QSqlQuery moduli;
      moduli.prepare("update Parametri_Paziente set Mano='"+dati::mano+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");

     moduli.exec();

            if (moduli.exec())
            {

            QMessageBox ::information(this,tr("Salvato"),tr("Configurazione del Modulo Extra MAP salvata"));
            ui->checkBox_MAP->setChecked(false);
           }
           else {
              QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
            }
      }
 //|| (dati::modulo_prec== "S-G") || (dati::modulo_prec=="S")

      else if (dati::modulo_polso == "0" ) {
        qDebug()<< "qui";
        QMessageBox::StandardButton risposta= QMessageBox::question(this,tr("Attenzione"), tr("Il modulo extra: Mano non può essere attivato se la configurazione dei moduli moduli meccanici non comprende anche il Modulo : Polso. Si desidera modificare la configurazione dei Moduli Meccanici? "));
        if (risposta==QMessageBox::Yes)
        {
            flag=6;
           // ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);
      }
        else if (risposta==QMessageBox::No) {
          ui->checkBox_MAP->setChecked(false);
        }
      }

    }
    if(ui->checkBox_oi->isChecked())
    {
      dati::oi = "oi";

      QSqlQuery moduli;
      moduli.prepare("update Parametri_Paziente set Oggetti_int='"+dati::oi+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");

     moduli.exec();

            if (moduli.exec())
            {

            QMessageBox ::information(this,tr("Salvato"),tr("Configurazione del Modulo Extra: Oggetti Interattattivi salvata"));
             ui->checkBox_oi->setChecked(false);
           }
           else {
              QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
            }
    }
    if (flag==6)
   {
       ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);


    }
    else {

   ui->tabWidget_2->setCurrentWidget(ui->tab_tutorial);
    }
}

void paginaprincipale::on_pushButton_continua_clicked()
{   qDebug() << flag;
    ui->tabWidget_2->setCurrentWidget(ui->tab_controllo);
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
ui->tabWidget_2->setCurrentWidget(ui->tab_controllo);

    }

}

void paginaprincipale::on_pushButton_salvaex_clicked()
{

 if(ui->checkBox_ex1->isChecked())
 {
   dati::ex1 = ui->comboBox_ex1->currentText();

   dati::rip1= ui->lineEdit_ex1->text();
   QSqlQuery selezione1;
   selezione1.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex1+"'");
   selezione1.exec();
   if (selezione1.exec()) {
     while(selezione1.next())
     {
     dati::num_ex1 = selezione1.value(0).toString();

       }
     if(dati::rip1.toInt()< 30) {
     QSqlQuery es1;
     es1.prepare("update Parametri_Paziente set ex1 = '"+dati::num_ex1+"' , rip1 = '"+dati::rip1+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
     es1.exec();
     if(es1.exec())
     {
       QMessageBox ::information(this,tr("Salvato"),tr("esercizio salvato"));
     }
     else {
       QMessageBox ::critical(this,tr("Errore"),tr("errore"));
     }
     }
     else if(dati::rip1.toInt()>30)
     {
       QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni del primo esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));


          }
   }




 }
 if(ui->checkBox_ex2->isChecked())
 {
   dati::ex2 = ui->comboBox_ex2->currentText();

   dati::rip2= ui->lineEdit_ex2->text();
   QSqlQuery selezione2;
   selezione2.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex2+"'");
   selezione2.exec();
   if (selezione2.exec()) {
     while(selezione2.next())
     {
     dati::num_ex2 = selezione2.value(0).toString();


       }
     if(dati::rip2.toInt()<30) {
     QSqlQuery es2;
     es2.prepare("update Parametri_Paziente set ex2 = '"+dati::num_ex2+"' , rip2 = '"+dati::rip2+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
     es2.exec();
     if(es2.exec())
     {
       QMessageBox ::information(this,tr("Salvato"),tr("esercizio salvato"));
     }
     else {
       QMessageBox ::critical(this,tr("Errore"),tr("errore"));
     }
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
   QSqlQuery selezione3;
   selezione3.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex3+"'");
   selezione3.exec();
   if (selezione3.exec()) {
     while(selezione3.next())
     {
     dati::num_ex3 = selezione3.value(0).toString();


       }
     if(dati::rip3.toInt()<30) {
     QSqlQuery es3;
     es3.prepare("update Parametri_Paziente set ex3 = '"+dati::num_ex3+"' , rip3 = '"+dati::rip3+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
     es3.exec();
     if(es3.exec())
     {
       QMessageBox ::information(this,tr("Salvato"),tr("esercizio salvato"));
     }
     else {
       QMessageBox ::critical(this,tr("Errore"),tr("errore"));
     }
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
  QSqlQuery selezione4;
  selezione4.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex4+"'");
  selezione4.exec();
  if (selezione4.exec()) {
    while(selezione4.next())
    {
    dati::num_ex4 = selezione4.value(0).toString();


      }
    if (dati::rip4.toInt()<30) {
    QSqlQuery es4;
    es4.prepare("update Parametri_Paziente set ex4 = '"+dati::num_ex4+"' , rip4 = '"+dati::rip4+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    es4.exec();
    if(es4.exec())
    {
      QMessageBox ::information(this,tr("Salvato"),tr("esercizio salvato"));
    }
    else {
      QMessageBox ::critical(this,tr("Errore"),tr("errore"));
    }
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
  QSqlQuery selezione5;
  selezione5.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex5+"'");
  selezione5.exec();
  if (selezione5.exec()) {
    while(selezione5.next())
    {
    dati::num_ex5 = selezione5.value(0).toString();


      }
    if(dati::rip5.toInt()<30) {
    QSqlQuery es5;
    es5.prepare("update Parametri_Paziente set ex5 = '"+dati::num_ex5+"' , rip5 = '"+dati::rip5+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    es5.exec();
    if(es5.exec())
    {
      QMessageBox ::information(this,tr("Salvato"),tr("esercizio salvato"));
    }
    else {
      QMessageBox ::critical(this,tr("Errore"),tr("errore"));
    }
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
  QSqlQuery selezione6;
  selezione6.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex6+"'");
  selezione6.exec();
  if (selezione6.exec()) {
    while(selezione6.next())
    {
    dati::num_ex6 = selezione6.value(0).toString();


      }
    if(dati::rip6.toInt()<30) {
    QSqlQuery es6;
    es6.prepare("update Parametri_Paziente set ex6 = '"+dati::num_ex6+"' , rip6 = '"+dati::rip6+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    es6.exec();
    if(es6.exec())
    {
      QMessageBox ::information(this,tr("Salvato"),tr("esercizio salvato"));
    }
    else {
      QMessageBox ::critical(this,tr("Errore"),tr("errore"));
    }
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
  QSqlQuery selezione7;
  selezione7.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex7+"'");
  selezione7.exec();
  if (selezione7.exec()) {
    while(selezione7.next())
    {
    dati::num_ex7 = selezione7.value(0).toString();


      }
    if(dati::rip7.toInt()<30) {
    QSqlQuery es7;
    es7.prepare("update Parametri_Paziente set ex7 = '"+dati::num_ex7+"' , rip7 = '"+dati::rip7+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    es7.exec();
    if(es7.exec())
    {
      QMessageBox ::information(this,tr("Salvato"),tr("esercizio salvato"));
    }
    else {
      QMessageBox ::critical(this,tr("Errore"),tr("errore"));
    }
    }
    else if(dati::rip7.toInt()>30)
    {
      QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
    }
  }

}
qDebug()<< dati::ind;

QSqlQuery esercizi;
esercizi.prepare("select ex1,rip1,ex2,rip2,ex3,rip3,ex4,rip4,ex5,rip5,ex6,rip6,ex7,rip7 from Parametri_Pazienti where Codice_ID = '"+dati::ind+"'");
if(esercizi.exec()){
while(esercizi.next())
{ ExInfo cur;
  QString EX1 = esercizi.value(0).toString();
  int RIP1 = esercizi.value(1).toInt();
  qDebug()<<EX1;
  if ( ! EX1.isEmpty() ){
  // FILL IT
  cur.EX = EX1; // fill it
  cur.REP = RIP1;
  ExInfoMap[EX1].images = GetImages(EX1);
  ExInfoMap[EX1] = cur; // now we add it

  }
  else return;

  QString EX2 = esercizi.value(2).toString();
  int RIP2 = esercizi.value(3).toInt();
  if(!EX2.isEmpty()) {
  // FILL IT
  cur.EX = EX2; // fill it
  cur.REP = RIP2;
  ExInfoMap[EX2].images = GetImages(EX2);  // use ID to get images  /////////////////////////////////////////////// IMAGES
  ExInfoMap[EX2] = cur; // now we add it
  }
  else return;
  QString EX3 = esercizi.value(4).toString();
  int RIP3 = esercizi.value(5).toInt();
  if(!EX3.isEmpty()) {
  // FILL IT
  cur.EX = EX3; // fill it
  cur.REP = RIP3;
   ExInfoMap[EX3].images = GetImages(EX3);
  ExInfoMap[EX3] = cur; // now we add it


  }
  else return;
  QString EX4 = esercizi.value(6).toString();
  int RIP4 = esercizi.value(7).toInt();
  if(!EX4.isEmpty()) {
  // FILL IT
  cur.EX = EX4; // fill it
  cur.REP = RIP4;
  ExInfoMap[EX4].images = GetImages(EX4);
  ExInfoMap[EX4] = cur; // now we add it


  }
  else return;
  QString EX5 = esercizi.value(8).toString();
  int RIP5 = esercizi.value(9).toInt();
  if(!EX5.isEmpty()){
  // FILL IT
  cur.EX = EX5; // fill it
  cur.REP = RIP5;
   ExInfoMap[EX5].images = GetImages(EX5);
  ExInfoMap[EX5] = cur; // now we add it


  }
  else return;
  QString EX6 = esercizi.value(10).toString();
  int RIP6 = esercizi.value(11).toInt();
  if(!EX6.isEmpty()) {
  // FILL IT
  cur.EX = EX6; // fill it
  cur.REP = RIP6;
  ExInfoMap[EX6].images = GetImages(EX6);
  ExInfoMap[EX6] = cur; // now we add it


  }
  else return;
  QString EX7 = esercizi.value(12).toString();
  int RIP7 = esercizi.value(13).toInt();
  if(!EX7.isEmpty()) {
  // FILL IT
  cur.EX = EX7; // fill it
  cur.REP = RIP7;
  ExInfoMap[EX7].images = GetImages(EX6);
  ExInfoMap[EX7] = cur; // now we add it
  }
  else return;
}
}
else qDebug()<<esercizi.lastError();



  ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);


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
    dati::mood = "Assisted ad needed";
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






}


void paginaprincipale::on_pushButton_salvamoduli_clicked()
{ if(ui->checkBox_spalla->isChecked())
  {
    dati::modulo_spalla= "1";
    QSqlQuery modulo;
    modulo.prepare("update Parametri_Paziente set Modulo_Spalla= '"+dati::modulo_spalla+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    modulo.exec();
        if (modulo.exec())
        {

         QMessageBox ::information(this,tr("Salvato"),tr("Configurazione del modulo meccanico Spalla salvata"));

        //  ui->tabWidget_2->setCurrentWidget(ui->tab_m_extra);

       }
       else {
          QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
        }

  }
  else
  {
    dati::modulo_spalla = "0";
        QSqlQuery modulo;
        modulo.prepare("update Parametri_Paziente set Modulo_Spalla= '"+dati::modulo_spalla+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
        modulo.exec();
            if (modulo.exec())
            {

        //     QMessageBox ::information(this,tr("Salvato"),tr("Configurazione del modulo meccanico Spalla salvata"));

            //   ui->tabWidget_2->setCurrentWidget(ui->tab_m_extra);

           }
           else {
              QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
            }

  }
  if (ui->checkBox_gomito->isChecked())
  {
    dati::modulo_gomito = "1";
    QSqlQuery modulo;
    modulo.prepare("update Parametri_Paziente set Modulo_gomito= '"+dati::modulo_gomito+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    modulo.exec();
        if (modulo.exec())
        {

         QMessageBox ::information(this,tr("Salvato"),tr("Configurazione del modulo meccanico Gomito salvata"));

        //  ui->tabWidget_2->setCurrentWidget(ui->tab_m_extra);

       }
       else {
          QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
        }
  }
  else
  {
    dati::modulo_gomito = "0";
    QSqlQuery modulo;
    modulo.prepare("update Parametri_Paziente set Modulo_gomito= '"+dati::modulo_gomito+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    modulo.exec();
        if (modulo.exec())
        {

       //  QMessageBox ::information(this,tr("Salvato"),tr("Configurazione del modulo meccanico Gomito salvata"));

        //  ui->tabWidget_2->setCurrentWidget(ui->tab_m_extra);

       }
       else {
          QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
        }
  }
  if (ui->checkBox_polso->isChecked())
  {
    dati::modulo_polso= "1";
    QSqlQuery modulo;
    modulo.prepare("update Parametri_Paziente set Modulo_polso= '"+dati::modulo_polso+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    modulo.exec();
        if (modulo.exec())
        {

         QMessageBox ::information(this,tr("Salvato"),tr("Configurazione del modulo meccanico Polso salvata"));

        //  ui->tabWidget_2->setCurrentWidget(ui->tab_m_extra);

       }
       else {
          QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
        }
  }
  else
  {
    dati::modulo_polso = "0";
    QSqlQuery modulo;
    modulo.prepare("update Parametri_Paziente set Modulo_polso= '"+dati::modulo_polso+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    modulo.exec();
        if (modulo.exec())
        {

       //  QMessageBox ::information(this,tr("Salvato"),tr("Configurazione del modulo meccanico Polso salvata"));

        //  ui->tabWidget_2->setCurrentWidget(ui->tab_m_extra);

       }
       else {
          QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
        }
  }
  ui->tabWidget_2->setCurrentWidget(ui->tab_m_extra);

  if (flag==6)
  {
    if (dati::modulo_emg_prec=="EMG")
    {
      ui->checkBox_emg->setChecked(true);
    }
    else if(dati::modulo_eeg_prec=="EEG")
    {
      ui->checkBox_eeg->setChecked(true);
    }
    else {
      ui->checkBox_eeg->setChecked(false);
      ui->checkBox_emg->setChecked(false);
    }
    if(!(dati::l_m_p==0))
    {
      ui->checkBox_MAP->setChecked(true);
      flag= 5;
    }
    else {
      ui->checkBox_MAP->setChecked(false);
    }
    if(!(dati::l_oi_p==0))
    {
      ui->checkBox_oi->setChecked(true);
    }
    else {
      ui->checkBox_oi->setChecked(false);
    }
  }
}

QList<QPixmap>GetImages(QString exID) {
  QList<QPixmap> mylist;
QDir directory("/home/alice/Desktop/ex_img" + exID);
QStringList images = directory.entryList(QStringList() << ".jpg" << ".JPG",QDir::Files);
foreach(QString filename, images) {
QPixmap pix(filename);
mylist.append(pix);

}
return mylist;

}
