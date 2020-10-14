#include "../include/agree_gui/paginaprincipale.h"
#include "ui_paginaprincipale.h"
#include "../include/agree_gui/login.h"
#include "../include/agree_gui/main_window.hpp"
#include "../include/agree_gui/sc_assistivo.h"
#include "../include/agree_gui/matrixwidget.h"
#include "../include/agree_gui/qnode.hpp"
#include <QMessageBox>
#include <QFloat16>
#include <QMovie>

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
//int8_t dati::status1;
int8_t dati::command_pp = 0, dati::command_old_pp = 1;
int8_t dati::command_exercise_pp = 0, dati::command_task_pp= 0;
int8_t dati::command_exercise_old_pp, dati::command_task_old_pp;
int8_t dati::flag_ex=0;

 SignalHelper *helper;

 void paginaprincipale::callback2(const agree_gui::agree_gui_command msg_command_pp) {
   ros::NodeHandle n;
 //  dati::command_old_pp = 1;
   dati::command_pp = msg_command_pp.mode;
   dati::command_exercise_pp = msg_command_pp.exercise;
   dati::command_task_pp = msg_command_pp.task;
     if((dati::command_old_pp) != (dati::command_pp) || (dati::command_exercise_old_pp)!= (dati::command_exercise_pp) || (dati::command_task_old_pp)!= (dati::command_task_pp)) {
       qDebug()<< dati::command_old_pp;
       qDebug()<< dati::command_pp;
       dati::command_old_pp=dati::command_pp;
       dati::command_task_old_pp = dati::command_task_pp;
       dati::command_exercise_old_pp = dati::command_exercise_pp;
       ROS_INFO("I heard: %d PAGINA PRINCIPALE", dati::command_pp);

       if(dati::command_old_pp ==2) {
         ui->tabWidget->setCurrentWidget(ui->tab);
         QSqlQuery prova;
         prova.prepare("select Nome, Cognome from Users where Username = '"+dati::username+"' and Password = '"+dati::password+"'");
         prova.exec();
         if (prova.exec()) {
           qDebug()<< "sono nella query prova";
           while(prova.next()) {
           ui->label_status->setText("Terapista: " + prova.value(0).toString() + " " +  prova.value(1).toString());
         } }
         else qDebug()<< prova.lastError();
         this->show();
       }
   if (dati::command_old_pp ==3) {
      ui->tabWidget_2->setCurrentWidget(ui->tab_vestizione);

   }
   if(dati::command_old_pp == 4) {
     ui->tabWidget_2->setCurrentWidget(ui->tab_parametri);

   }
   if(dati::command_old_pp == 5) {
     ui->tabWidget_2->setCurrentWidget(ui->tab_controllo);
   }
   if(dati::command_old_pp == 6){
     ui->tabWidget_2->setCurrentWidget(ui->tab_calibrazione);

   }
   if(dati::command_old_pp == 7) {
      ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
      dati::status1 = 7;
    msg_status_pp.data = dati::status1;
    ROS_INFO ("%d", msg_status_pp.data);
    status_publisher.publish(msg_status_pp);
   }

   if(dati::command_old_pp == 11) {
     ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
   }
   if(dati::command_old_pp ==12){

//     dati::command_exercise_pp = msg_command_pp.exercise;
//     dati::command_task_pp = msg_command_pp.task;
}
   if(dati::command_old_pp == 14){
     timer_rehab->stop();
   ui->tabWidget_2->setCurrentWidget(ui->tab_valutazione);
   //    //carico la tabella dei parametri cinematici  dei pazienti
          QSqlQueryModel *model1 = new QSqlQueryModel();
          QSqlQuery * qry_val = new QSqlQuery(mydb2);
           qry_val -> prepare("select Intrajoint_coordination, Normalized_jerk, Movement_arrest_period_ratio, Peak_speed_ratio, Acceleration_metric from Valutazioni  where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' order by Data_acquisizione desc limit 1 ");
           qry_val -> exec();
           if(qry_val->exec()) {
           model1 -> setQuery(*qry_val);
           ui->tableView_valutazioni->setModel(model1);
           ui->tableView_valutazioni->resizeColumnsToContents(); }
           else qDebug()<<qry_val->lastError();
         //  qDebug() << (model->rowCount());
       // carico la tabella dei parametri EMG dei pazienti
           QSqlQueryModel *model2 = new QSqlQueryModel();
           QSqlQuery * qry_val_emg = new QSqlQuery(mydb2);
           qry_val_emg -> prepare ("select Per_corretta_attivazione_muscolare, Normalized_EMG_action_level, Indice_co_contrazione, Sinergie_muscolari, Active_movement_Idex from Valutazioni where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' order by Data_acquisizione desc limit 1 ");
           qry_val_emg-> exec();
           if(qry_val_emg-> exec()) {
           model2 -> setQuery(*qry_val_emg);
           ui->tableView_parametriEMG-> setModel(model2);
           ui->tableView_parametriEMG-> resizeColumnsToContents();


           }}
   }

   //   if(dati::command_old == 8) {

   //     n.getParam("/point1/mat_coordinates", point1);
   //     n.getParam("/point2/mat_coordinates", point2);
   //     n.getParam ("/point3/mat_coordinates", point3);
   //     qDebug()<< point1;
   //     dati::status1 = 8;

   //         std_msgs::Int8 msg;
   //         msg.data = dati::status1;
   //         ROS_INFO ("%d", msg.data);
   //         status_publisher.publish(msg);

   //   }
   //   if(dati::command_old == 9) {
   //     n.setParam("/point1/mat_coordinates", point1);
   //     n.setParam("/point2/mat_coordinates", point2);
   //     n.setParam("/point3/mat_coordinates", point3);
   //   }
 }



paginaprincipale::paginaprincipale(QWidget *parent) :


  QDialog(parent),

  ui(new Ui::paginaprincipale)



{


  ui->setupUi(this);
  ui->tabWidget->setCurrentWidget(ui->tab);
  ui->stackedWidget->setCurrentWidget(ui->page_3);
//  MatrixWidget * matrix = new MatrixWidget (this);
     ui->verticalLayout->addWidget(matrix);
     // ho aggiunto questi
     ros::NodeHandle n;
status_publisher = n.advertise<std_msgs::Int8>("/gui/status", 1000);
//definisco topic

//definisco topic da cui faccio subscribe

 command_subscriber = n.subscribe("/gui/command", 1000, &paginaprincipale::callback2, this); //creo il topic a cui faccio il subscribe


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

connect(ui->checkBox_ex1, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex()));
connect(ui->checkBox_ex2, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex()));
connect(ui->checkBox_ex3, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex()));
connect(ui->checkBox_ex4, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex()));
connect(ui->checkBox_ex5, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex()));
connect(ui->checkBox_ex6, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex()));
connect(ui->checkBox_7, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex()));

//timer = new QTimer(this);
timer_init = new QTimer(this);
timer_rehab = new QTimer(this);
timer_val = new QTimer(this);
timer_feedback = new QTimer(this);
ROS_INFO("TIMER");
// setup signal and slot
//connect(timer, SIGNAL(timeout()),
      //this, SLOT(next_img()));

connect(timer_init,SIGNAL(timeout()), this, SLOT(skip_init()));

connect(timer_rehab, SIGNAL(timeout()),this,SLOT(next_img()));

connect(timer_val, SIGNAL(timeout()), this,  SLOT(show_val()));

connect(timer_feedback, SIGNAL(timeout()), this, SLOT(show_feed()));
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

    QPixmap pic6("/home/alice/catkin_ws/src/agree_gui/resources/images/img/arm/bracciodx.png");
    ui->label_4_dx_3->setPixmap(pic6);

    QPixmap pic7("/home/alice/catkin_ws/src/agree_gui/resources/images/img/ROM/flesso-estensionespalla.png");
    ui->label_13->setPixmap(pic7);

    QPixmap pic8("/home/alice/catkin_ws/src/agree_gui/resources/images/img/ROM/nuova.png");
    ui->label_14->setPixmap(pic8);

    QPixmap pic9("/home/alice/catkin_ws/src/agree_gui/resources/images/img/ROM/rotazionespalla.png");
    ui->label_15->setPixmap(pic9);

    QPixmap pic10("/home/alice/catkin_ws/src/agree_gui/resources/images/img/ROM/gomito.png");
    ui->label_17->setPixmap(pic10);

    QPixmap pic11("/home/alice/catkin_ws/src/agree_gui/resources/images/img/ROM/polso.png");
    ui->label_16->setPixmap(pic11);

    QPixmap pic12("/home/alice/Desktop/init_agree4.png");
    ui->label_wait->setPixmap(pic12);

// setto icone
   ui->pushButton_cerca_3->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Zoom.png"));
   ui->pushButton_elencoPazienti->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Database.png"));
   ui->pushButton_eliminapaziente->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Delete.png"));
   ui->pushButton_utente->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Person.png"));
   ui->pushButton_home->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Home.png"));
   ui->pushButton_nuovopaziente->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Add.png"));
   ui->pushButton_modifica->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Modify.png"));
   ui->pushButton_vestizioneAgree->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Movie.png"));
   ui->pushButton_salva->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Save.png"));
   ui->pushButton_salva_2->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Save.png"));
   ui->pushButton_salvamoduli->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Save.png"));
   ui->pushButton_salvaconf->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Save.png"));
   ui->pushButton_controllo->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Save.png"));
   ui->pushButton_salvaex->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Save.png"));
   ui->pushButton_salvatapp->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Save.png"));
   ui->pushButton_salta->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Forward.png"));
   ui->pushButton_indietro_2->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Back.png"));
   ui->pushButton_prosegui->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Fast-forward.png"));
   ui->pushButton_go->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Forward"));
   ui->pushButton_logout->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Turn off"));
   ui->pushButton_go->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Fast-forward"));
   ui->pushButton_avanti_v->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Forward"));
   ui->pushButton->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Stop sign"));
   ui->pushButton_add->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Add"));
   ui->pushButton_remove->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Remove"));

  //creo la data
  QDate data;
data= QDate::currentDate();
 dati::data1= data.toString(Qt::ISODate);
ui->label_date->setText(data.toString());


  QSqlDatabase mydb2 = QSqlDatabase::database();
}

paginaprincipale::~paginaprincipale()
{
  delete ui;
}

/**********************       INSERISCO NUOVO PAZIENTE            *********************/
void paginaprincipale::on_pushButton_nuovopaziente_clicked()
{    ROS_INFO("NUOVOPAZIENTE");
     qDebug()<< "nuovopaziente";
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

/**********************       SALVO PAZIENTE (NUOVO E MODIFICA)  *********************/
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
// se esiste già non  eseguo la  query
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

/**********************      CARICO TABELLA PAZIENTI                       *********************/
void paginaprincipale::on_pushButton_elencoPazienti_clicked()
{   // prova_signal();
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

/**********************       ATTIVO DOPPIO CLICK TABELLA                 *********************/
void paginaprincipale::on_tableView_database_activated(const QModelIndex &index)
{
     dati::ind= ui-> tableView_database->model()->data(index).toString();
 flag= 3; //paziente selezionato
}

/**********************       ELIMINO PAZIENTE                      *********************/
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

/**********************       MODIFICO PAZIENTE                       *********************/
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

/**********************       DICHIARO DATI UTENTE                       *********************/
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
         QString profilo = qry3.value(5).toString();
         if(profilo == "1") ui->radioButton_terapista->setChecked(true);
         else if(profilo == "2") ui->radioButton_tecnico->setChecked(true);
         else if(profilo == "3") ui->radioButton_utente->setChecked(true);
       } }
     else
     {
         QMessageBox ::critical(this,tr("Errore"),tr("boh3"));
     }
         QSqlQuery prova1;
         prova1.prepare("select cont from Count where username = '"+dati::username+"'");
         prova1.exec();
         while(prova1.next())
        {
           dati::count_act= prova1.value(0).toString();
           qDebug()<< dati::count_act;
      }
}

/**********************       SALVO DATI UTENTE NUOVI                       *********************/
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
  qDebug()<< dati::username;

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
      prova2.prepare("update Pazienti set UsernameDoc = '"+dati::username+"' where UsernameDoc = '"+dati::uservecchio+"'" );
      prova2.exec();
    }
  }
  else
  {
    QMessageBox ::critical(this,tr("Errore"),tr("bo3"));
  }

    ui->label_status->setText(QString("Utente: %1 %2").arg(dati::Nome) .arg(dati::Cognome));
}

/**********************       INIZIO SEDUTA RIABILITATIVA                       *********************/
void paginaprincipale::on_pushButton_vestizioneAgree_clicked()
{   //  if (dati::command == 3){
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
           //  }
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
                  if(!(dati::mano_prec=="0")) //ho cambiato qui
                  {
                    ui->checkBox_MAP_2->setChecked(true);
                    prova= 5;
                  }
                  else {
                    ui->checkBox_MAP_2->setChecked(false);
                  }


       }
       ui->tabWidget->setCurrentWidget(ui->tab_2);
       ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);
     }


      else if(risposta.clickedButton()==pButtonNo){
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
 // }
}

/**********************       TORNO ALLA HOME E PULISCO TUTTA LA GUI             *********************/
void paginaprincipale::on_pushButton_home_clicked()
{
      ui->tabWidget->setCurrentWidget(ui->tab);
      ui->stackedWidget->setCurrentWidget(ui->page_3);
      ui->checkBox_sinistro->setChecked(false);
      ui->checkBox_destro->setChecked(false);
      ui->checkBox_eeg_2->setChecked(false);
      ui->checkBox_emg_2->setChecked(false);
      ui->checkBox_MAP_2->setChecked(false);
      ui->checkBox_spalla->setChecked(false);
      ui->checkBox_gomito->setChecked(false);
      ui->checkBox_polso->setChecked(false);
      ui->radioButton_pass->setAutoExclusive(false);
      ui->radioButton_pass->setChecked(false);
      ui->radioButton_pass->setAutoExclusive(true);
       ui->radioButton_ag->setAutoExclusive(false);
      ui->radioButton_ag->setChecked(false);
      ui->radioButton_ag->setAutoExclusive(true);
       ui->radioButton_aan->setAutoExclusive(false);
      ui->radioButton_aan->setChecked(false);
      ui->radioButton_aan->setAutoExclusive(true);
       ui->radioButton_chall->setAutoExclusive(false);
      ui->radioButton_chall->setChecked(false);
      ui->radioButton_chall->setAutoExclusive(true);
       ui->radioButton_trigger->setAutoExclusive(false);
      ui->radioButton_trigger->setChecked(false);
      ui->radioButton_trigger->setAutoExclusive(true);
      ui->checkBox_ex1->setChecked(false);
      ui->checkBox_ex2->setChecked(false);
      ui->checkBox_ex3->setChecked(false);
      ui->checkBox_ex4->setChecked(false);
      ui->checkBox_ex5->setChecked(false);
      ui->checkBox_ex6->setChecked(false);
      ui->checkBox_7->setChecked(false);
      ui->comboBox_ex1->setCurrentIndex(0);
      ui->comboBox_ex2->setCurrentIndex(0);
      ui->comboBox_ex3->setCurrentIndex(0);
      ui->comboBox_ex4->setCurrentIndex(0);
      ui->comboBox_ex5->setCurrentIndex(0);
      ui->comboBox_ex6->setCurrentIndex(0);
      ui->comboBox_ex7->setCurrentIndex(0);

      dati::status1 = 14;

      std_msgs::Int8 msg_status;
      msg_status.data = dati::status1;
      ROS_INFO ("%d", msg_status.data);
      status_publisher.publish(msg_status);


}

/**********************       SCORRO IL TUTORIAL DEL MONTAGGIO                       *********************/
void paginaprincipale::on_pushButton_salta_clicked()
{    qDebug() << sel_tut;

     if(curTut<sel_tut.size()) {
       key2 = sel_tut.at(curTut);
       qDebug() << key2;
       if(TutInfoMap.find(key2) != TutInfoMap.end()) {
         TutInfo &one2 = TutInfoMap[key2];
         if(curImg < one2.img.size()){
           ui->label_img_tut -> setPixmap(one2.img.at(curImg));
           ui->label_tut->setText(one2.istr.at(curImg));
           curImg ++;
         }
         if(curImg == one2.img.size()) {
           curImg =0;
           curTut ++;
         }
       }
     }
     else if(curTut== sel_tut.size()) {
       timer_init->start(5000);
       ui->tabWidget_2->setCurrentWidget(ui->tab_init);
       ui->label_img_tut->clear();
       ui->label_tut->setText("");

     }

}

/**********************       SALVO CONFIGURAZIONE ROM                       *********************/
void paginaprincipale::on_pushButton_salvaconf_clicked()
{
    QString FESm1, FESM1, AASm1, AASM1, RIESm1, RIESM1,Gm1, GM1, Pm1,PM1;
    qfloat16 FESm1_f, FESM1_f, AASm1_f, AASM1_f, RIESm1_f, RIESM1_f,Gm1_f, GM1_f, Pm1_f,PM1_f;
    qfloat16 FESm1_def, FESM1_def, AASm1_def, AASM1_def, RIESm1_def, RIESM1_def,Gm1_def, GM1_def, Pm1_def,PM1_def;
    FESm1_def = -80;
    FESM1_def = 45;
    AASm1_def = -75;
    AASM1_def = 35;
    RIESm1_def = -20;
    RIESM1_def = 90;
    Gm1_def = 0;
    GM1_def = 135;
    Pm1_def = -20;
    PM1_def = 180;
    FESm1= ui->lineEdit_flessospallamin->text();
    FESm1_f = FESm1.toFloat();
    FESM1 = ui->lineEdit_flessospallamax->text();
    FESM1_f = FESM1.toFloat();
    AASm1= ui->lineEdit_adduzionespallamin->text();
    AASm1_f = AASm1.toFloat();
    AASM1 = ui->lineEdit_adduzionespallamax->text();
    AASM1_f = AASM1.toFloat();
    RIESm1= ui->lineEdit_rotazionespallamin->text();
    RIESm1_f = RIESm1.toFloat();
    RIESM1 = ui->lineEdit_rotazionespallamax->text();
    RIESM1_f = RIESM1.toFloat();
    Gm1= ui->lineEdit_gomitomin->text();
    Gm1_f =Gm1.toFloat();
    GM1 = ui->lineEdit_gomitomax->text();
    GM1_f = GM1.toFloat();
    Pm1 = ui ->lineEdit_polomin->text();
    Pm1_f = Pm1.toFloat();
    PM1= ui->lineEdit_polsomax->text();
    PM1_f = PM1.toFloat();
    if(FESm1_f<FESm1_def) {
      QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della flesso estensione minima della spalla è fuori dal valore minimo consentito"));

    }
    else if (FESM1_f > FESM1_def) {
      QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della flesso estensione massima della spalla è fuori dal valore massimo consentito"));

    }
    else if(AASm1_f < AASm1_def) {
      QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della abdo-adduzione minima della spalla è fuori dal valore minimo consentito"));

    }
    else if (AASM1_f > AASM1_def) {
      QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della abdo-adduzione massima della spalla è fuori dal valore massimo consentito"));

    }
    else if(RIESm1_f < RIESm1_def) {
      QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della rotazione interna/esterna minima della spalla è fuori dal valore minimo consentito"));

    }
    else if (RIESM1_f > RIESM1_def) {
      QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della rotazione interna/esterna massima della spalla è fuori dal valore massimo consentito"));

    }
    else if(Gm1_f < Gm1_def) {
      QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della felsso-estensione minima del gomito è fuori dal valore minimo consentito"));

    }
    else if (GM1_f > GM1_def) {
      QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della flesso-estensione massima del gomito è fuori dal valore massimo consentito"));

    }
    else if(Pm1_f < Pm1_def) {
      QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della prono-supinazione minima del polso è fuori dal valore minimo consentito"));

    }
    else if (PM1_f > PM1_def) {
      QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della prono-supinazione massima del polso è fuori dal valore massimo consentito"));

    }
    else {
    QSqlQuery qry9;
     qry9.prepare("update Parametri_Paziente set ROM1_min = '"+FESm1+"', ROM1_max= '"+FESM1+"', ROM2_min= '"+AASm1+"', ROM2_max= '"+AASM1+"', ROM3_min= '"+RIESm1+"', ROM3_max= '"+RIESM1+"', ROM4_min= '"+Gm1+"', ROM4_max= '"+GM1+"', ROM5_min = '"+Pm1+"', ROM5_max= '"+PM1+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    qry9.exec();
    if (qry9.exec())
        {
         QMessageBox ::information(this,tr("Salvato"),tr("Parametri Salvati"));
        // ui->tabWidget_2->setCurrentWidget(ui->tab_controllo);
        // aggiungo questo:

//pubblico che ho salvato i rom su gui/status

       dati::status1 = 4;

       std_msgs::Int8 msg_status;
       msg_status.data = dati::status1;
       ROS_INFO ("%d", msg_status.data);
       status_publisher.publish(msg_status);
       QString l_b, l_a;
       QSqlQuery lunghezza;
       lunghezza.prepare("select LunghezzaBraccio, LunghezzaAvambraccio from Pazienti where Codice_ID = '"+dati::ind+"' ");
       lunghezza.exec();
       while(lunghezza.next()) {
         l_b = lunghezza.value(0).toString();
         l_a = lunghezza.value(1).toString();
       }

       upperarm = l_b.toFloat();
       lowerarm = l_a.toFloat();
              /***************         SETTO ROS PARAMETERS CON I ROM   ******************/
       J_MAX = {FESM1_f, AASM1_f, RIESM1_f, GM1_f, PM1_f};
       J_MIN = {FESm1_f, AASm1_f, RIESm1_f, Gm1_f, Pm1_f};
       ARM_LENGTH = {upperarm, lowerarm};

       ros::NodeHandle n;

       n.setParam("/physiological_param/ROM_Max", J_MAX);
       n.setParam("/physiological_param/ROM_Min", J_MIN);
       n.setParam ("/physiological_param/arm_length", ARM_LENGTH);

         //agree_gui::QNode status << "ho salvato la configurazione dedi rom";
       }
       else {
          QMessageBox ::critical(this,tr("Errore"),tr("bo3"));
        }

}
}

/**********************       CERCO PAZIENTE PER COGNOME                       *********************/
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

/**********************       INABILITO LA SELEZIONE DEGLI OGGETTI INTERATIVI                       *********************/
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

/**********************       CALCOLO TEMPO STIMATO PER LA TERAPIA                       *********************/
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

/**********************       INABILITO COMBO ESERCIZI (PROVVISORIO)                       *********************/
void paginaprincipale::enable_combo_ex() {
  ui->comboBox_ex1->setEnabled(false);
  ui->comboBox_ex2->setEnabled(false);
  ui->comboBox_ex3->setEnabled(false);
  ui->comboBox_ex4->setEnabled(false);
  ui->comboBox_ex5->setEnabled(false);
  ui->comboBox_ex6->setEnabled(false);
  ui->comboBox_ex7->setEnabled(false);

  if(ui->checkBox_ex1->isChecked() ) {
    ui->comboBox_ex1->setEnabled(true);
  }
  if(ui->checkBox_ex2->isChecked() ) {
    ui->comboBox_ex2->setEnabled(true);
  }
  if(ui->checkBox_ex3->isChecked()) {
    ui->comboBox_ex3->setEnabled(true);
  }
  if(ui->checkBox_ex4->isChecked() ) {
    ui->comboBox_ex4->setEnabled(true);
  }
  if(ui->checkBox_ex5->isChecked() ) {
    ui->comboBox_ex5->setEnabled(true);
  }
  if(ui->checkBox_ex6->isChecked()) {
    ui->comboBox_ex6->setEnabled(true);
  }
  if(ui->checkBox_7->isChecked()) {
    ui->comboBox_ex7->setEnabled(true);
  }

}

/**********************       SALVO ESERCIZI                       *********************/
void paginaprincipale::on_pushButton_salvaex_clicked()
{    QString bicchiere, forchetta, libro;
     bicchiere = "Bicchiere";
     forchetta = "Forchetta";
     libro = "Libro";

 if(ui->checkBox_ex1->isChecked())
 {  check_ex1=1;
   dati::ex1 = ui->comboBox_ex1->currentText();

   dati::rip1= ui->lineEdit_ex1->text();
   rep1 = dati::rip1.toInt();
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
     exe1 = dati::num_ex1.toInt();

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
   rep2 = dati::rip2.toInt();
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
     exe2 = dati::num_ex2.toInt();


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
   rep3 = dati::rip3.toInt();
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
     exe3 = dati::num_ex3.toInt();


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
  rep4 = dati::rip4.toInt();
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
    exe4 = dati::num_ex4.toInt();


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
  rep5 = dati::rip5.toInt();
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
    exe5 = dati::num_ex5.toInt();


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
  rep6 = dati::rip6.toInt();
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
    exe6 = dati::num_ex6.toInt();


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
  rep7 = dati::rip7.toInt();
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
    exe7 = dati::num_ex7.toInt();


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


 /******************       AGGIORNO TOPIC STATUS : FINISHED EXERCISE SEQUENCE                 ***********************/
//std_msgs::Int8 msg_status;
  dati::status1 = 5;
msg_status_pp.data = dati::status1;
ROS_INFO ("%d", msg_status_pp.data);
status_publisher.publish(msg_status_pp);

 /******************         AGGIORNO ROS PARAMETERS : EXERCISE SEQUENCE                      ***********************/
ex_seq = {exe1, exe2, exe3, exe4, exe5, exe6, exe7};
ex_rep = {rep1, rep2, rep3, rep4, rep5, rep6, rep7};
ex_obj = {ros_ogg1, ros_ogg2, ros_ogg3, ros_ogg4, ros_ogg5, ros_ogg6, ros_ogg7};
ros::NodeHandle n;
n.setParam("/exercise/sequence", ex_seq);
n.setParam("/exercise/repetition", ex_rep);
n.setParam ("/exercise/objects", ex_obj);

}
else {
  QMessageBox ::critical(this,tr("Errore"),tr("errore"));
  qDebug()<< selezione.lastError();
}

QSqlQuery esercizi;
esercizi.prepare("select ex1,rip1,ex2,rip2,ex3,rip3,ex4,rip4,ex5,rip5,ex6,rip6,ex7,rip7 from Parametri_Paziente where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' order by Data_acquisizione desc limit 1");
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
  // ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);

   }
   //else ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
  }

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
   // ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
    std::cout<< "Key found";


    }
    else {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
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
   // ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
    std::cout<< "Key found";


    }
    else {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
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
    //ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
    std::cout<< "Key found";


    }
    else  {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
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
   // ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
    std::cout<< "Key found";


    }
    else {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
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
    //ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
    std::cout<< "Key found";


    }
    else {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
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
    //ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
    std::cout<< "Key found";


    }
    else {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
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

/**********************       SALVO MODALITÀ DI CONTROLLO                       *********************/
void paginaprincipale::on_pushButton_controllo_clicked()
{

  if(ui->radioButton_trigger->isChecked()) {
    dati::mood = "Trigger";
    QSqlQuery modalita;
    modalita.prepare("update Parametri_Paziente set Modalita_utilizzo = '"+dati::mood+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    modalita.exec();
        if (modalita.exec())
        {
         mode = 2;
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
         mode = 1;
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
         mode = 3;
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
         mode = 4;
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
         mode = 5;
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



         ros::NodeHandle n;
         n.setParam ("/exercise/mode", mode);



                     if (flag==4) {
                        ui->tabWidget_2->setCurrentWidget(ui->tab_ex);

                       qDebug()<< "qui";
                      if(!(dati::lex1==0))
                      {
                        ui->checkBox_ex1->setChecked(true);
                        dati::flag_ex=0;
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
                        dati::flag_ex = 1;
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
                        dati::flag_ex=2;
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
                        dati::flag_ex=3;
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
                        dati::flag_ex=4;
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
                        dati::flag_ex=5;
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
                        dati::flag_ex=6;
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

if (dati::flag_ex ==0 ){
  ui->checkBox_ex1->setChecked(true);
  dati::flag_ex++;
}








}

/**********************       SALVO MODULI MECCANICI ED EXTRA                       *********************/
void paginaprincipale::on_pushButton_salvamoduli_clicked()
{ int8_t check = 0;
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
    active_module_spalla = 1;
    active_module_gomito = 1;
    active_module_RF = 1;
    active_module_MAT = 1;

  }

  if (ui->checkBox_polso->isChecked())
  { dati::modulo_spalla = "1";
    dati::modulo_polso= "1";
    dati::modulo_gomito = "1";
    dati::oi = "1";
    active_module_spalla = 1;
    active_module_gomito = 1;
    active_module_RF = 1;
    active_module_MAT = 1;
    active_module_polso = 1;


  }

  if(ui->checkBox_eeg_2->isChecked())
  {
    dati::modulo_eeg= "1";
    active_module_EEG_EMG=1;


  }
  if(ui->checkBox_emg_2->isChecked())
  {
    dati::modulo_emg= "1";
    active_module_EEG_EMG = 1;

  }
  if(ui->checkBox_MAP_2->isChecked() ||  (prova == 5))
  {

    if(dati::modulo_polso == "1")
    {
    dati::mano = "1";
    active_module_MAP = 1;

    }


    else if (dati::modulo_polso == "0" ) {

      QMessageBox::StandardButton risposta= QMessageBox::question(this,tr("Attenzione"), tr("Il modulo extra: Mano non può essere attivato se la configurazione dei moduli moduli meccanici non comprende anche il Modulo : Polso. Si desidera modificare la configurazione dei Moduli Meccanici? "));
      if (risposta==QMessageBox::Yes)
      {
        //  flag=6;
         // ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);
        ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);
        check = 1;
        qDebug() << "modulo polso stronzissimo";
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
  if(!(check==1)) {
  QSqlQuery moduli;
  moduli.prepare("update Parametri_Paziente set Lato = '"+dati::lato+"', Modulo_Spalla= '"+dati::modulo_spalla+"', Modulo_gomito = '"+dati::modulo_gomito+"', Modulo_polso = '"+dati::modulo_polso+"',EEG='"+dati::modulo_eeg+"', Oggetti_int='"+dati::oi+"', Mano='"+dati::mano+"', EMG='"+dati::modulo_emg+"' where Codice_ID= '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
 moduli.exec();
 if (moduli.exec())
 { QMessageBox ::information(this,tr("Salvato"),tr("Configurazione dei Moduli Meccanici ed Extra salvata"));
   ui->tabWidget_2->setCurrentWidget(ui->tab_tutorial);
   active_modules = {active_module_spalla, active_module_gomito, active_module_polso, active_module_MAT, active_module_RF, active_module_EEG_EMG, active_module_MAP};
 }
 else {
   QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
   qDebug()<< moduli.lastError();
 }
}
  //  if (flag==6)
// {
//     ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);


//  }
//  else {
 //salvo i moduli
//  ss2 << "ho salvato i moduli " ; // al posto di questa devo leggere qnode.variabile da dove l'ho modificata
//  msg.data = ss2.str();
//status_publisher.publish(msg);
//ROS_INFO_STREAM(msg);
//ui->tabWidget_2->setCurrentWidget(ui->tab_tutorial);

//recupero dati salvati
QSqlQuery conf_moduli;
conf_moduli.prepare("select Modulo_Spalla, Modulo_gomito, Modulo_polso, EEG, EMG, Mano from Parametri_Paziente where  Codice_ID= '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' order by Data_acquisizione desc limit 1");
if(conf_moduli.exec()){
  qDebug()<< "ho eseguito la query";

while(conf_moduli.next()) {
  TutInfo curr;
  VestInfo curr1;
  QString spalla, gomito, polso, EEG, EMG, Mano;

  spalla = conf_moduli.value(0).toString();
  gomito = conf_moduli.value(1).toString();
  polso = conf_moduli.value(2).toString();
  EEG = conf_moduli.value(3).toString();
  EMG = conf_moduli.value(4).toString();
  Mano = conf_moduli.value(5).toString();
//QString string1 = "Impostare la lunghezza del braccio del paziente regolando la distanza tra asse 1 e asse 4. ";
//QString string2 = "Svitare le viti cherchiate in figura, bloccando la testa della vite e svitando il bullone.Successivamente posizionare il giunto 4 (in corrispondenza dell'asse 4) sfilando o infilando la barra di collegamento all'interno della morsa. Ruotare la morsa attorno all'asse della vite soltanto se necessario.";
//QString string3 = ""
QStringList istr1 = {"Impostare la lunghezza del braccio del paziente regolando la distanza tra asse 1 e asse 4. ", "Svitare le viti cherchiate in figura, bloccando la testa della vite e svitando il bullone.\nSuccessivamente posizionare il giunto 4 (in corrispondenza dell'asse 4) sfilando o infilando la barra di collegamento all'interno della morsa.\nRuotare la morsa attorno all'asse della vite soltanto se necessario.", "Impostare la lunghezza dell'avambraccio del paziente regolando la distanza tra l'asse 4 e l'attacco del giunto 5. ","Per farlo, svitare le 4 viti ad incasso esagonale mostrate in figura,\nquindi far slittare la barra di aggancio al giunto 5, fino a raggiungere la posizione desiderata.\nIn fine avvitare le 4 viti. "};
QStringList istr2 = {"Posizionare gli elettrodi sul Deltoide posteriore", "Posizionare gli elettrodi sul deltoide anteriore", "Posizionare gli elettrodi sul deltoide mediale", "Posizionare gli elettrodi sul bicipite", "Accendere il dispositivo utilizzando il tasto on/off.\nPosizionarlo nell'apposito alloggiamento in dotazione in corrispondenza della spalla dell'utente"};
QStringList istr3 = {"Agganciare il Modulo di Assistenza alla Presa al giunto 5 (Polso) dell'esoscheletro"};
QStringList istr_vest1 = {"Individuare e definire una posizione confortevole ddel paziente in modo tale che la shiena sia appoggiata allo schienale.", "il giunto 1 (spalla) deve essere almeno allo stesso livello della spalla nel piano orizzontale lungo x, come mostrato in figura.\nVerificare inoltre che l'altezza del giunto 1(spalla) sia tale da evitare il contatto tra la spalla del paziente e il giunto stesso, sia in stasi che in movimento.\nVerificare infine che il sistema di aggancio del polso all'esoscheletro non sia in alcun modo d'ostacolo al movimento di presa della mano,\ne che non provochi sensazione di trazione nella mano del paziente."};
 if (spalla =="1" && gomito == "1" && polso == "1") {
   QString tut1 = "mecc1";
   curr.tut = tut1;
   curr.img = GetImages2(tut1);
   curr.istr = istr1;
   TutInfoMap[tut1] = curr;
   qDebug()<<curr.img.size();
   sel_tut.append(tut1);

   QString vest1 = "vest";
   curr1.vest = vest1;
   curr1.img_v = GetImages3(vest1);
   curr1.istr_vest = istr_vest1;
   VestInfoMap[vest1] = curr1;
   sel_vest.append(vest1);
   qDebug()<<"sel : " <<sel_vest;
   qDebug()<<"size:" << sel_vest.size();


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
    curr.istr = istr2;
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
    curr.istr = istr3;
    TutInfoMap[tut5] = curr;
    qDebug()<<curr.img.size();
    sel_tut.append(tut5);
    qDebug()<<"sel : " <<sel_tut;
    qDebug()<<"size:" << sel_tut.size();
  }


}
}
/***************         SETTO ROS PARAMETERS CON I MODULI   ******************/
ros::NodeHandle n;
n.setParam("/active_modules", active_modules );



}

/**********************       SALVO IN UNA LISTA IMMAGINI PER ESERCIZI                       *********************/
//SALVO TUTTE LE IMMAGINI DEGLI ESERCIZI IN UNA LISTA
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

/**********************       SALVO IN UNA LISTA IMMAGINI PER TUTORIAL MONTAGGIO                       *********************/
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

/**********************       SALVO IN UNA LISTA IMMAGINI PER TUTORIAL VESTIZIONE                      *********************/
QList<QPixmap>GetImages3(QString vestID) {
  QList<QPixmap> mylist3;
  auto folder3 ("/home/alice/Desktop/vestizione/" +vestID);
  QDir directory3(folder3);
  QStringList img_v = directory3.entryList(QStringList() <<"*.jpg" << "*.JPG" <<"*.png" << "*.PNG", QDir::Files );
  qDebug() <<directory3;
  qDebug() << "i found" << img_v.size();
  foreach(QString filename, img_v) {
    QPixmap pix3(folder3 + QString("/") + filename);
    mylist3.append(pix3);
    qDebug()<< mylist3;
  }
  return mylist3;
}

/**********************       SALVO I 3 PUNTI DEL PAD                       *********************/
void paginaprincipale::on_pushButton_salvatapp_clicked()
{

QVector<QPoint> mylocalList =matrix->getPosition();

// mando il massaggio che ho salvato i punti sul tappetino
//ss4 << "ho salvato i punti sul tappetino" ; // al posto di questa devo leggere qnode.variabile da dove l'ho modificata
//msg.data = ss4.str();
//status_publisher.publish(msg);
//ROS_INFO_STREAM(msg);
//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
dati::status1 = 10;

std_msgs::Int8 msg;
msg.data = dati::status1;
ROS_INFO ("%d", msg.data);
status_publisher.publish(msg);


}

/**********************       INIZIO TERAPIA                       *********************/
void paginaprincipale::on_pushButton_next_clicked()
{ //qDebug()<<sel_ex;
timer_rehab->start(20);
dati::status1 = 11;

std_msgs::Int8 msg;
msg.data = dati::status1;
ROS_INFO ("%d", msg.data);
status_publisher.publish(msg);

 //  next_img();
 // timer->start(1000);
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

/**********************          SCORRO LE IMMAGINI DEGLI ESERCIZI                    *********************/
void paginaprincipale::next_img() {
  qDebug()<< dati::command_exercise_pp;
QString istr99, istr_def, istr1_1, istr3_1, istr5_1, istr1_3, istr2_3, istr3_3, istr4_3, istr5_3, istr6_3, istr7_3, istr8_3, istr9_3, istr_def6, istr2_6, istr_def7, istr2_7, istr_terap, istr0_3;
  istr99 = "Resta in Attesa di una nuova istruzione";
  istr_def = "Posizione di Riposo";
 // istr_def6 = "Posizione di Riposo";
//  istr_def7 = "Posizione di Riposo";

  //ISTRUZIONI ESERCIZIO 1
  istr1_1 = "Porta il braccio sul punto Rosso";
  istr3_1 = "Porta il braccio sul punto Rosso";
  istr5_1 = "Porta il braccio sul punto Rosso";

  //ISTRUZIONI ESERCIZIO 3
//  istr0_3 = "Attendi che la mano sia posizionata in posizione di riposo";
//  istr1_3 = "Prendi l'oggetto dalla posizione centrale";
//  istr2_3 = "Porta l'oggetto a sinistra";
//  istr3_3 = "Lascia l'oggetto, quindi ritorna in posizione di riposo";
//  istr4_3 = "Prendi l'oggetto";
//  istr5_3= "Porta l'oggetto a destra";

//  istr6_3 = "Lascia l'oggetto e ritorna in posizione di riposo";
//  istr7_3 = "Prendi l'oggetto";
//  istr8_3="Porta l'oggetto in posizione centrale";
//  istr9_3 = "Torna in posizione di Rest";

  //ISTRUZIONI ESERCIZIO 6
  istr_terap = "Terapista, posiziona l'oggetto in posizione di riposo ";
  istr2_6 = "porta l'oggetto alla bocca";



  //ISTRUZIONI ESERCIZIO 7

  istr2_7= "Eleva il braccio lateralmente";


  QPixmap case99("/home/alice/Desktop/wait.jpg"); // ATTESA
  //QPixmap case99("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/wait.jpg"); // ATTESA
  QPixmap case1_1("/home/alice/Desktop/es1_new/es1_2.png");
  //QPixmap case1_1("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/es1_new/es1_2.png");
  QPixmap case3_1("/home/alice/Desktop/es1_new/es1_3.png");
  //QPixmap case3_1("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/es1_new/es1_3.png");
  QPixmap case5_1("/home/alice/Desktop/es1_new/es1_6.png");
  //QPixmap case5_1("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/es1_new/es1_6.png");
  QPixmap def("/home/alice/Desktop/es1_new/es1_rest.png"); //POSIZIONE DI REST
  //QPixmap def("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/es1_new/es1_rest.png");
   QPixmap def1("/home/alice/Desktop/ex_img1/01/es1_1.JPG"); //POSIZIONE DI REST
   //QPixmap def1("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ex_img1/01/es1_1.JPG");


  QPixmap case1_3("/home/alice/Desktop/new/es3_1.jpg"); //vai in centro prendi oggetto
  //QPixmap case1_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/new/es3_1.jpg");


  QPixmap case2_3("/home/alice/Desktop/new/es3_2.jpg"); // sx
  //QPixmap case2_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/new/es3_2.jpg");

  QPixmap case3_3("/home/alice/Desktop/new/es3_3.jpg"); // rest
  //QPixmap case3_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/new/es3_3.jpg");

  QPixmap case4_3("/home/alice/Desktop/new/es3_4.jpg"); // sx
  //QPixmap case4_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/new/es3_4.jpg");
  QPixmap case5_3("/home/alice/Desktop/new/es3_5.jpg"); // dx
  //QPixmap case5_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/new/es3_5.jpg");
  QPixmap case6_3("/home/alice/Desktop/new/es3_6.jpg"); // rest
  //QPixmap case6_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/new/es3_6.jpg");
  QPixmap case7_3("/home/alice/Desktop/new/es3_7.jpg"); // dx
  //QPixmap case7_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/new/es3_7.jpg");
  QPixmap case8_3("/home/alice/Desktop/new/es3_8.jpg"); // centro
  //QPixmap case8_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/new/es3_8.jpg");
  QPixmap case9_3("/home/alice/Desktop/new/es3_9.jpg"); // rest
  //QPixmap case9_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/new/es3_9.jpg");

  QPixmap def_6("/home/alice/Desktop/es6/es6_1.jpeg");
  //QPixmap def_6("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/es6/es6_1.jpeg");
  QPixmap case2_6("/home/alice/Desktop/es6/es6_2.jpeg");
  //QPixmap case2_6("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/es6/es6_2.jpeg");

  QPixmap def_7("/home/alice/Desktop/ex_img1/07/es7_1.JPG");
  //QPixmap def_7("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ex_img1/07/es7_1.JPG");
  QPixmap case2_7("/home/alice/Desktop/ex_img1/07/es7_2.JPG");
  //QPixmap case2_7("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ex_img1/07/es7_2.JPG");


  QPixmap feedback_happy("/home/alice/Desktop/smile.jpeg");
  //QPixmap feedback_happy("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/smile.jpeg");



  /**********************          SCORRO LE IMMAGINI DEGLI ESERCIZI FUNZIONE NUOVA             *********************/
  switch (dati::command_exercise_pp) {

//ESERCIZIO REACHING NEL PIANO SENZA OGGETTI

  case 1 :
    qDebug()<< dati::command_task_pp;
    switch (dati::command_task_pp) {

    case 100: // SCHERMATA ESERCIZIO
      // mostro foto dell'esercizio 1
      ui->label_img-> setText("Iniziamo esercizio di \nraggiungimento dei punti. \nPremere OK per iniziare.");

      break;

    case 99:
      ui->label_img->setPixmap(case99);
      ui->label_istr_ex->setText(istr99);
      qDebug()<< "case99";
      break;
   case 0:
      ui->label_img->setText("Attendi che AGREE\nposizioni la mano in \nposizione di riposo");
      break;
    case 1:
      ui->label_img->setPixmap(case1_1);
      ui->label_istr_ex->setText(istr1_1);
      qDebug()<< "case1";
      break;

    case 3:
      ui->label_img->setPixmap(case3_1);
      ui->label_istr_ex->setText(istr3_1);
      qDebug()<< "case3";
      break;

    case 5:
      ui->label_img->setPixmap(case5_1);
      ui->label_istr_ex->setText(istr5_1);
      qDebug()<< "case5";
      break;

     case 102: //FEEDBACK
      ui->label_img->setPixmap(feedback_happy);
      ui->label_istr_ex->setText("Congratulazioni! Continua Così!");
      break;

    default:
      ui->label_img->setPixmap(def);
      ui->label_istr_ex->setText(istr_def);
      qDebug()<< "casedef";
      break;



    }   // end switch task
    break; //break exer 1


    // ESERCIZIO REACHING NEL PIANO CON OGGETTI
  case 3:
    qDebug()<< dati::command_task_pp;
    switch(dati::command_task_pp) {

    case 100: // SCHERMATA ESERCIZIO
      // mostro foto dell'esercizio 1
      ui->label_img-> setText("Iniziamo esercizio di \nraggiungimento punti con oggetto. \nPremere OK per iniziare.");
       ui->pushButton_ok->setEnabled(false);
      break;

    case 0:
       ui->label_img->setText("Attendi che AGREE\nposizioni la mano in Rest");
        ui->pushButton_ok->setEnabled(true);
       break;

    case 101: // POSIZIONAMENTO OGGETTO
      ui->label_img->setText("Terapista, posiziona l'oggetto \nsul punto del pad illuminato. \nQuindi premi OK");
       ui->pushButton_ok->setEnabled(false);
      break;
    case 99:
      ui->label_img->setPixmap(case99);
      ui->label_istr_ex->setText(istr99);
       ui->pushButton_ok->setEnabled(true);
      qDebug()<< "case99";
      break;



    case 1:
      ui->label_img->setPixmap(case1_3);
       ui->pushButton_ok->setEnabled(true);
     // ui->label_istr_ex->setText(istr1_3);
      qDebug()<< "case1_3";
      break;


    case 2:
      ui->label_img->setPixmap(case2_3);
       ui->pushButton_ok->setEnabled(true);
     // ui->label_istr_ex->setText(istr2_3);
      qDebug()<< "case2_3";
      break;


    case 3 :
      ui->label_img->setPixmap(case3_3);
       ui->pushButton_ok->setEnabled(true);
     // ui->label_istr_ex->setText(istr3_3);
          break;

    case 4:
      ui->label_img->setPixmap(case4_3);
       ui->pushButton_ok->setEnabled(true);
      //ui->label_istr_ex->setText(istr4_3);
      qDebug()<< "case4_3";
      break;

    case 5:
      ui->label_img->setPixmap(case5_3);
       ui->pushButton_ok->setEnabled(true);
      //ui->label_istr_ex->setText(istr5_3);
      qDebug()<< "case5_3";
      break;

    case 6:
      ui->label_img->setPixmap(case6_3);
       ui->pushButton_ok->setEnabled(true);
      //ui->label_istr_ex->setText(istr6_3);
      qDebug()<< "case6_3";
      break;

    case 7:
      ui->label_img->setPixmap(case7_3);
       ui->pushButton_ok->setEnabled(true);
      //ui->label_istr_ex->setText(istr7_3);
      qDebug()<< "case8_3";
      break;

    case 8:
      ui->label_img->setPixmap(case8_3);
       ui->pushButton_ok->setEnabled(true);
      //ui->label_istr_ex->setText(istr8_3);
      qDebug()<< "case9_3";
      break;

    case 9:
      ui->label_img->setPixmap(case9_3);
       ui->pushButton_ok->setEnabled(true);
      //ui->label_istr_ex->setText(istr9_3);
      qDebug()<< "case9_3";
      break;

    case 102: // FEEDBACK
     ui->label_img->setPixmap(feedback_happy);
     ui->label_istr_ex->setText("Congratulazioni! Continua Così!");
      ui->pushButton_ok->setEnabled(true);
     break;

    default:
      ui->label_img->setPixmap(case1_3);
       ui->pushButton_ok->setEnabled(true);
    //  ui->label_istr_ex->setText(istr_def);
      qDebug()<< "casedef";
      break;
    }
    break;

    // ESERICZIO MANO ALLA BOCCA CON OGGETTO
  case 6:
    qDebug()<< dati::command_task_pp;
    switch(dati::command_task_pp) {

    case 100: // SCHERMATA ESERCIZIO
      // mostro foto dell'esercizio 1
      ui->label_img-> setText("Iniziamo esercizio \nMano alla bocca con oggetto. \nPremere OK per iniziare.");
 ui->pushButton_ok->setEnabled(false);
      break;
   case 101: //POSIZIONAMENO OGGETTO
   ui->label_img-> setText("Terapista aggancia l'oggetto \n alla mano del paziente.\nQuindi premi OK");
    ui->pushButton_ok->setEnabled(false);

      break;
    case 99:
      ui->label_img->setPixmap(case99);
      ui->label_istr_ex->setText(istr99);
      qDebug()<< "case99";
      break;

    case 0:
       ui->label_img->setText("Attendi che AGREE\nposizioni la mano in Rest");
        ui->pushButton_ok->setEnabled(true);
       break;




    case 1:
      ui->label_img->setPixmap(case2_6);
      ui->label_istr_ex->setText(istr2_6);
      qDebug()<< "case2_6";
       ui->pushButton_ok->setEnabled(true);
      break;

    case 2:
      ui->label_img->setPixmap(def_6);
      ui->label_istr_ex->setText(istr_def6);
      qDebug()<< "case2_6";
       ui->pushButton_ok->setEnabled(true);
      break;

    case 102: //FEEDBACK
     ui->label_img->setPixmap(feedback_happy);
     ui->label_istr_ex->setText("Congratulazioni! Continua Così!");
      ui->pushButton_ok->setEnabled(true);
     break;

    default:
      ui->label_img->setPixmap(def_6);
      ui->label_istr_ex->setText(istr_def6);
      qDebug()<< "casedef";
       ui->pushButton_ok->setEnabled(true);
      break;




    }
    break;

    // ELEVAZIONE LATERALE CON OGGETTO
  case 7 :
    qDebug()<< dati::command_task_pp;
    switch(dati::command_task_pp) {
    case 99:
      ui->label_img->setPixmap(case99);
      ui->label_istr_ex->setText(istr99);
      qDebug()<< "case99";
       ui->pushButton_ok->setEnabled(true);
      break;

    case 1:
      ui->label_img->setPixmap(case2_7);
      ui->label_istr_ex->setText(istr2_7);
      ui->pushButton_ok->setEnabled(true);
      qDebug()<< "case2_7";
      break;

    case 102: //FEEDBACK PAZIENTE
     ui->label_img->setPixmap(feedback_happy);
     ui->label_istr_ex->setText("Congratulazioni! Continua Così!");
      ui->pushButton_ok->setEnabled(true);
     break;

    default:
      ui->label_img->setPixmap(def_7);
      ui->label_istr_ex->setText(istr_def7);
       ui->pushButton_ok->setEnabled(true);
      qDebug()<< "casedef";
      break;

    }
    break;

  } // end switch exer

  /**********************          SCORRO LE IMMAGINI DEGLI ESERCIZI FUNZIONE VECCHIA          *********************/
  qDebug()<< "sono nella funzione next_img";
// // if(dati::next_img=="a"){
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
//              dati::status1 = 12;

//                  std_msgs::Int8 msg;
//                  msg.data = dati::status1;
//                  ROS_INFO ("%d", msg.data);
//                  status_publisher.publish(msg);
//          }

//          if ( curImage == one.images.size() ) { // -1 we start in zero
//              curImage = 0;
//              rep++;
//              ui->label_fine_ex->setText("");
//          }
//  }
//          if ( rep == one.REP ) {
//              rep=0;
//              timer_feedback->start(2500);
////              ui->label_fine_ex->setText("Congratulazioni hai completato correttamente l'esercizio, continua cosi!");
////              QPixmap smile("/home/alice/Desktop/smile.jpeg");
////              ui->label_img->setPixmap(smile);
//               curEx++;
//              // now take next EX
//          }
//      }


////      if(curEx==sel_ex.size())
////      {
////        curEx=0;
////        return;
////      }
//  }
//  else if (curEx==sel_ex.size()) {

//   //ui->tabWidget_2->setCurrentWidget(ui->tab_valutazione);
//qDebug()<< "in ==";
//    timer_val->start(2500);
//    //carico la tabella dei parametri cinematici  dei pazienti
//        QSqlQueryModel *model1 = new QSqlQueryModel();
//        QSqlQuery * qry_val = new QSqlQuery(mydb2);
//        qry_val -> prepare("select Intrajoint_coordination, Normalized_jerk, Movement_arrest_period_ratio, Peak_speed_ratio, Acceleration_metric from Valutazioni  where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' order by Data_acquisizione desc limit 1 ");
//        qry_val -> exec();
//        if(qry_val->exec()) {
//        model1 -> setQuery(*qry_val);
//        ui->tableView_valutazioni->setModel(model1);
//        ui->tableView_valutazioni->resizeColumnsToContents(); }
//        else qDebug()<<qry_val->lastError();
//      //  qDebug() << (model->rowCount());
//    // carico la tabella dei parametri EMG dei pazienti
//        QSqlQueryModel *model2 = new QSqlQueryModel();
//        QSqlQuery * qry_val_emg = new QSqlQuery(mydb2);
//        qry_val_emg -> prepare ("select Per_corretta_attivazione_muscolare, Normalized_EMG_action_level, Indice_co_contrazione, Sinergie_muscolari, Active_movement_Idex from Valutazioni where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' order by Data_acquisizione desc limit 1 ");
//        qry_val_emg-> exec();
//        if(qry_val_emg-> exec()) {
//        model2 -> setQuery(*qry_val_emg);
//        ui->tableView_parametriEMG-> setModel(model2);
//        ui->tableView_parametriEMG-> resizeColumnsToContents();
//        dati::status1 = 13;

//            std_msgs::Int8 msg;
//            msg.data = dati::status1;
//            ROS_INFO ("%d", msg.data);
//            status_publisher.publish(msg);
//        }


//        else  qDebug()<< qry_val_emg ->lastError();
//        timer_rehab->stop();
//  }
//dati::next_img = "b";

//  }
}

/**********************       MOSTRO FEEDBACK DURANTE LA TERAPIA                       *********************/
void paginaprincipale::show_feed() {
  ui->label_fine_ex->setText("Congratulazioni hai completato correttamente l'esercizio, continua cosi!");
  QPixmap smile("/home/alice/Desktop/smile.jpeg");
  ui->label_img->setPixmap(smile);
 timer_feedback->stop();
}

/**********************       MOSTRO I RISULTATI DELLA SESSIONE                       *********************/
void paginaprincipale::show_val() {
  qDebug() << "sono in show val";
   ui->tabWidget_2->setCurrentWidget(ui->tab_valutazione);
   timer_val->stop();
  // timer->stop();

   ui->label_img->clear();
   ui->label_fine_ex->clear();
}

/**********************       SCORRO INDIETRO LE IMMAGINI DEL TUTORIAL DI MONTAGGIO (DA SISTEMARE)  *********************/
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

/**********************       SALTO TUTORIAL MONTAGGIO  *********************/
void paginaprincipale::on_pushButton_prosegui_clicked()
{
    ui->tabWidget_2->setCurrentWidget(ui->tab_init);
    timer_init->start(5000);
}

/**********************       SALTO TUTORIAL VESTIZIONE  *********************/
void paginaprincipale::on_pushButton_go_clicked()
{  dati::status1 = 3;

   std_msgs::Int8 msg;
   msg.data = dati::status1;
   ROS_INFO ("%d", msg.data);
   status_publisher.publish(msg);
//  if(dati::command == 4)
//    ui->tabWidget_2->setCurrentWidget(ui->tab_parametri);
}

/**********************       INTERROMPO TERAPIA  *********************/
void paginaprincipale::on_pushButton_clicked()
{   //timer->stop();
    timer_rehab->stop();
    ui->tabWidget->setCurrentWidget(ui->tab);
    ui->stackedWidget->setCurrentWidget(ui->page_3);

}

/**********************       SCORRO AVANTI IMMAGINI TUTORIAL VESTIZIONE  *********************/
void paginaprincipale::on_pushButton_avanti_v_clicked()
{
  qDebug() << sel_vest;

      if(curVest<sel_vest.size()) {
        key3 = sel_vest.at(curVest);
        qDebug() << key2;
        if(VestInfoMap.find(key3) != VestInfoMap.end()) {
          VestInfo &one3 = VestInfoMap[key3];
          if(curimgs < one3.img_v.size()){
            ui->label_img_vest -> setPixmap(one3.img_v.at(curimgs));
            ui->label_istr_vest->setText(one3.istr_vest.at(curimgs));
            curimgs ++;
          }
          if(curimgs == one3.img_v.size()) {
            curimgs =0;
            curVest++;
          }
        }
      }
      else if(curTut== sel_tut.size()) {
       // timer_init->start(5000);
        if(dati::command_pp == 4) {
        ui->tabWidget_2->setCurrentWidget(ui->tab_parametri);
        }
        ui->label_img_vest->clear();
        ui->label_istr_vest->setText("");

      }
}

/**********************       EFFETTUO LOG OUT  *********************/
void paginaprincipale::on_pushButton_logout_clicked()
{


  QMessageBox logout;
  logout.setText(tr("Si è scelto di effetturare il Log out?"));
  QAbstractButton* pButtonYes = logout.addButton(tr("Conferma"), QMessageBox::YesRole);
  QAbstractButton* pButtonNo =  logout.addButton(tr("No"), QMessageBox::NoRole);
  logout.exec();
  if(logout.clickedButton()==pButtonYes) {

    emit ShowMain();
    accept();





  }
  else if (logout.clickedButton()==pButtonNo) {

  }
}

void paginaprincipale::skip_init(){
  timer_init->stop();
  //ui->tabWidget_2->setCurrentWidget(ui->tab_vestizione);
  dati::status1 =2;
  msg_status_pp.data = dati::status1;
  ROS_INFO ("%d", msg_status_pp.data);
  status_publisher.publish(msg_status_pp);

if (flag == 4) {
  if (dati::mood_prec == "Mobilizzazione Passiva"){
    ui->radioButton_pass->setChecked(true);
  }
  else if (dati::mood_prec == "Trigger") {
    ui->radioButton_trigger->setChecked(true);
  }
  else if(dati::mood_prec == "Assisted as needed") {
    ui->radioButton_aan->setChecked(true);

  }
  else if(dati::mood_prec == "Anti-g") {
    ui->radioButton_ag->setChecked(true);

  }
  else if(dati::mood_prec == "Challenging") {
    ui->radioButton_chall->setChecked(true);
  }
}
//ui->stackedWidget->setCurrentWidget(ui->page_3);
}

void paginaprincipale::on_pushButton_2_clicked()
{
  dati::status1 = 6;

     std_msgs::Int8 msg;
     msg.data = dati::status1;
     ROS_INFO ("%d", msg.data);
     status_publisher.publish(msg);
}

void paginaprincipale::on_pushButton_add_clicked()

{ if(dati::flag_ex == 0) {
  dati::flag_ex++;}
  if(dati::flag_ex == 1) {
    ui->checkBox_ex2->setChecked(true);

    dati::flag_ex++;
     qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex==2) {
    ui->checkBox_ex3->setChecked(true);
    dati::flag_ex++;
     qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex==3) {
    ui->checkBox_ex4->setChecked(true);
    dati::flag_ex++;
     qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex==4) {
    ui->checkBox_ex5->setChecked(true);
    dati::flag_ex++;
     qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex==5) {
    ui->checkBox_ex6->setChecked(true);
    dati::flag_ex++;
     qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex==6) {
    ui->checkBox_7->setChecked(true);
   // dati::flag_ex++;
     qDebug()<<dati::flag_ex;
  }

}

void paginaprincipale::on_pushButton_remove_clicked()
{ if(dati::flag_ex == 6){
    ui->checkBox_7->setChecked(false);
    dati::flag_ex--;
    qDebug()<<dati::flag_ex;

  }
  else if (dati::flag_ex ==5) {
    ui->checkBox_ex6->setChecked(false);
    dati::flag_ex--;
     qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex ==4) {
    ui->checkBox_ex5->setChecked(false);
    dati::flag_ex--;
     qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex ==3) {
    ui->checkBox_ex4->setChecked(false);
    dati::flag_ex--;
     qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex ==2) {
    ui->checkBox_ex3->setChecked(false);
    dati::flag_ex--;
     qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex ==1) {
    ui->checkBox_ex2->setChecked(false);
    dati::flag_ex--;
     qDebug()<<dati::flag_ex;
  }

}

void paginaprincipale::on_pushButton_ok_clicked()
{
  if(dati::command_old_pp == 12) {
    dati::status1=12;
  msg_status_pp.data = dati::status1;
  status_publisher.publish(msg_status_pp);
  }
  if(dati::command_old_pp ==13) {
    dati::status1=13;
  msg_status_pp.data = dati::status1;
  status_publisher.publish(msg_status_pp);
  }

}
