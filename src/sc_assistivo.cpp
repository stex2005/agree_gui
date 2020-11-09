#include "../include/agree_gui/sc_assistivo.h"
#include "ui_sc_assistivo.h"
#include "../include/agree_gui/login.h"
#include "../include/agree_gui/main_window.hpp"
#include "../include/agree_gui/paginaprincipale.h"
#include "../include/agree_gui/qnode.hpp"
#include <QMessageBox>
#include <QFloat16>
QString dati::patologia;
int joy;
int contatore= 0;
int rett=0;


int dati::controllo_voc, dati::controllo_joy, dati::controllo_gomito;
int16_t dati::command_old_sc3=1, dati::command_sc3=0, dati::command_istr_sc3, dati::command_sec_sc3, dati::command_istr_sc3_old, dati::command_sec_sc3_old ;


//CALLBACK



sc_assistivo::sc_assistivo(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::sc_assistivo)
{
  ui->setupUi(this);
  ros::NodeHandle n;
  status_publisher = n.advertise<std_msgs::Int16>("/gui/status", 1000);
  command_subscriber = n.subscribe("/gui/command", 1000, &sc_assistivo::callback3, this);

  //creo il timer per cambiare il colore dei rettangoli del joystick

  timer_joy = new QTimer (this);

  // IMMAGINI LABEL
  QPixmap pic1_sc3("/home/alice/catkin_ws/src/agree_gui/resources/images/init.png");
  ui->label_init_sc3->setPixmap(pic1_sc3);

  //ICONE TASTI
  ui->pushButton_spegni->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Turn off"));
  ui->pushButton_skip_sc3->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Fast-forward"));

  ui->pushButton_allarme_sc3->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Stop sign"));

  //DATA
  QDate data_sc3;
  data_sc3= QDate::currentDate();
  dati::data1= data_sc3.toString(Qt::ISODate);
  ui->label_data_sc3->setText(data_sc3.toString());

  QSqlDatabase mydb3 = QSqlDatabase::database();
  if (!mydb3.open())
    ui->label_utente-> setText("Database non connesso");

  else

    ui->label_utente ->setText("Database connesso...");

  connect(timer_joy, SIGNAL(timeout()), this, SLOT(cal_joy()));

  // timer->start(5000);
  //QSqlDatabase::database();


  qDebug() << dati::nuovo_utente;



}


sc_assistivo::~sc_assistivo()
{
  delete ui;
}

void sc_assistivo::callback3(const agree_gui::agree_gui_command msg_command_sc3) {
  ros::NodeHandle n;
  dati::command_sc3 = msg_command_sc3.mode;
  qDebug()<< "SONO NELLA CALLBACK SC3";
  dati::command_istr_sc3 = msg_command_sc3.exercise;
  dati::command_sec_sc3 = msg_command_sc3.task;
  QFont font1, font2;
  font1.setPointSize(19);
  font2.setPointSize(16);
  if((dati::command_old_sc3) != (dati::command_sc3) || (dati::command_istr_sc3_old)!= (dati::command_istr_sc3) || (dati::command_sec_sc3_old)!= (dati::command_sec_sc3)) {
    qDebug()<< dati::command_old_sc3;
    qDebug()<< dati::command_sc3;
    dati::command_old_sc3=dati::command_sc3;
    dati::command_istr_sc3_old = dati::command_istr_sc3;
    dati::command_sec_sc3_old = dati::command_sec_sc3;
    ROS_INFO("I heard: %d SCENARIO 3", dati::command_sc3);

    if(dati::command_old_sc3 ==3002) {
      qDebug() << "sono nel ciclo ma non faccio un cazzooo";
      ui->stackedWidget->setCurrentWidget(ui->page_config);
      ui->pushButton_allarme_sc3->setVisible(false);
      // this->showMaximized();
      QSqlQuery prova_sc3;
      prova_sc3.prepare("select Nome, Cognome from Users where Username = '"+dati::username+"' and Password = '"+dati::password+"'");
      prova_sc3.exec();
      if (prova_sc3.exec()) {
        qDebug()<< "sono nella query prova";
        while(prova_sc3.next()) {
          qDebug()<<dati::username;
          ui->label_utente->setText("Utente: " + prova_sc3.value(0).toString() + " " +  prova_sc3.value(1).toString());
        } }
      else qDebug()<< prova_sc3.lastError();
      this->show();
    }
    // INIZIALIZZAZIONE
    if (dati::command_old_sc3 == 3003) {
      ui->stackedWidget->setCurrentWidget(ui->page_init_sc3);
    }
    // VESTIZIONE
    if (dati::command_old_sc3 == 3004) {
      ui->stackedWidget->setCurrentWidget(ui->page_vest_sc3);
    }
    // ROM
    if (dati::command_old_sc3 == 3005) {
      ui->stackedWidget->setCurrentWidget(ui->page_ROM_sc3);
    }
    // AVVISO CONFIGURAZIONE JOYSTICK
    if (dati::command_old_sc3 == 3006) {
      ui->stackedWidget->setCurrentWidget(ui->page_joystick_conf_confirm);
    }
    // INIZIO CONFIGURAZIONE JOYSTICK
    if (dati::command_old_sc3 == 3007) {

      ui->stackedWidget->setCurrentWidget(ui->page_joy);
      joy=1;
      //      if ((dati::command_istr_sc3_old==0) && (dati::command_sec_sc3_old==0)) {
      //        dati::status1 = 3007;

      //        std_msgs::Int16 msg_status;
      //        msg_status.data = dati::status1;
      //        ROS_INFO ("%d", msg_status.data);
      //        status_publisher.publish(msg_status);
      //        ui->label_istr->setText("Quando sei pronto per iniziare la configurazione spingi il joysick verso l'ALTO.");
      //      }

      //      if(dati::command_istr_sc3_old==1) {
      //        myfunction();
      //        if(dati::command_sec_sc3_old == 0) {
      //          ui->label_istr->setText("Quando sei pronto per iniziare la configurazione spingi il joysick verso l'ALTO.");
      //        }

      //        if(dati::command_sec_sc3_old==5){

      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }
      //        if(dati::command_sec_sc3_old==4){
      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }
      //        if(dati::command_sec_sc3_old==3){
      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }
      //        if(dati::command_sec_sc3_old==2){
      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }
      //        if(dati::command_sec_sc3_old==1){
      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }

      //      }
      //      if(dati::command_istr_sc3_old == 2) {
      //        if(dati::command_sec_sc3_old == 0) {
      //          ui->label_istr->setText("Quando sei pronto per iniziare la configurazione spingi il joysick verso il BASSO.");
      //          ui->label_joy_sec->setText("Configurazione Joystick");

      //        }
      //      }
      //      if(dati::command_istr_sc3_old==3) {
      //        myfunction1();
      //        if(dati::command_sec_sc3_old==5){

      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }
      //        if(dati::command_sec_sc3_old==4){

      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }
      //        if(dati::command_sec_sc3_old==3){

      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }
      //        if(dati::command_sec_sc3_old==2){

      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }
      //        if(dati::command_sec_sc3_old==1){
      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }


      //        if(dati::command_istr_sc3_old == 4) {
      //          if(dati::command_sec_sc3_old == 0) {
      //            ui->label_istr->setText("Quando sei pronto per iniziare la configurazione spingi il joysick verso SINISTRA.");
      //            ui->label_joy_sec->setText("Configurazione Joystick");

      //          }
      //        }
      //      }
      //      if(dati::command_istr_sc3_old==5) {
      //        myfunction3();
      //        if(dati::command_sec_sc3_old==5){
      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }
      //        if(dati::command_sec_sc3_old==4){
      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }
      //        if(dati::command_sec_sc3_old==3){
      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }
      //        if(dati::command_sec_sc3_old==2){
      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }
      //        if(dati::command_sec_sc3_old==1){
      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }

      //      }

      //      if(dati::command_istr_sc3_old == 6) {
      //        if(dati::command_sec_sc3_old == 0) {
      //          ui->label_istr->setText("Quando sei pronto per iniziare la configurazione spingi il joysick verso DESTRA.");
      //          ui->label_joy_sec->setText("Configurazione Joystick");

      //        }
      //      }
      //      if(dati::command_istr_sc3_old==7) {
      //        myfunction2();
      //        if(dati::command_sec_sc3_old==5){
      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }
      //        if(dati::command_sec_sc3_old==4){
      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }
      //        if(dati::command_sec_sc3_old==3){
      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }
      //        if(dati::command_sec_sc3_old==2){
      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }
      //        if(dati::command_sec_sc3_old==1){
      //          ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      //        }
      //      }

      if(dati::command_istr_sc3_old == 9) {

        ui->stackedWidget->setCurrentWidget(ui->page_end_joy);
        joy = 2;

      }
    }
    // SALVATAGGIO POSIZIONE DI REST
    if (dati::command_old_sc3 == 3009) {

      ui->stackedWidget->setCurrentWidget(ui->page_rest_pos_sc3);
    }
    if(dati::command_old_sc3==3010){
      QFont font1, font2;
      font1.setPointSize(19);
      font2.setPointSize(16);
      dati::status1 = 3010;

      std_msgs::Int16 msg_status;
      msg_status.data = dati::status1;
      ROS_INFO ("%d", msg_status.data);
      status_publisher.publish(msg_status);

      ui->stackedWidget->setCurrentWidget(ui->page_main_menu);

      if(dati::command_istr_sc3_old==1 ){

        ui->pushButton_joystick->setFont(font1);
        ui->pushButton_recallPos->setFont(font2);
        ui->pushButton_salvapos->setFont(font2);
        ui->pushButton_vocale->setFont(font2);
        ui->pushButton_singoloj->setFont(font2);
        ui->pushButton_gomito->setFont(font2);
        ui->pushButton_joy->setFont(font2);

        ui->pushButton_joystick->setStyleSheet("background-color : green");
        ui->pushButton_recallPos->setStyleSheet("background-color : white");
        ui->pushButton_salvapos->setStyleSheet("background-color : white");
        ui->pushButton_vocale->setStyleSheet("background-color : white");
        ui->pushButton_singoloj->setStyleSheet("background-color : white");
        ui->pushButton_gomito->setStyleSheet("background-color : white");
        ui->pushButton_joy->setStyleSheet("background-color : white");


      }
      if(dati::command_istr_sc3_old ==2){
        ui->pushButton_joystick->setFont(font2);
        ui->pushButton_recallPos->setFont(font1);
        ui->pushButton_salvapos->setFont(font2);
        ui->pushButton_vocale->setFont(font2);
        ui->pushButton_singoloj->setFont(font2);
        ui->pushButton_gomito->setFont(font2);
        ui->pushButton_joy->setFont(font2);
        ui->pushButton_joystick->setStyleSheet("background-color : white");
        ui->pushButton_recallPos->setStyleSheet("background-color : green");
        ui->pushButton_salvapos->setStyleSheet("background-color : white");
        ui->pushButton_vocale->setStyleSheet("background-color : white");
        ui->pushButton_singoloj->setStyleSheet("background-color : white");
        ui->pushButton_gomito->setStyleSheet("background-color : white");
        ui->pushButton_joy->setStyleSheet("background-color : white");
      }
      if(dati::command_istr_sc3_old ==3){
        ui->pushButton_joystick->setFont(font2);
        ui->pushButton_recallPos->setFont(font2);
        ui->pushButton_salvapos->setFont(font1);
        ui->pushButton_vocale->setFont(font2);
        ui->pushButton_singoloj->setFont(font2);
        ui->pushButton_gomito->setFont(font2);
        ui->pushButton_joy->setFont(font2);
        ui->pushButton_joystick->setStyleSheet("background-color : white");
        ui->pushButton_recallPos->setStyleSheet("background-color : white");
        ui->pushButton_salvapos->setStyleSheet("background-color : green");
        ui->pushButton_vocale->setStyleSheet("background-color : white");
        ui->pushButton_singoloj->setStyleSheet("background-color : white");
        ui->pushButton_gomito->setStyleSheet("background-color : white");
        ui->pushButton_joy->setStyleSheet("background-color : white");
      }
      if(dati::command_istr_sc3_old ==4){
        ui->pushButton_joystick->setFont(font2);
        ui->pushButton_recallPos->setFont(font2);
        ui->pushButton_salvapos->setFont(font2);
        ui->pushButton_vocale->setFont(font1);
        ui->pushButton_singoloj->setFont(font2);
        ui->pushButton_gomito->setFont(font2);
        ui->pushButton_joy->setFont(font2);
        ui->pushButton_joystick->setStyleSheet("background-color : white");
        ui->pushButton_recallPos->setStyleSheet("background-color : white");
        ui->pushButton_salvapos->setStyleSheet("background-color : white");
        ui->pushButton_vocale->setStyleSheet("background-color : green");
        ui->pushButton_singoloj->setStyleSheet("background-color : white");
        ui->pushButton_gomito->setStyleSheet("background-color : white");
        ui->pushButton_joy->setStyleSheet("background-color : white");
      }
      if(dati::command_istr_sc3_old ==5){
        ui->pushButton_joystick->setFont(font2);
        ui->pushButton_recallPos->setFont(font2);
        ui->pushButton_salvapos->setFont(font2);
        ui->pushButton_vocale->setFont(font2);
        ui->pushButton_singoloj->setFont(font1);
        ui->pushButton_gomito->setFont(font2);
        ui->pushButton_joy->setFont(font2);
        ui->pushButton_joystick->setStyleSheet("background-color : white");
        ui->pushButton_recallPos->setStyleSheet("background-color : white");
        ui->pushButton_salvapos->setStyleSheet("background-color : white");
        ui->pushButton_vocale->setStyleSheet("background-color : white");
        ui->pushButton_singoloj->setStyleSheet("background-color : green");
        ui->pushButton_gomito->setStyleSheet("background-color : white");
        ui->pushButton_joy->setStyleSheet("background-color : white");
      }
      if(dati::command_istr_sc3_old ==6){
        ui->pushButton_joystick->setFont(font2);
        ui->pushButton_recallPos->setFont(font2);
        ui->pushButton_salvapos->setFont(font2);
        ui->pushButton_vocale->setFont(font2);
        ui->pushButton_singoloj->setFont(font2);
        ui->pushButton_gomito->setFont(font1);
        ui->pushButton_joy->setFont(font2);
        ui->pushButton_joystick->setStyleSheet("background-color : white");
        ui->pushButton_recallPos->setStyleSheet("background-color : white");
        ui->pushButton_salvapos->setStyleSheet("background-color : white");
        ui->pushButton_vocale->setStyleSheet("background-color : white");
        ui->pushButton_singoloj->setStyleSheet("background-color : white");
        ui->pushButton_gomito->setStyleSheet("background-color : green");
        ui->pushButton_joy->setStyleSheet("background-color : white");
      }
      if(dati::command_istr_sc3_old ==7){
        ui->pushButton_joystick->setFont(font2);
        ui->pushButton_recallPos->setFont(font2);
        ui->pushButton_salvapos->setFont(font2);
        ui->pushButton_vocale->setFont(font2);
        ui->pushButton_singoloj->setFont(font2);
        ui->pushButton_gomito->setFont(font2);
        ui->pushButton_joy->setFont(font1);
        ui->pushButton_joystick->setStyleSheet("background-color : white");
        ui->pushButton_recallPos->setStyleSheet("background-color : white");
        ui->pushButton_salvapos->setStyleSheet("background-color : white");
        ui->pushButton_vocale->setStyleSheet("background-color : white");
        ui->pushButton_singoloj->setStyleSheet("background-color : white");
        ui->pushButton_gomito->setStyleSheet("background-color : white");
        ui->pushButton_joy->setStyleSheet("background-color : green");
      }
    }
    if(dati::command_old_sc3==3011) {
      ui->stackedWidget->setCurrentWidget(ui->page_sessione_sc3);
      if(dati::command_istr_sc3_old==1) {
        ui->pushButton_XY_JOY->setStyleSheet("background-color : green");
        ui->pushButton_z_teta_JOY->setStyleSheet("background-color : white");
        ui->pushButton_XY_JOY->setFont(font1);
        ui->pushButton_z_teta_JOY->setFont(font2);
      }
      if(dati::command_istr_sc3_old==2) {
        ui->pushButton_XY_JOY->setStyleSheet("background-color : white");
        ui->pushButton_z_teta_JOY->setStyleSheet("background-color : green");
        ui->pushButton_XY_JOY->setFont(font2);
        ui->pushButton_z_teta_JOY->setFont(font1);
      }
    }
    if(dati::command_old_sc3==3012) {
      ui->stackedWidget->setCurrentWidget(ui->page_recallpos);
    }
    if(dati::command_old_sc3==3013) {
  //SALVA POSIZIONE
    }
    if(dati::command_old_sc3==3014) {
   //CONTROLLO VOCALE
    }
    if(dati::command_old_sc3==3015) {
      ui->stackedWidget->setCurrentWidget(ui->page_joint);
    }
    if(dati::command_old_sc3==3016) {
      ui->stackedWidget->setCurrentWidget(ui->page_rot_gomito);
    }
    if(dati::command_old_sc3==3017) {
      ui->stackedWidget->setCurrentWidget(ui->page_rot_gomito);
    }
  }
}

void sc_assistivo::myfunction() //up
{
  col1 = Qt::green; //up
  ui->label_istr->setText("Spingi il joystick verso l'alto ");




  update();


  qDebug()<< "timer...";

}
void sc_assistivo::myfunction1() //down

{ //timer->stop();
  ui->label_istr->setText("Spingere il joystick verso il basso ");

  col1 = Qt::cyan;
  col2 = Qt::green;

  update();

  qDebug()<< "timer1...";


}
void sc_assistivo::myfunction2() //left
{ //timer1->stop();
  ui->label_istr->setText("Spingere il joystick verso destra ");

  col1= Qt::cyan;
  col2= Qt::cyan;
  col3 = Qt::green;




  update();

  qDebug()<< "timer2...";

}
void sc_assistivo::myfunction3() //right
{ ui->label_istr->setText("Spingere il joystick verso sinistra ");
  // timer2->stop();
  col1= Qt::cyan;
  col2= Qt::cyan;
  col3 = Qt::cyan;
  col4 = Qt::green;


  update();

  qDebug()<< "timer3...";

}
void sc_assistivo::myfunction4() {
  // timer3->stop();

  col4 = Qt::cyan;
  ui->label_istr->setText("Se sei soddisfatto della configurazione premi Salva, \n in caso contrario premi Configura");
  // qDebug()<< "timer4...";
  update();
}



// // update();



void sc_assistivo::on_pushButton_salva_clicked()
{

  QString   sesso, latodom, lb, la, h_sc3, w_sc3;
  float  lb_f, la_f, h_sc3_f, w_sc3_f;
  QString user;
  user = dati::username;
  dati::patologia = ui->lineEdit_patologia->text();
  sesso = ui->comboBox_sesso->currentText();
  latodom = ui->comboBox_latodom->currentText();
  lb = ui->lineEdit_lb->text();
  lb_f = lb.toFloat();
  la= ui->lineEdit_la->text();
  la_f = la.toFloat();
  h_sc3= ui->lineEdit_h->text();
  h_sc3_f= h_sc3.toFloat();
  w_sc3=ui->lineEdit_w->text();
  w_sc3_f = w_sc3.toFloat();


  QSqlQuery prova;
  prova.prepare("insert into Utenti_ass(usernameass, Sesso,Patologia,Lato_dominante, Lunghezza_braccio, Lunghezza_avambraccio, altezza, peso, data) values ('"+sesso+"', '"+dati::patologia+"', '"+latodom+"', '"+lb+"', '"+la+"', '"+h_sc3+"', '"+w_sc3+"', '"+dati::data1+"')");
  //prova.prepare("update Utenti_ass set Sesso = '"+sesso+"', Patologia = '"+dati::patologia+"', Lato_dominante= '"+latodom+"', Lunghezza_braccio = '"+lb+"', Lunghezza_avambraccio = '"+la+"', altezza = '"+h_sc3+"', peso = '"+w_sc3+"' where usernameass = '"+user+"'");
  prova.exec();
  if(prova.exec())
  {     QMessageBox::information(this, tr("Salvato"), tr("Modifiche salvate correttamente"));

    ARM_LENGTH_SC3 = {lb_f, la_f};



    ros::NodeHandle n;
    n.setParam ("/physiological_param/arm_length", ARM_LENGTH_SC3);

    n.setParam("physiological_param/height", h_sc3_f);
    n.setParam("physiological_param/weight",w_sc3_f);


    dati::status1 = 3002;

    std_msgs::Int16 msg_status;
    msg_status.data = dati::status1;
    ROS_INFO ("%d", msg_status.data);
    status_publisher.publish(msg_status);
  }
  else { qDebug()<<prova.lastError().text();

  }


}


void sc_assistivo::on_pushButton_vocale_clicked()
{       QMessageBox controllovoc;
        controllovoc.setText(tr("Si è scelto di utilizzare il controllo vocale per la sessione corrente.Confermare?"));
              QAbstractButton* pButtonYes = controllovoc.addButton(tr("Conferma"), QMessageBox::YesRole);
                    QAbstractButton* pButtonNo =  controllovoc.addButton(tr("No"), QMessageBox::NoRole);
                          controllovoc.exec();
                                if(controllovoc.clickedButton()==pButtonYes)
                                  //  QMessageBox messageBox(QMessageBox::Question, tr("Controllo Vocale"), tr("Si è scelto di utilizzare il controllo vocale. Confermare?"), QMessageBox::Yes | QMessageBox::No, this);
                                  //      messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
                                  //      messageBox.setButtonText(QMessageBox::No, tr("No"));
                                  //      if (messageBox.exec() ==QMessageBox::Yes)
                                {
                                  //messaggio ros per il controllo vocale

                                  dati::controllo_voc=1;
                                  ss_voc << "ho effettuato la configurazione dei ROM" ; // al posto di questa devo leggere qnode.variabile da dove l'ho modificata
                                  msg.data = ss_voc.str();
                                  status_publisher.publish(msg);

                                }
                                else if(controllovoc.clickedButton()==pButtonNo)      {
                                  dati::controllo_voc = 0;
                                }
}





void sc_assistivo::on_pushButton_joy_clicked()
{

  //     timer->start(5000);
  //     timer1->start(10000);
  //     timer2->start(15000);
  //     timer3->start(20000);
  //     timer4->start(25000);


  ui->stackedWidget->setCurrentWidget(ui->page_joy);


}





void sc_assistivo::on_pushButton_joystick_clicked()
{  QMessageBox controllojoy;
   controllojoy.setText(tr("Si è scelto di utilizzare il controllo vocale per la sessione corrente.Confermare?"));
    QAbstractButton* pButtonYes = controllojoy.addButton(tr("Conferma"), QMessageBox::YesRole);
     QAbstractButton* pButtonNo =  controllojoy.addButton(tr("No"), QMessageBox::NoRole);
      controllojoy.exec();
       if(controllojoy.clickedButton()==pButtonYes)
         //  QMessageBox messageBox(QMessageBox::Question, tr("Controllo con Joystick"), tr("Si è scelto di utilizzare il controllo vocale. Confermare?"), QMessageBox::Yes | QMessageBox::No, this);
         //    messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
         //    messageBox.setButtonText(QMessageBox::No, tr("No"));
         //    if (messageBox.exec() ==QMessageBox::Yes)
       {
         //messaggio ros per il controllo vocale

         dati::controllo_joy=1;
         ss_joy << "ho selezionato il controllo con il Joystick" ; // al posto di questa devo leggere qnode.variabile da dove l'ho modificata
         msg.data = ss_joy.str();
         status_publisher.publish(msg);


       }
       else if(controllojoy.clickedButton()==pButtonNo)
       {
         dati::controllo_joy = 0;
       }

}

void sc_assistivo::on_pushButton_gomito_clicked()

{ QMessageBox controllogom;
  controllogom.setText(tr("Si è scelto di controllare la rotazione del gomito.Confermare?"));
  QAbstractButton* pButtonYes = controllogom.addButton(tr("Conferma"), QMessageBox::YesRole);
  QAbstractButton* pButtonNo =  controllogom.addButton(tr("No"), QMessageBox::NoRole);
  controllogom.exec();
  if(controllogom.clickedButton()==pButtonYes)
    //  QMessageBox messageBox(QMessageBox::Question, tr("Controllo Rotazione del Gomito"), tr("Si è scelto di controllare la rotazione del gomito. Confermare?"), QMessageBox::Yes | QMessageBox::No, this);
    //   messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
    //   messageBox.setButtonText(QMessageBox::No, tr("No"));
    //   if (messageBox.exec() ==QMessageBox::Yes)
  {
    //messaggio ros per il controllo vocale

    dati::controllo_gomito=1;
    ss_elb_rot << "ho selezionato la rotazione del gomito" ; // al posto di questa devo leggere qnode.variabile da dove l'ho modificata
    msg.data = ss_elb_rot.str();
    status_publisher.publish(msg);


  }
  else if(controllogom.clickedButton()==pButtonNo)
  {
    dati::controllo_gomito = 0;
  }

}

//DESC LIMIT 1



void sc_assistivo::on_pushButton_singoloj_clicked()
{
  ui->stackedWidget->setCurrentWidget(ui->page_joint);
}

//void sc_assistivo::on_pushButton_modifica_2_clicked()
//{
//  dati::nuovo_utente = 0;
//   ui->stackedWidget->setCurrentWidget(ui->page_config);
//   if (dati::nuovo_utente==0)
//   {
//     QSqlQuery sel_mod;

//     sel_mod.prepare("select Sesso, Patologia, Lato_dominante, Lunghezza_braccio, Lunghezza_avambraccio,altezza,peso, uROM1_min, uROM1_max, uROM2_min, uROM2_max,uROM3_min, uROM3_max,uROM4_min, uROM4_max,uROM5_min, uROM5_max from Utenti_ass where usernameass = '"+dati::username+"' ");
//     if (sel_mod.exec()){
//     while (sel_mod.next()) {
//    //  sel_mod.value(0).toString();
//    //  sel_mod.value(2).toString();
//       QString patologia = sel_mod.value(1).toString();

//       ui->lineEdit_patologia->setText(patologia);
//       ui->lineEdit_la->setText(sel_mod.value(4).toString());
//       ui->lineEdit_lb->setText(sel_mod.value(3).toString());
//       ui->lineEdit_h->setText(sel_mod.value(5).toString());
//       ui->lineEdit_w->setText(sel_mod.value(6).toString());
//       ui->lineEdit_rom1_min->setText(sel_mod.value(7).toString());
//       ui->lineEdit_rom1_max->setText(sel_mod.value(8).toString());
//       ui->lineEdit_rom2_min->setText(sel_mod.value(9).toString());
//       ui->lineEdit_rom2_max->setText(sel_mod.value(10).toString());
//       ui->lineEdit_rom3_min->setText(sel_mod.value(11).toString());
//       ui->lineEdit_rom3_max->setText(sel_mod.value(12).toString());
//       ui->lineEdit_rom4_min->setText(sel_mod.value(13).toString());
//       ui->lineEdit_rom4_max->setText(sel_mod.value(14).toString());
//       ui->lineEdit_rom5_min->setText(sel_mod.value(15).toString());
//       ui->lineEdit_rom5_max->setText(sel_mod.value(16).toString());
//     }
//     }
//     else{qDebug()<<sel_mod.lastError();}




//   }
//}

void sc_assistivo::on_pushButton_salva_rom_sc3_clicked()
{
  QString   ROM1_min, ROM1_max, ROM2_min, ROM2_max, ROM3_min, ROM3_max, ROM4_min, ROM4_max, ROM5_min, ROM5_max;
  float ROM1_min_f, ROM1_max_f, ROM2_min_f, ROM2_max_f, ROM3_min_f, ROM3_max_f, ROM4_min_f, ROM4_max_f, ROM5_min_f, ROM5_max_f;
  QString user;
  user = dati::username;

  ROM1_min = ui->lineEdit_rom1_min->text();
  ROM1_min_f= ROM1_min.toFloat();
  ROM1_max = ui->lineEdit_rom1_max->text();
  ROM1_max_f= ROM1_max.toFloat();
  ROM2_min = ui->lineEdit_rom2_min->text();
  ROM2_min_f= ROM2_min.toFloat();
  ROM2_max = ui->lineEdit_rom2_max->text();
  ROM2_max_f= ROM2_max.toFloat();
  ROM3_min = ui->lineEdit_rom3_min->text();
  ROM3_min_f= ROM3_min.toFloat();
  ROM3_max = ui->lineEdit_rom3_max->text();
  ROM3_max_f= ROM3_max.toFloat();
  ROM4_min = ui->lineEdit_rom4_min->text();
  ROM4_min_f= ROM4_min.toFloat();
  ROM4_max = ui->lineEdit_rom4_max->text();
  ROM4_max_f= ROM4_max.toFloat();
  ROM5_min = ui->lineEdit_rom5_min->text();
  ROM5_min_f= ROM5_min.toFloat();
  ROM5_max = ui->lineEdit_rom5_max->text();
  ROM5_max_f= ROM5_max.toFloat();

  QSqlQuery prova;
  prova.prepare("update Utenti_ass set uROM1_min= '"+ROM1_min+"', uROM1_max = '"+ROM1_max+"', uROM2_min= '"+ROM2_min+"', uROM2_max = '"+ROM2_max+"', uROM3_min= '"+ROM3_min+"', uROM3_max = '"+ROM3_max+"', uROM4_min= '"+ROM4_min+"', uROM4_max = '"+ROM4_max+"', uROM5_min= '"+ROM5_min+"', uROM5_max = '"+ROM5_max+"' where usernameass = '"+user+"' desc limit 1" );;
  prova.exec();
  if(prova.exec())
  {     QMessageBox::information(this, tr("Salvato"), tr("Modifiche salvate correttamente"));


    J_MAX_SC3 = {ROM1_max_f, ROM2_max_f, ROM3_max_f, ROM3_max_f, ROM3_max_f};
    J_MIN_SC3 = {ROM1_min_f, ROM2_min_f, ROM3_min_f, ROM3_min_f, ROM3_min_f};


    ros::NodeHandle n;

    n.setParam("/physiological_param/ROM_Max", J_MAX_SC3);
    n.setParam("/physiological_param/ROM_Min", J_MIN_SC3);

    dati::status1 = 3005;

    std_msgs::Int16 msg_status;
    msg_status.data = dati::status1;
    ROS_INFO ("%d", msg_status.data);
    status_publisher.publish(msg_status);



  }
  else { qDebug()<<prova.lastError().text();

  }
}

void sc_assistivo::on_pushButton_skip_sc3_clicked()
{
  dati::status1 = 3004;

  std_msgs::Int16 msg_status;
  msg_status.data = dati::status1;
  ROS_INFO ("%d", msg_status.data);
  status_publisher.publish(msg_status);
}

void sc_assistivo::on_pushButton_spegni_clicked()
{
  emit ShowMain_sc3();
  accept();
}

void sc_assistivo::on_pushButton_configura_joy_sc3_clicked()
{
  dati::status1 = 3006;

  std_msgs::Int16 msg_status;
  msg_status.data = dati::status1;
  ROS_INFO ("%d", msg_status.data);
  status_publisher.publish(msg_status);
  timer_joy->start(10);
}

void sc_assistivo::on_pushButton_salta_joy_clicked()
{
  dati::status1 = 3008;

  std_msgs::Int16 msg_status;
  msg_status.data = dati::status1;
  ROS_INFO ("%d", msg_status.data);
  status_publisher.publish(msg_status);


}


void sc_assistivo::cal_joy()  {
  if(dati::command_sc3==3007) {

    qDebug()<<"sono nella funzione cal_joy";
    if ((dati::command_istr_sc3==0) && (dati::command_sec_sc3==0)) {
      dati::status1 = 3007;

      std_msgs::Int16 msg_status;
      msg_status.data = dati::status1;
      ROS_INFO ("%d", msg_status.data);
      status_publisher.publish(msg_status);
      ui->label_istr->setText("Quando sei pronto per iniziare la configurazione spingi il joysick verso l'ALTO.");

    }

    if(dati::command_istr_sc3==1) {

      myfunction();

      ui->label_istr->setText("Quando sei pronto per iniziare la configurazione spingi il joysick verso l'ALTO.");
      ui->pushButton_SU->setStyleSheet("background-color: white");
      QFont font = ui->pushButton_SU->font();
      font.setPointSize(19);
      ui->pushButton_SU->setFont(font);


      if(dati::command_sec_sc3==5){
        ui->pushButton_SU->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }
      if(dati::command_sec_sc3==4){
        ui->pushButton_SU->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }
      if(dati::command_sec_sc3==3){
        ui->pushButton_SU->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }
      if(dati::command_sec_sc3==2){
        ui->pushButton_SU->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }
      if(dati::command_sec_sc3==1){
        ui->pushButton_SU->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }

    }
    if(dati::command_istr_sc3 == 2) {

      ui->label_istr->setText("Quando sei pronto per iniziare la configurazione spingi il joysick verso il BASSO.");
      ui->label_joy_sec->setText("Configurazione Joystick");
      ui->pushButton_SU->setStyleSheet("background-color: white");
      ui->pushButton_GIU->setStyleSheet("background-color: white");
      QFont font = ui->pushButton_GIU->font();
      font.setPointSize(19);
      ui->pushButton_GIU->setFont(font);


    }
    if(dati::command_istr_sc3==3) {
      myfunction1();
      if(dati::command_sec_sc3==5){
        ui->pushButton_GIU->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }
      if(dati::command_sec_sc3==4){
        ui->pushButton_GIU->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));

      }
      if(dati::command_sec_sc3==3){
        ui->pushButton_GIU->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }
      if(dati::command_sec_sc3==2){
        ui->pushButton_GIU->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }
      if(dati::command_sec_sc3==1){
        ui->pushButton_GIU->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }
    }

    if(dati::command_istr_sc3 == 4) {
      qDebug()<< "sono nell'ex 4";
      ui->label_istr->setText("Quando sei pronto per iniziare la configurazione spingi il joysick verso SINISTRA.");
      ui->label_joy_sec->setText("Configurazione Joystick");
      ui->pushButton_GIU->setStyleSheet("background-color: white");
      ui->pushButton_SX->setStyleSheet("background-color: white");
      QFont font = ui->pushButton_SX->font();
      font.setPointSize(19);
      ui->pushButton_SX->setFont(font);


    }

    if(dati::command_istr_sc3==5) {
      myfunction3();
      if(dati::command_sec_sc3==5){
        ui->pushButton_SX->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }
      if(dati::command_sec_sc3==4){
        ui->pushButton_SX->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }
      if(dati::command_sec_sc3==3){
        ui->pushButton_SX->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }
      if(dati::command_sec_sc3==2){
        ui->pushButton_SX->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }
      if(dati::command_sec_sc3==1){
        ui->pushButton_SX->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }

    }

    if(dati::command_istr_sc3 == 6) {
      qDebug()<< "sono nell'ex 6";
      ui->label_istr->setText("Quando sei pronto per iniziare la configurazione spingi il joysick verso DESTRA.");
      ui->label_joy_sec->setText("Configurazione Joystick");
      ui->pushButton_SX->setStyleSheet("background-color: white");
      ui->pushButton_DX->setStyleSheet("background-color: white");
      QFont font = ui->pushButton_DX->font();
      font.setPointSize(19);
      ui->pushButton_DX->setFont(font);


    }
    if(dati::command_istr_sc3==7) {
      myfunction2();
      if(dati::command_sec_sc3==5){
        ui->pushButton_DX->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }
      if(dati::command_sec_sc3==4){
        ui->pushButton_DX->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }
      if(dati::command_sec_sc3==3){
        ui->pushButton_DX->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }
      if(dati::command_sec_sc3==2){
        ui->pushButton_DX->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }
      if(dati::command_sec_sc3==1){
        ui->pushButton_DX->setStyleSheet("background-color: green");
        ui->label_joy_sec->setText(QString("TEMPO: %1").arg(dati::command_sec_sc3));
      }
    }
  }
}

void sc_assistivo::on_pushButton_rifo_joy_clicked()
{
  dati::status1 = 3006;

  std_msgs::Int16 msg_status;
  msg_status.data = dati::status1;
  ROS_INFO ("%d", msg_status.data);
  status_publisher.publish(msg_status);
}

void sc_assistivo::on_pushButton_end_conf_joy_clicked()
{
  dati::status1 = 3008;

  std_msgs::Int16 msg_status;
  msg_status.data = dati::status1;
  ROS_INFO ("%d", msg_status.data);
  status_publisher.publish(msg_status);
}

void sc_assistivo::on_pushButton_clicked()
{
  dati::status1 = 3009;

  std_msgs::Int16 msg_status;
  msg_status.data = dati::status1;
  ROS_INFO ("%d", msg_status.data);
  status_publisher.publish(msg_status);

}
